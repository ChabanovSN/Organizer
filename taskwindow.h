#ifndef TASKWINDOW_H
#define TASKWINDOW_H
#include"Utiles.h"
#include <QDialog>

namespace Ui {
class TaskWindow;
}

class TaskWindow : public QDialog
{
    Q_OBJECT
signals:
void dialogClosed();
public:
    explicit TaskWindow(QWidget *parent = nullptr);
    ~TaskWindow();

    void setTask(Task *);
public slots:
    void closeAndWrite();
private:
      Utiles utils;
      Ui::TaskWindow *ui;
};

#endif // TASKWINDOW_H
