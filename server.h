#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTime>
#include <QFile>
#include <QtNetwork>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = 0);
    void refused();

signals:

    void snd_file_name(QString file_name);

public slots:

private:
    Ui::Server *ui;

    qint16 port;
    QTcpServer *file_server;
    QFile *file;
    QString filename_path;
    QString filename_file;

    qint64 total_bytes;
    qint64 bytes_written;
    qint64 bytes_to_write;
    qint64 payload_size;

    QByteArray out_block;

    QTcpSocket *client_conn;

    QTime time;

private slots:

    void snd_msg();

    void upd_send_progress(qint64 bytes_num);

};

#endif // SERVER_H
