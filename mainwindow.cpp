#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QDebug>
#include <QMessageBox>
#include "file_server.h"
#include "file_client.h"
#include "online_video.h"
//#include ""

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr(" "));
    tcpServer = new QTcpServer(this);
    tcpSocket_s = new QTcpSocket(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(receive_connection()));
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
    }
    ui->self_port->setText(tr("%1").arg(tcpServer->serverPort()));

    file_srv = new file_server(this);
    connect(file_srv, SIGNAL(snd_file_name(QString)), this, SLOT(get_filename(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_file_transfer_clicked()
{
    file_srv->show();
    file_srv->server_init();
    //qDebug() << fileName << IP << port;
}


void MainWindow::on_text_transfer_clicked()
{
    text = ui->text->text();
    IP = ui->oppo_ip->text();
    port = ui->oppo_port->text().toInt();
    tcpSocket_s->connectToHost(IP, port);
    if(tcpSocket_s->ConnectedState == QAbstractSocket::ConnectedState)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << (qint32)0;
        out << text;
        out.device()->seek(0);
        out << (qint16)0 << (qint16)(block.size() - sizeof(qint32));
        tcpSocket_s->write(block);
        tcpSocket_s->disconnectFromHost();
        //qDebug() << text << IP << port;
    }
}

void MainWindow::receive_connection()
{
    tcpSocket_r = tcpServer->nextPendingConnection();
    connect(tcpSocket_r, SIGNAL(readyRead()), this, SLOT(read_tcp()));
}

void MainWindow::read_tcp()
{
    QDataStream in(tcpSocket_r);
    in.setVersion(QDataStream::Qt_5_3);
    qint16 type;
    in >> type;
    if (type == (qint16)0)
    {
        qDebug() << "reading text!";
        in >> blocksize;
        if (tcpSocket_r->bytesAvailable() < blocksize)
            return;
        QString text;
        in >> text;
        QMessageBox::information(this, "good!", text);
    }
    else if (type == (qint16)1)
    {
        qint16 tmp;
        in >> tmp;
        QString filename;
        in >> filename;
        has_pending_file(filename);
    }
}

void MainWindow::get_filename(QString name)
{
    fileName = name;
    IP = ui->oppo_ip->text();
    port = ui->oppo_port->text().toInt();
    tcpSocket_s->connectToHost(IP, port);
    if(tcpSocket_s->ConnectedState == QAbstractSocket::ConnectedState)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << (qint32)0;
        out << fileName;
        out.device()->seek(0);
        out << (qint16)1 << (qint16)(block.size() - sizeof(qint32));
        tcpSocket_s->write(block);
        tcpSocket_s->disconnectFromHost();
    }
}

void MainWindow::has_pending_file(QString filename)
{
    IP = ui->oppo_ip->text();
    int btn = QMessageBox::information(this, tr("接受文件"), tr("来自A的文件%1,是否接受？").arg(filename),QMessageBox::Yes, QMessageBox::No);
    if (btn == QMessageBox::Yes)
    {
        file_client *client = new file_client(this);
        client->set_file_name(filename);
        client->set_host_addr(QHostAddress(IP));
        client->show();
    }
}

void MainWindow::on_online_video_clicked()
{
    IP = ui->oppo_ip->text();
    online_video *w = new online_video(IP);
    w->show();
}
