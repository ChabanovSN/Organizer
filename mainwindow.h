#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Utiles.h"
#include <QMainWindow>
#include<QVBoxLayout>
#include<QListWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QSpinBox>
#include<QMessageBox>
#include<QToolBar>
#include<QLabel>
#include"taskwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void makeItem(int i, Task * task, QListWidget * lstWgt );
public slots:
    void onBtnClicked();
    void onBtnClickedDel();
    void getNewList();
    void newRecord();
private:
    QToolBar *tb ;
    QListWidget* lstWgt;
    Utiles utils;
    QList<Task*> listTasks;
    TaskWindow taskWindow;
    const char * setting = "text-align: center;\
            color:#CD0E6B;\
    font-size: 12pt;\
    font-weight: bold;";

};
#endif // MAINWINDOW_H
