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

FriendWidget::FriendWidget(int id, int bt, QString num, QPixmap p, QString n, QString s, QWidget *parent) :
    QWidget(parent),
    id(id)
{
    this->resize(275, 30);
    photo = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    belongto = bt;
    studentnum = num;
    photopix = p;
    namestr = n;
    signstr = s;
    init();
}

void FriendWidget::init()
{
    this->resize(275, 30);
    photo->resize(20,20);
    photo->move(5, 5);
    photo->setScaledContents(true);
    photo->setPixmap(photopix);

    name->resize(100, 20);
    name->move(30, 5);
    name->setText(namestr);

    sign->resize(100, 20);
    sign->move(150, 5);
    sign->setText(signstr);
}

void FriendWidget::choose()
{
    this->resize(275, 50);
    photo->resize(40, 40);
    photo->move(5, 5);
    photo->setScaledContents(true);
    photo->setPixmap(photopix);

    name->resize(100, 20);
    name->move(50, 5);
    name->setText(namestr);

    sign->resize(100, 20);
    sign->move(50, 25);
    sign->setText(signstr);
}

void FriendWidget::cancel_choose()
{
    init();
}
