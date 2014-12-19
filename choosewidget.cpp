#include "choosewidget.h"
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
#include "chatdialog.h"

ChooseWidget::ChooseWidget(QWidget *parent) :
    QWidget(parent)
{

    chats = new HeadButton(QPixmap(":/image/chats_not_chosen"), QPixmap(":/image/chats_chosen"), this);
    friends = new HeadButton(QPixmap(":/image/friends_not_chosen"), QPixmap(":/image/friends_chosen"), this);
    groups = new HeadButton(QPixmap(":/image/groups_not_chosen"), QPixmap(":/image/groups_chosen"), this);
    choice = new QButtonGroup(this);
    friendstree = new QTreeWidget(this);
    init();
    connect(chats, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friends, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(groups, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friendstree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(double_clicked(QTreeWidgetItem*,int)));
}

void ChooseWidget::double_clicked(QTreeWidgetItem *item, int column)
{
    //QMessageBox::information(this, "check it out!", QString(column));
    FriendWidget* f = (FriendWidget*)friendstree->itemWidget(item, column);
    QTcpSocket* check = new QTcpSocket(this);
    check->connectToHost("166.111.180.60", 8000);
    QString st = "q" + f->id;
    QByteArray bt;
    bt.append(st);
    check->write(bt);
    if (!check->waitForReadyRead(300))
    {

    }
    bt = check->readAll();
    if (bt == "n")
    {
        QMessageBox::information(this, tr("登录信息"), tr("查无此人！"));
    }
    else
    {
        ChatDialog* chat = new ChatDialog(f->id);
        chat->show();
        connect(chat, SIGNAL(send_msg(QString,QString)), this, SLOT(from_down_msg(QString, QString)));
        connect(this, SIGNAL(to_down_msg(QString,QString)), chat, SLOT(rec_msg(QString,QString)));
        emit(new_conn(f->id, QString(bt)));
    }
}

void ChooseWidget::from_up_msg(QString id, QString msg)
{
    emit to_down_msg(id, msg);
}

void ChooseWidget::from_down_msg(QString id, QString msg)
{
    emit to_up_msg(id, msg);
}

void ChooseWidget::init()
{
    chats->move(0, 0);
    friends->move(60, 0);
    groups->move(120, 0);
    choice->addButton(chats, 0);
    choice->addButton(friends, 1);
    choice->addButton(groups, 2);

    friendstree->move(0, 30);
    friendstree->resize(275, 200);
    friendstree->setHeaderHidden(true);
    friendstree->setFrameStyle(QFrame::NoFrame);

    QStringList str;
    str << QObject::tr("需要膜拜的人");
    QTreeWidgetItem *parentitem = new QTreeWidgetItem(friendstree, str);

    for(int i = 0; i < num_of_friends-1; i++)
    {
        FriendWidget *f = new FriendWidget("2012011490", QPixmap(":/image/photo_gjq"), "高大神", "I'm doge!", this);
        QTreeWidgetItem *childitem = new QTreeWidgetItem(parentitem);
        childitem->setSizeHint(0, QSize(200, 30));
        friendstree->setItemWidget(childitem, 0, f);
    }
    FriendWidget *f = new FriendWidget("2012011489", QPixmap(":/image/photo_gjq"), "测试用账号", "I'm bzdy!", this);
    QTreeWidgetItem *childitem = new QTreeWidgetItem(parentitem);
    childitem->setSizeHint(0, QSize(200, 30));
    friendstree->setItemWidget(childitem, 0, f);

}


void ChooseWidget::x_chosen()
{
    int id = choice->checkedId();
    if(choice->button(id)->isChecked() == false)
        choice->button(id)->isChecked() == true;
    for(int i = 0; ((i < 3) && (i != id)); i++)
        choice->button(i)->isChecked() == false;
    refresh();
}


void ChooseWidget::refresh()
{
    chats->refresh();
    friends->refresh();
    groups->refresh();
    int id = choice->checkedId();
    switch (id)
    {
    case 0:
        friendstree->setVisible(true);
        break;
    case 1:
        friendstree->setVisible(false);
        break;
    case 2:
        friendstree->setVisible(false);
    }
    qDebug()<< "in chooseWidget::refresh() " << choice->checkedId();
}
