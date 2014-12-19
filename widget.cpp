#include "widget.h"
#include "friendwidget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(275, 600);
    choosew = new ChooseWidget(this);
    //HeadButton *h = new HeadButton(this);
    /*
    list = new QListWidget(this);
    list->resize(200, 600);
    FriendWidget *f = new FriendWidget();
    QListWidgetItem *i = new QListWidgetItem();
    i->setSizeHint(QSize(200, 50));
    list->addItem(i);
    list->setItemWidget(i, f);

    tree = new QTreeWidget(this);
    tree->resize(275, 600);
    tree->move(200, 0);
    QStringList str;
    str << QObject::tr("张三");
    QTreeWidgetItem *treeitem = new QTreeWidgetItem(tree, str);
    QTreeWidgetItem *child1 = new QTreeWidgetItem(treeitem, str);
    treeitem->addChild(child1);
    */
    createTray();

    chat_server = new QTcpServer(this);
    chat_server->listen(QHostAddress::Any, 55554);
    connect(chat_server, SIGNAL(newConnection()), this, SLOT(receive_connection()));
    connect(choosew, SIGNAL(to_up_msg(QString,QString)), this, SLOT(send_msg(QString, QString)));
    connect(choosew, SIGNAL(new_conn(QString, QString)), this, SLOT(new_conn(QString, QString)));
    connect(this, SIGNAL(rec_msg(QString,QString)), choosew, SLOT(from_up_msg(QString,QString)));
}

void Widget::setUsername(QString name)
{
    username = name;
    qDebug() << "username: " << username;
}


void Widget::init()
{
    this->resize(275, 600);
    //choosew->setUsername(this->username);
    //choosew->init();
}


Widget::~Widget()
{
    delete ui;
}

void Widget::createTray()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/image/tray"));
    trayIcon->setToolTip(tr("qq"));
    QString titlec=tr("子曰USay");
    QString textc=tr("子曰USay：给你神一般的体验");
    trayIcon->show();
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
}

void Widget::send_msg(QString id, QString msg)
{
    if (socket_map.contains(id))
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << (qint32)0;
        out << msg;
        out.device()->seek(0);
        out << (qint16)1 << (qint16)(block.size() - sizeof(qint32));
        QMap<QString, QTcpSocket*>::iterator it = socket_map.find(id);
        QString tmp;
        tmp = block;
        it.value()->write(block);
        qDebug() << "in Widget::send_msg, sending msg to id, the socket is:" << it.value();
        qDebug() << "what i send is" << msg << "to" << id;
    }
    else
    {
        qDebug() << "error!in send_msg, no id found!";
    }
}

void Widget::new_conn(QString id, QString ip)
{
    if (!socket_map.contains(id))
    {
        QTcpSocket* new_sock = new QTcpSocket(this);
        new_sock->connectToHost(ip, 55554);
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << username;
        new_sock->write(block);
        qDebug() << "new_conn_sending" << username << "ip:" << ip;
        if (!new_sock->waitForReadyRead(300))
        {

        }
        QDataStream in(new_sock);
        qint16 result;
        in.setVersion(QDataStream::Qt_5_3);
        in >> result;
        qDebug() << "in" << in;
        if (result == -1)
        {
            new_sock->disconnectFromHost();
            delete new_sock;
            QMessageBox::warning(this, "connection failure!", "Cannot connect to the friend!");
        }
        else
        {
            socket_map.insert(id, new_sock);
            QMap<QString, QTcpSocket*>::iterator it = socket_map.find(id);
            connect(it.value(), SIGNAL(readyRead()), this, SLOT(read_tcp()));
            new_sock = NULL;
        }
    }
    qDebug() << "socket_map_in_new_conn" << socket_map;
}

void Widget::receive_connection()
{
    waiting_soc = chat_server->nextPendingConnection();
    connect(waiting_soc, SIGNAL(readyRead()), this, SLOT(wait_for_id()));
}

void Widget::wait_for_id()
{
    QDataStream in(waiting_soc);
    in.setVersion(QDataStream::Qt_5_3);
    QString id;
    in >> id;
    qDebug() << "wair_for_id_id: " << id;
    if (!socket_map.contains(id))
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        if (!id.startsWith("2012") || id.length() != 10)
        {
            out << (qint32)0;
            out << "configure failed, going to close this session.";
            out.device()->seek(0);
            out << (qint16)-1 << (qint16)(block.size() - sizeof(qint32));
            qDebug() << "out-1" << " " << id;
            waiting_soc->write(block);
            waiting_soc->disconnectFromHost();
            disconnect(waiting_soc, SIGNAL(readyRead()), this, SLOT(wait_for_id()));
            delete waiting_soc;
        }
        else
        {
//            out << (qint32)0;
//            out << "configure success, going to keep this session.";
//            out.device()->seek(0);
//            out << (qint16)0 << (qint16)(block.size() - sizeof(qint32));
            qDebug() << "out0";
            waiting_soc->write(block);
            socket_map.insert(id, waiting_soc);
            disconnect(waiting_soc, SIGNAL(readyRead()), this, SLOT(wait_for_id()));
            QMap<QString, QTcpSocket*>::iterator it = socket_map.find(id);
            connect(it.value(), SIGNAL(readyRead()), this, SLOT(read_tcp()));
            waiting_soc = NULL;
        }
    }
    qDebug() << "socket_map_in_wait_for_id" << socket_map;
}

void Widget::read_tcp()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_3);
    qint16 type;
    in >> type;
    qDebug() << "Widget::read_tcp()::type" << type << "socket: " << socket;
    qint16 blocksize;
    in >> blocksize;
    QString text;
    in >> text;
    if (type == (qint16)1)
    {
        QString id;
        QMap<QString, QTcpSocket*>::iterator it;
        for ( it = socket_map.begin(); it!= socket_map.end(); it++ )
        {
            if ( it.value() != socket )
                continue;
            else
            {
                id = it.key();
                break;
            }
        }
        qDebug() << "reading text!in widget::read_tcp()";
        if (socket->bytesAvailable() < blocksize)
            return;
        QMessageBox::information(this, "good!", text);
        emit rec_msg(id, text);
    }
    else
    {
        QMessageBox::warning(this, "not good!", "type" + QString(type) + "blocksize:"+QString(blocksize)+ "text:"+text);
    }
}
