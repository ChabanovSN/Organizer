#ifndef UTILES_H
#define UTILES_H
#include"Task.h"
#include <fstream>
#include<iomanip>
#include<QList>
#include<QFile>
#define  FileTask "FileTasks.dat"


using namespace std;
class Utiles{
    Task task;

public:
    Utiles(){
//        QFile file(FileTask);
//        file.open(QIODevice::WriteOnly);
//        file.close();

        fstream f;
        f.open(FileTask,ios::in|ios::binary);//открываем поток для чтения
        long file_size;
        f.seekg(0, ios::end);
        file_size = f.tellg();
        if (file_size == 0){
            //  если файла нет то создаем его и заполняем пустышкми на 100 записей
            ofstream outTask( FileTask, ios::binary);
            // если ofstream не смог открыть файл, выйти из программы
            if ( !outTask ){
                cerr << "File could not be opened." << endl;
                exit( 1 );
            }

            Task blankTask; // конструктор обнуляет все элементы

            // вывести в файл 100 пустых записей
            for ( int i = 0; i < 100; i++ )
                outTask.write( reinterpret_cast<const char *>(&blankTask),
                               sizeof( Task ) );

            outTask.close();
        }
    }
    void writeInFile(int id, string name,string description, QDateTime date){
        //        cout << "File " <<id<<" "<<name<<" "<<description<<" "
        //             <<date.toString().toStdString()<<endl;

        fstream outTasks( FileTask, ios::in|ios::out|ios::binary );
        // если fstream не смог открыть файл, выйти из программы
        if ( !outTasks )
        {
            cerr << "File could not be opened." << endl;
            exit( 1 );
        } // конец if

        if(id >=101){
            id=getId(outTasks);
            // cout << "File " <<id<<" "<<name<<description<< endl;
        }
        if ( id > 0 && id <= 100 )
        {
            // прользователь вводит фамилию, имя и баланс
            //            cout << "Enter name, description, \n? ";
            //            cin >> setw( 50 ) >> name;
            //            cin >> setw( 300 ) >> description;


            // установить
            task.setId(id);
            task.setName(name);
            task.setDescription(description);
            task.setDateTime(date);

            // найти позицию записи
            outTasks.seekp( ( task.getId() - 1 ) * sizeof( Task) );

            // записать специфицированную пользователем информацию в файл
            outTasks.write( reinterpret_cast< const char * >( &task ),
                            sizeof( Task ) );

            // предложить пользователю ввести следующий счет
            // cout << " задача №"<<id<<" записана\n? ";
            // cin >> id;
        } // конец while
    }


    QList<Task *> readFile(){
        QList<Task *> list;
        ifstream inTask( FileTask, ios::in );

        // если ifstream не смог открыть файл, выйти из программы
        if ( !inTask )
        {
            cerr << "File could not be opened." << endl;
            exit( 1 );
        } // конец if

        //        cout << left << setw( 10 ) << "Task" <<setw( 50 )
        //             << "name" << setw(300 ) << "description"<< endl;


        // прочитать из файла первую запись
        inTask.read( reinterpret_cast< char * >( &task ),
                     sizeof(Task) );

        // прочитать все записи файла
        while ( inTask && !inTask.eof() )
        {
            // вывести запись
            if ( task.getId() != 0 ){
                Task *newTask = new Task();
                newTask->setId(task.getId());
                newTask->setName(task.getName());
                newTask->setDescription(task.getDescription());
                newTask->setDateTime(task.getDateTime());
                list.push_back(newTask);
            }
            // outputLine( cout, task );

            // прочитать из файла следующую запись
            inTask.read( reinterpret_cast< char * >( &task),
                         sizeof( Task) );
        } // конец while

        return list;

    }

    void deleteRecord(int id)
    {
        fstream deleteFromFile( FileTask, ios::out|ios::binary|ios::in );
        deleteFromFile.seekg( ( id-1 ) * sizeof(Task) );
        // прочитать запись из файла
        deleteFromFile.read( reinterpret_cast< char * >(&task),
                             sizeof(Task) );
        // если запись существует, удалить запись из файла
        if ( task.getId() != 0 )
        {
            Task blankTask; // создать пустую запись
            // переместить указатель позиции файла к нужной записи
            deleteFromFile.seekp( ( id - 1 ) *sizeof(Task) );
            // заменить существующую запись пустой записью
            deleteFromFile.write(
                        reinterpret_cast< const char * >( &blankTask ),sizeof(Task) );
            //  cout << "Task #" << id << " deleted. \n" ;
        } // конец if
        else // если запись не существует, сообщить об ошибке
            cerr << "Account #" << id << " is empty. \n";
    } // конец функции deleteRecord


    int getId(  fstream &outTasks)
    {
        int id=1;

        // получить значение номера счета1020

        do
        {
            outTasks.seekg( ( id-1 ) * sizeof(Task) );
            // прочитать запись из файла
            outTasks.read( reinterpret_cast< char * >(&task),
                           sizeof(Task) );

            if(task.getId()==0){
                break;
            }
            id++;

        } while ( id < 100 );

        return id;
    }


};

#endif // UTILES_H
