#include "file_server.h"
#include "ui_file_server.h"
#include <QMessageBox>
#include <QFileDialog>

file_server::file_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file_server)
{
    ui->setupUi(this);
    port = 55555;
    file_trans_server = new QTcpServer(this);
    connect(file_trans_server, SIGNAL(newConnection()), this, SLOT(snd_file()));

    file_trans_server->close();
}

file_server::~file_server()
{
    delete ui;
}

void file_server::server_init()
{
    total_bytes = 0;
    bytes_written = 0;
    bytes_to_write = 0;
    payload_size = 1024 * 64;
    ui->file_progress->setValue(0);
}

void file_server::snd_file()
{
    qDebug() << "in_snd_file";
    client_conn = file_trans_server->nextPendingConnection();
    connect(client_conn, SIGNAL(bytesWritten(qint64)), this, SLOT(upd_send_progress(qint64)));
    file = new QFile(filename_path);
    if ( !file->open((QFile::ReadOnly)))
    {
        QMessageBox::warning(this, tr("应用程序"), tr("无法的读取文件%1:\n%2").arg(filename_path).arg(file->errorString()));
        return;
    }
    total_bytes = file->size();
    QDataStream send(&out_block, QIODevice::WriteOnly);
    send.setVersion(QDataStream::Qt_5_3);
    time.start();
    //QString filename_file = filename_path.right(filename_path.size() - filename_path.lastIndexOf('/') - 1);
    send << qint64(0) << qint64(0) << filename_file;
    total_bytes += out_block.size();
    send.device()->seek(0);
    send << total_bytes << qint64(out_block.size() - sizeof(qint64) * 2);
    bytes_to_write = total_bytes - client_conn->write(out_block);
    out_block.resize(0);
    qDebug() << "sendingfile";
}

void file_server::upd_send_progress(qint64 bytes_num)
{
    qApp->processEvents();
    qDebug() << "in upd_send_progress" << bytes_written;
    bytes_written += (int) bytes_num;
    if (bytes_to_write > 0)
    {
        out_block = file->read(qMin(bytes_to_write, payload_size));
        bytes_to_write -= (int)client_conn->write(out_block);
        out_block.resize(0);
    }
    else
    {
        qDebug() << "file_close()";
        file->close();
    }
    ui->file_progress->setMaximum(total_bytes);
    ui->file_progress->setValue(bytes_written);

    float use_time = time.elapsed();
    double speed = bytes_written / use_time;

    if (bytes_written == total_bytes)
    {
        file->close();
        file_trans_server->close();
        qDebug() << "file_done";
        QMessageBox::information(this, tr("文件传输"), tr("文件传输成功！"));
        this->close();
    }
}

void file_server::on_send_file_clicked()
{
    filename_path = QFileDialog::getOpenFileName(this);
    if(!filename_path.isEmpty())
    {
        filename_file = filename_path.right(filename_path.size() - filename_path.lastIndexOf('/') - 1);
        if (!file_trans_server->listen(QHostAddress::Any, port))
        {
            close();
            return;
        }
        emit snd_file_name(filename_file);
    }
}
