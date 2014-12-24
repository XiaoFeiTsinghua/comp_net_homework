#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QContextMenuEvent>
#include <QMenu>
#include <QVector>
#include <QCursor>
#include "database.h"
#include "headbutton.h"
#include "friendwidget.h"
#include "groupwidget.h"

class ChooseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseWidget(QWidget *parent = 0);
    ChooseWidget(QString name, QWidget *parent = 0);
    void init();
    void x_chosen();
    void refresh();
    void refresh_friends();

private:
    HeadButton *chats;
    HeadButton *friends;
    HeadButton *groups;
    QButtonGroup *choice;

    QTreeWidget *friendstree;
    QVector<QTreeWidgetItem*> roots;
    QVector<GroupWidget*> rootscontent;
    QVector<QTreeWidgetItem*> childs;
    QVector<FriendWidget*> childscontent;

    QAction *deletefriendAction;
    QAction *deletegroupAction;

    QString username;
    int num_of_friends;
    int num_of_groups;
    int friend_to_delete;
    int group_to_delete;

signals:
    void new_conn(QString id, QString ip);
    void to_up_msg(QString id, QString msg);
    void to_down_msg(QString id, QString msg);
    void itemClicked(QTreeWidgetItem*,int);

public slots:
    void double_clicked(QTreeWidgetItem* item, int column);
    void clicked(QTreeWidgetItem* item, int column);
    void from_down_msg(QString id, QString msg);
    void from_up_msg(QString id, QString msg);
    void init_friends();
    void show_deletefriend_menu(QPoint pos);
    void delete_friend();
    void delete_group();
};

#endif // CHOOSEWIDGET_H
