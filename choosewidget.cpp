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
    deletefriendAction = new QAction(tr("删除好友"), this);
    deletegroupAction = new QAction(tr("删除分组"), this);
}

ChooseWidget::ChooseWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    username = name;
    chats = new HeadButton(QPixmap(":/image/chats_not_chosen"), QPixmap(":/image/chats_chosen"), this);
    friends = new HeadButton(QPixmap(":/image/friends_not_chosen"), QPixmap(":/image/friends_chosen"), this);
    groups = new HeadButton(QPixmap(":/image/groups_not_chosen"), QPixmap(":/image/groups_chosen"), this);
    choice = new QButtonGroup(this);
    friendstree = new QTreeWidget(this);
    friendstree->setContextMenuPolicy(Qt::CustomContextMenu);

    deletefriendAction = new QAction(tr("删除好友"), this);
    deletegroupAction = new QAction(tr("删除分组"), this);
    connect(deletefriendAction, &QAction::triggered, this, &ChooseWidget::delete_friend);
    connect(deletegroupAction, &QAction::triggered, this, &ChooseWidget::delete_group);

    connect(chats, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friends, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(groups, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friendstree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(double_clicked(QTreeWidgetItem*,int)));
    connect(friendstree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(clicked(QTreeWidgetItem*,int)));
    connect(friendstree, &QTreeWidget::customContextMenuRequested, this, &ChooseWidget::show_deletefriend_menu);

    init();
    init_friends();
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
    friendstree->resize(275, 500);
    friendstree->setHeaderHidden(true);
    friendstree->setFrameStyle(QFrame::NoFrame);
}

void ChooseWidget::init_friends()
{
    num_of_friends = getFriendsnum(username);
    num_of_groups = getGroupsnum(username);
    roots.resize(num_of_groups);
    rootscontent.resize(num_of_groups);
    childs.resize(num_of_friends);
    childscontent.resize(num_of_friends);
    for(int i = 0; i < num_of_groups; i++)
    {
        groupinfo gi = getGroupinfo(username, i + 1);
        rootscontent[i] = new GroupWidget(gi.id, gi.name, gi.friendsingroup, this);
        roots[i] = new QTreeWidgetItem(friendstree);
        roots[i]->setSizeHint(0, QSize(200, 20));
        friendstree->setItemWidget(roots[i], 0, rootscontent[i]);
    }

    for(int i = 0; i < num_of_friends; i++)
    {
        friendinfo fi = getFriendinfo(username, i + 1);
        QString photofile = "./" + username + "/friendsphoto/" + fi.photo;
        childscontent[i] = new FriendWidget(fi.id, fi.belongto, fi.studentnum, QPixmap(photofile), fi.name, fi.sign, this);
        childs[i] = new QTreeWidgetItem(roots[fi.belongto - 1]);
        childs[i]->setSizeHint(0, QSize(200, 30));
        friendstree->setItemWidget(childs[i], 0, childscontent[i]);
    }
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
        friendstree->setVisible(false);
        break;
    case 1:
        friendstree->setVisible(true);
        break;
    case 2:
        friendstree->setVisible(false);
        break;
    }
    qDebug()<< "in chooseWidget::refresh() " << choice->checkedId();
}

void ChooseWidget::refresh_friends()
{
    for(int i = 0; i < childs.size(); i++)
    {
        //qDebug()<<i;
        delete childs[i];
        childs[i] = NULL;
    }
    childs.clear();

    for(int i = 0; i < childscontent.size(); i++)
    {
        //qDebug()<<i;
        delete childscontent[i];
        childscontent[i] = NULL;
    }
    childscontent.clear();

    for(int i = 0; i < roots.size(); i++)
    {
        //qDebug()<<i;
        delete roots[i];
        roots[i] = NULL;
    }
    roots.clear();

    for(int i = 0; i < roots.size(); i++)
    {
        //qDebug()<<i;
        delete rootscontent[i];
        rootscontent[i] = NULL;
    }
    rootscontent.clear();

    init_friends();
}

void ChooseWidget::clicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent)
        return;
   qDebug() << "clicked";
   for(int i = 0; i < num_of_friends; i++)
   {
       childscontent[i]->cancel_choose();
       childs[i]->setSizeHint(0, childscontent[i]->size());
   }
   FriendWidget* f = (FriendWidget*)friendstree->itemWidget(item, column);
   f->choose();
   item->setSizeHint(0, f->size());
   for(int i = 0; i < num_of_groups; i++)
   {
       bool state = roots[i]->isExpanded();
       if(state == true)
       {
           roots[i]->setExpanded(false);
           roots[i]->setExpanded(true);
       }
   }
}

void ChooseWidget::double_clicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent)
    {
        if(item->isExpanded() == false)
        {
            for(int i = 0; i < num_of_friends; i++)
            {
                if(childs[i]->parent() == item)
                childscontent[i]->cancel_choose();
                childs[i]->setSizeHint(0, childscontent[i]->size());
            }
        }
        return;
    }
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
        ChatDialog* chat = new ChatDialog(f->studentnum);
        chat->show();
        connect(chat, SIGNAL(send_msg(QString,QString)), this, SLOT(from_down_msg(QString, QString)));
        connect(this, SIGNAL(to_down_msg(QString,QString)), chat, SLOT(rec_msg(QString,QString)));
        emit(new_conn(f->studentnum, QString(bt)));
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

void ChooseWidget::show_deletefriend_menu(QPoint pos)
{
    QTreeWidgetItem* curItem=friendstree->itemAt(pos);  //获取当前被点击的节点

    if(curItem==NULL)
        return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    QTreeWidgetItem *parent = curItem->parent();
    QMenu *menu=new QMenu(this);
    if(NULL==parent)        //右键是父节点
    {
        GroupWidget *g = (GroupWidget*)friendstree->itemWidget(curItem, 0);
        qDebug()<<g->id;
        group_to_delete = g->id;
        if(group_to_delete == 1)
            return;
        menu->addAction(deletegroupAction); //添加菜单项1
    }
    else
    {
        FriendWidget *f = (FriendWidget*)friendstree->itemWidget(curItem, 0);
        qDebug()<<f->id;
        friend_to_delete = f->id;
        menu->addAction(deletefriendAction); //添加菜单项1
    }
    QCursor cur=this->cursor();
    menu->exec(cur.pos()); //关联到光标
}


void ChooseWidget::delete_friend()
{
    qDebug()<<"deletefriend";
    deleteFriend(username, friend_to_delete);
    refresh_friends();
}

void ChooseWidget::delete_group()
{
    qDebug()<<"deletegroup";
    deleteGroup(username, group_to_delete);
    refresh_friends();
}
