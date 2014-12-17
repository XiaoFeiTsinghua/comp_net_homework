#ifndef FILE_CLIENT_H
#define FILE_CLIENT_H

#include <QDialog>
#include <QtNetwork>
#include <QTime>
#include <QAbstractSocket>

namespace Ui {
class file_client;
}

class file_client : public QDialog
{
    Q_OBJECT

public:
    explicit file_client(QWidget *parent = 0);
    ~file_client();

    void set_host_addr(QHostAddress addr);
    void set_file_name(QString name);

private:
    Ui::file_client *ui;

    QTcpSocket *file_trans_client;
    qint16 block_size;
    QHostAddress host_addr;
    qint16 port;

    qint64 total_bytes;
    qint64 bytes_received;
    qint64 file_name_size;
    QString file_name;
    QFile *file;
    QByteArray in_block;

    QTime time;

private slots:

    void new_conn();
    void read_file();
    //void display_error(QAbstrackSocket::SocketError socket_err);
};

#endif // FILE_CLIENT_H
