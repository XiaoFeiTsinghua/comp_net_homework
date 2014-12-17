#include "friendwidget.h"

FriendWidget::FriendWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(275, 30);
    photo = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    qDebug()<<"1"<<endl;
}

FriendWidget::FriendWidget(QString id, QPixmap p, QString n, QString s, QWidget *parent) :
    QWidget(parent),
    id(id)
{
    this->resize(275, 30);
    photo = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    init(p, n, s);
}

void FriendWidget::init(QPixmap p, QString n, QString s)
{
    photo->resize(20,20);
    photo->move(0, 5);
    photo->setPixmap(p);

    name->resize(100, 20);
    name->move(30, 5);
    name->setText(n);

    sign->resize(100, 20);
    sign->move(150, 5);
    sign->setText(s);
}
