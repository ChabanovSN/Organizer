#include "taskwindow.h"
#include "ui_taskwindow.h"
#include<QDebug>
TaskWindow::TaskWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskWindow)
{
    ui->setupUi(this);
       setWindowTitle(QString::fromUtf8("Заметка"));
    ui->spinBoxId->hide();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setCalendarPopup ( true);
    ui->dateTimeEdit->setDisplayFormat(QString("dd.MM.yyyy HH:mm"));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(closeAndWrite()));
}

void TaskWindow::setTask(Task * task){

    ui->spinBoxId->setValue(task->getId());
    ui->lineEditName->setText(QString::fromStdString(task->getName()));
    ui->textEditDescription->setText(QString::fromStdString(task->getDescription()));
    ui->dateTimeEdit->setDateTime(task->getDateTime());



}
void TaskWindow::closeAndWrite()  {
    utils.writeInFile(
                ui->spinBoxId->value(),
                ui->lineEditName->text().toStdString(),
                ui->textEditDescription->toPlainText().toStdString(),
                ui->dateTimeEdit->dateTime());
    emit dialogClosed();
    this->accept();

}


TaskWindow::~TaskWindow()
{
    delete ui;
}
