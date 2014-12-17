#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "file_server.h"

namespace Ui {
class MainWindow;
}

class file_server;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_file_transfer_clicked();

    void on_text_transfer_clicked();

    void read_tcp();

    void receive_connection();

    void get_filename(QString filename);

    void on_online_video_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QString IP;
    int port;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket_r;
    QTcpSocket* tcpSocket_s;

    file_server *file_srv;

    quint16 blocksize;

    QString text;

    void has_pending_file(QString filename);
};

#endif // MAINWINDOW_H
