#include "functionwidget.h"

FunctionWidget::FunctionWidget(QWidget *parent) :
    QWidget(parent)
{
}

FunctionWidget::FunctionWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    username = name;
    addfriendButton = new QPushButton(this);
    addgroupButton = new QPushButton(this);
    addfriendw = new AddfriendWidget(username);
    addgroupw = new AddgroupWidget(username);

    addfriendButton->resize(50, 30);
    addfriendButton->move(20, 0);
    addfriendButton->setText("查找");

    addgroupButton->resize(50, 30);
    addgroupButton->move(80, 0);
    addgroupButton->setText("添加分组");

    connect(addfriendButton, &QPushButton::clicked, this, &FunctionWidget::addfriend);
    connect(addfriendw, &AddfriendWidget::infoSend, this, &FunctionWidget::friendinfoRecv);
    connect(addgroupButton, &QPushButton::clicked, this, &FunctionWidget::addgroup);
    connect(addgroupw, &AddgroupWidget::infoSend, this, &FunctionWidget::groupinfoRecv);
}

void FunctionWidget::addfriend()
{
    qDebug()<<"add";
    addfriendw->show();
}

void FunctionWidget::friendinfoRecv(friendinfo fi)
{
    emit added();
    qDebug() << fi.id;
}

void FunctionWidget::addgroup()
{
    qDebug()<<"addgroup";
    addgroupw->show();
}

void FunctionWidget::groupinfoRecv(groupinfo gi)
{
    emit added();
    qDebug() << gi.id << "miao";
}
