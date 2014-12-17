#include "interface.h"
#include "ui_interface.h"
#include <QDebug>
#include <QMessageBox>

interface::interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface)
{
    ui->setupUi(this);
    log = new QTcpSocket(this);
    con();
}

interface::~interface()
{
    delete ui;
}

void interface::con()
{
    if (log != NULL)
    {
        delete log;
        log = NULL;
    }
    log = new QTcpSocket(this);
    log->connectToHost("166.111.180.60", 8000);
}

void interface::on_listWidget_doubleClicked(const QModelIndex &index)
{

}

void interface::on_login_clicked()
{
    QString id = ui->id->text();
    QString st = id + '_' + "net2014";
    QByteArray bt;
    bt.append(st);
    if (log == NULL)
    {
        con();
    }
    log->write(bt);
    if (!log->waitForReadyRead(300))
    {

    }
    bt = log->readAll();
    if (bt == "lol")
    {
        QMessageBox::information(this, tr("登录信息"),tr("成功！"));
        qDebug() << "lol";
    }
    else
    {
        QMessageBox::information(this, tr("登录信息"),tr("失败！"));
        qDebug() << "false";
    }
}

void interface::on_logout_clicked()
{
    QString id = ui->id->text();
    QString st = "logout" + id;
    QByteArray bt;
    bt.append(st);
    if (log == NULL)
    {
        con();
    }
    log->write(bt);
    if (!log->waitForReadyRead(300))
    {

    }
    bt = log->readAll();
    if (bt == "loo")
    {
        QMessageBox::information(this, tr("下线信息"),tr("成功！"));
        qDebug() << "loo";
    }
    else
    {
        QMessageBox::information(this, tr("下线信息"),tr("失败！"));
        qDebug() << "false";
    }
}

void interface::on_add_friends_clicked()
{

}
