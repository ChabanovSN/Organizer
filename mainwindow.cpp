#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)

{

    setWindowTitle(QString::fromUtf8("Органайзер"));

    setStyleSheet("border-image: url(:/border.jpg);");
     msg = new QMessageBox(this);
     msg->setStyleSheet(setting);
    lstWgt = new QListWidget;
    QLayout* l = new QVBoxLayout;

    tb = new QToolBar();
    tb->setStyleSheet(setting);
    tb->addAction(QString::fromUtf8("Добавить"),this,SLOT(newRecord()));
    tb->addAction(QString::fromUtf8("Обновить"),this,SLOT(getNewList()));
    tb->addAction(QString::fromUtf8("Выход"),this,SLOT(close()));
    l->setMenuBar(tb);
    l->addWidget( lstWgt );
    setLayout( l );
    connect(&taskWindow,SIGNAL(dialogClosed()),this,SLOT(getNewList()));
    getNewList();
    resize(530, 500 );
}
void MainWindow::newRecord(){
    if(listTasks.size()>=2){
        msg->setWindowTitle(QString::fromUtf8("Внимание"));
        msg->setText(QString::fromUtf8("Количество записей 100, удалите ненужные"));
        msg->show();
//        msg->information( this, QString::fromUtf8("Внимание"),
//                                  QString::fromUtf8("Количество записей 100, удалите ненужные"));
    }else{
        QDateTime d = QDateTime::currentDateTime();
        taskWindow.setTask(new Task(101,"","",d));
        taskWindow.show();

    }

}
void MainWindow::getNewList(){
    lstWgt->clear();
    listTasks.clear();
    listTasks= utils.readFile();
    sort(listTasks.begin(), listTasks.end(),
         [](Task* a, Task* b) -> bool { return a->getDateTime() < b->getDateTime(); });

    int i=1;
    foreach(  Task * task, listTasks){
        makeItem(i++, task,lstWgt );
    }
}

void MainWindow::makeItem(int i, Task * task,QListWidget* lstWgt) {
    QWidget* wgt = new QWidget;
    QLayout* l = new QHBoxLayout;
    QSpinBox *id = new QSpinBox();
    id->setValue(task->getId());
    id->hide();
    QString name;
    name.append(QString::number(i)).append(") ")
            .append(task->getDateTime().toString(Qt::LocaleDate));

    QLabel *num = new QLabel(name);
    num->setFixedSize(QSize(180, 25));

    QPushButton* btn1 = new QPushButton(QString::fromStdString(task->getName()));
    btn1->setFixedSize(QSize(250, 25));

    QPushButton* btn2 = new QPushButton(QString::fromUtf8("X"));

    if(task->getDateTime()<=QDateTime::currentDateTime()){
        num->setStyleSheet(settingR);
        btn1-> setStyleSheet(settingR);
        btn2-> setStyleSheet(settingR);
    }else{
        num->setStyleSheet(setting);
        btn1-> setStyleSheet(setting);
        btn2-> setStyleSheet(setting);
    }


    btn2->setFixedSize(QSize(40, 25));

    connect( btn1, SIGNAL( clicked() ), SLOT( onBtnClicked() ) );
    connect( btn2, SIGNAL( clicked() ), SLOT( onBtnClickedDel() ) );
    l->addWidget( id);
    l->addWidget(num);
    l->addWidget( btn1 );
    l->addWidget( btn2 );
    wgt->setLayout( l );

    QListWidgetItem* item = new QListWidgetItem( lstWgt );
    item->setSizeHint( wgt->sizeHint() );
    lstWgt->setItemWidget( item, wgt );
}
void MainWindow::onBtnClicked() {
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) ) {
        if( QSpinBox* i = btn->parent()->findChild< QSpinBox* >() ) {
            for(auto t : listTasks)
                if(t->getId()==i->value()){
                    taskWindow.setTask(t);
                    taskWindow.show();
                    return;
                }

        }
    }
}
void MainWindow:: onBtnClickedDel(){
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) ) {
        if( QSpinBox* i = btn->parent()->findChild< QSpinBox* >() ) {
            for(auto t : listTasks)
                if(t->getId()==i->value()){
                    utils.deleteRecord(i->value());
                    getNewList();
                    return;
                }

        }
    }
}
MainWindow::~MainWindow()
{   delete msg;
    delete tb ;
    delete lstWgt;
    foreach(Task* t,listTasks) delete t;

}

