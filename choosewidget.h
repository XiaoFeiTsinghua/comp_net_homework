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
#include "headbutton.h"
#include "friendwidget.h"

class ChooseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseWidget(QWidget *parent = 0);
    void init();
    void x_chosen();
    void refresh();
private:
    HeadButton *chats;
    HeadButton *friends;
    HeadButton *groups;
    QButtonGroup *choice;

    QTreeWidget *friendstree;

    int num_of_friends = 6;
signals:
    void new_conn(QString id, QString ip);
    void send_msg(QString id, QString msg);

public slots:
    void double_clicked(QTreeWidgetItem* item, int column);
    void rec_msg(QString id, QString msg);
};

#endif // CHOOSEWIDGET_H
