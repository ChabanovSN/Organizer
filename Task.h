#ifndef TASK_H
#define TASK_H
#include<iostream>
#include<string.h>
#include<QDateTime>
using namespace std;
class Task{
 int id=0;
 char name[50];
 char description[300];
 QDateTime date;
  public:
    Task(){}
    Task( int id, string  name,string descrip, QDateTime date){
       setId(id);
       setName(name);
       setDescription(descrip);
       setDateTime(date);
    }
    int getId(){
        return id;
    }
    void setId(int id){
        this->id=id;
    }
    void setDateTime( QDateTime d){
       date=d;
    }
     QDateTime getDateTime(){
        return date;
    }
    void setName(string nameString){
        const char *nameValue = nameString.data();
        int length = nameString.size();
        length = ( length < 50 ? length : 49 ) ;
        strncpy( name, nameValue, length );
        name[ length ] = '\0';
    }
    string getName(){
        return string(name);
    }
    void setDescription(string descrString){
        const char *descripValue = descrString.data();
        int length = descrString.size();
        length = ( length < 300 ? length : 299 ) ;
        strncpy(description, descripValue, length );
        description[ length ] = '\0';
    }
    string getDescription(){
        return string(description);
    }
    string toString(){
        string str;
        return  str.append(name).append(": ").append(description);
    }
};

#endif // TASK_H
