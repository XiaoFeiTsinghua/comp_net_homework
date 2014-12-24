#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include "addfriendwidget.h"
#include "addgroupwidget.h"

class FunctionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionWidget(QWidget *parent = 0);
    FunctionWidget(QString username, QWidget *parent = 0);

private:
    QString username;
    QPushButton *addfriendButton, *addgroupButton;

    AddfriendWidget *addfriendw;
    AddgroupWidget *addgroupw;

signals:
    void added();//已经添加，需要刷新
public slots:
    void addfriend();
    void addgroup();
    void friendinfoRecv(friendinfo fi); //消息接收 槽函数
    void groupinfoRecv(groupinfo gi); //消息接收 槽函数

};

#endif // FUNCTIONWIDGET_H
