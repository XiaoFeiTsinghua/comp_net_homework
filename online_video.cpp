#include "online_video.h"
#include "ui_online_video.h"
#include "MatToQImage.h"

#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QDebug>

online_video::online_video(QString server_address, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::online_video),
    server_address(server_address)
{
    ui->setupUi(this);
    cap = new VideoCapture(0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateFrame()));
    timer->start(100);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress::LocalHost, 55556);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

online_video::~online_video()
{
    delete ui;
}

void online_video::closeEvent()
{
    delete cap;
    delete timer;
    delete sender;
    delete receiver;
}

void online_video::UpdateFrame()
{
    *cap >> frame;
    QImage tmp = MatToQImage(frame);
    tmp = tmp.scaled(128,128);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(tmp));
    ui->video->setScene(scene);
    ui->video->show();
    QByteArray datagram;
    QBuffer buf(&datagram);
    buf.open(QIODevice::WriteOnly);
    tmp.save(&buf, "PNG");
    buf.close();
    //QByteArray datagram((char*)tmp.bits(), tmp.byteCount());
    //datagram = qCompress(tmp.bits(), tmp.byteCount());
    //qDebug() << datagram.size() << tmp.byteCount();
    sender->writeDatagram(datagram.data(), datagram.size(), QHostAddress(server_address), 55556);
}

void online_video::readPendingDatagrams()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        //QString string(datagram);
        QImage tmp;
        tmp.loadFromData(datagram, "PNG");
        qDebug() << tmp.byteCount();
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(tmp));
        ui->video2->setScene(scene);
        ui->video2->show();
        ui->udp_trans->setText(QString(count));
        qDebug() << "inhere!";
    }
}
