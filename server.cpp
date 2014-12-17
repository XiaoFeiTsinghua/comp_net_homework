#include "server.h"

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    port = 55555;
    file_server = new QTcpServer(this);
    connect(file_server, SIGNAL(newConnection()), this, SLOT(snd_msg()));

    total_bytes = 0;
    bytes_written = 0;
    bytes_to_write = 0;
    payload_size = 1024 * 64;

    file_server->close();
}

