#include "file_client.h"
#include "ui_file_client.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

file_client::file_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file_client)
{
    ui->setupUi(this);
    total_bytes = 0;
    bytes_received = 0;
    file_name_size = 0;
    file_trans_client = new QTcpSocket(this);
    port = 55555;
    connect(file_trans_client, SIGNAL(readyRead()), this, SLOT(read_file()));
    //connect(file_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstrackSocket::SocketError)));
}

file_client::~file_client()
{
    delete ui;
}

void file_client::read_file()
{
    qDebug() << "in_file_client::read_file";
    QDataStream in(file_trans_client);
    in.setVersion(QDataStream::Qt_5_3);
    float use_time = time.elapsed();

    if (bytes_received <= sizeof(qint64) * 2)
    {
        if ( file_trans_client->bytesAvailable() >= sizeof(qint64) * 2 && file_name_size == 0)
        {
            in >> total_bytes >> file_name_size;
            bytes_received += sizeof(qint64) * 2;
        }
        if (file_trans_client->bytesAvailable() >= file_name_size && file_name_size != 0)
        {
            in >> file_name;
            bytes_received += file_name_size;

            if(!file->open(QFile::WriteOnly))
            {
                QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件%1:\/%2").arg(file_name).arg(file->errorString()));
                return;
            }
            else
                return;
        }
    }
    if (bytes_received < total_bytes)
    {
        bytes_received += file_trans_client->bytesAvailable();
        in_block = file_trans_client->readAll();
        file->write(in_block);
        in_block.resize(0);
    }

    ui->receive_progress->setMaximum(total_bytes);
    ui->receive_progress->setValue(bytes_received);

    double speed = bytes_received / use_time;

    if (bytes_received == total_bytes)
    {
        file->close();
        file_trans_client->close();
        QMessageBox::information(this, tr("文件传输"), tr("文件传输成功！"));
        this->close();
    }

}

void file_client::set_host_addr(QHostAddress addr)
{
    host_addr = addr;
    new_conn();
}

void file_client::set_file_name(QString name)
{
    file = new QFile(name);
}

void file_client::new_conn()
{
    block_size = 0;
    file_trans_client->abort();
    file_trans_client->connectToHost(host_addr, 55555);
    time.start();
}
