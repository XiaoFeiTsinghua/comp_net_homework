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
    functionw = new FunctionWidget(username, this);
    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);

    chat_server = new QTcpServer(this);
    chat_server->listen(QHostAddress::Any, 55554);
    connect(chat_server, SIGNAL(newConnection()), this, SLOT(receive_connection()));
    connect(choosew, SIGNAL(to_up_msg(QString,QString)), this, SLOT(send_msg(QString, QString)));
    connect(choosew, SIGNAL(new_conn(QString, QString)), this, SLOT(new_conn(QString, QString)));
    connect(this, SIGNAL(rec_msg(QString,QString)), choosew, SLOT(from_up_msg(QString,QString)));
    connect(functionw, &FunctionWidget::added, choosew, &ChooseWidget::refresh_friends);
}

Widget::Widget(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    username = name;
    ui->setupUi(this);
    this->resize(275, 600);
    //判断该用户是否曾在本机登录，如果没有，创建文件夹以保存其信息
    QDir *temp = new QDir;
    bool exist = temp->exists(username);

    if(exist)
        qDebug() << "exist";
    else
        newFolder(username);

    //构建好友列表
    choosew = new ChooseWidget(username, this);

    //构建功能菜单
    functionw = new FunctionWidget(username, this);

    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);
    //托盘
    createTray();
    //圆角
    setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);
    setMask(bmp);//设置窗体遮罩

    chat_server = new QTcpServer(this);
    chat_server->listen(QHostAddress::Any, 55554);
    connect(chat_server, SIGNAL(newConnection()), this, SLOT(receive_connection()));
    connect(choosew, SIGNAL(to_up_msg(QString,QString)), this, SLOT(send_msg(QString, QString)));
    connect(choosew, SIGNAL(new_conn(QString, QString)), this, SLOT(new_conn(QString, QString)));
    connect(this, SIGNAL(rec_msg(QString,QString)), choosew, SLOT(from_up_msg(QString,QString)));
    connect(exitButton, &QPushButton::clicked, this, &Widget::close);
    connect(functionw, &FunctionWidget::added, choosew, &ChooseWidget::refresh_friends);

    this->setMouseTracking(true);
    exitButton->setMouseTracking(true);
    minButton->setMouseTracking(true);

    init();
}

//设置用户（用于切换账号，功能还未实现）
void Widget::setUsername(QString name)
{
    username = name;
}


void Widget::init()
{
    this->resize(275, 600);
    this->setWindowFlags(Qt::FramelessWindowHint);
    choosew->resize(275, 500);
    choosew->move(0, 50);

    functionw->resize(275, 50);
    functionw->move(0, 550);

    exitButton->resize(20, 20);
    exitButton->move(255, 0);
    exitButton->setIcon(QIcon(":/image/close"));
    exitButton->setStyleSheet("border:none; background-color:transparent;");

    minButton->resize(20, 20);
    minButton->move(235, 0);
    minButton->setIcon(QIcon(":/image/min"));
    minButton->setStyleSheet("border:none; background-color:transparent;");
    //deleteFriend(username, 5);
    //deleteGroup(username, 3);
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
    QString titlec=tr("qq");
    QString textc=tr("不想写……");
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

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(inButton(exitButton, e->pos()))
        exitButton->setStyleSheet("border:none; background-color: rgb(255, 0, 4);");
    else
        exitButton->setStyleSheet("border:none; background-color:transparent;");

    if(inButton(minButton, e->pos()))
        minButton->setStyleSheet("border:none; background-color: rgba(255, 0, 0, 100);");
    else
        minButton->setStyleSheet("border:none; background-color:transparent;");


    if (e->buttons() == Qt::LeftButton)
           move(e->globalPos() - pPos);
}

bool Widget::inButton(QPushButton *push, QPoint p)
{
    int height = push->height();
    int width = push->width();
    QPoint left_up = push->pos();
    QPoint right_down;
    right_down.setX(push->pos().x() + width);
    right_down.setY(push->pos().y() + height);
    if((p.x() >= left_up.x()) && (p.x() <= right_down.x()) && (p.y() >= left_up.y()) && (p.y() <= right_down.y()))
        return true;
    else
        return false;
}

void Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
           pPos = mouseEvent->pos();
}

