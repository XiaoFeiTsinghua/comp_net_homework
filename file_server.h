#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include <QDialog>
#include <QtNetwork>
#include <QTime>

namespace Ui {
class file_server;
}

class file_server : public QDialog
{
    Q_OBJECT

public:
    explicit file_server(QWidget *parent = 0);
    ~file_server();
    void refused();
    void server_init();

signals:

    void snd_file_name(QString file_name);

public slots:

private:
    Ui::file_server *ui;

    qint16 port;
    QTcpServer *file_trans_server;
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

    void snd_file();

    void upd_send_progress(qint64 bytes_num);

    void on_send_file_clicked();
};

#endif // FILE_SERVER_H
