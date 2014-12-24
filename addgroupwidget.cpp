#include "addgroupwidget.h"

AddgroupWidget::AddgroupWidget(QWidget *parent) :
    QWidget(parent)
{
}

AddgroupWidget::AddgroupWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    username = name;
    nameEdit = new QLineEdit(this);
    configButton = new QPushButton(this);

    connect(configButton, &QPushButton::clicked, this, &AddgroupWidget::emit_signal_infosend);

    init();
}

void AddgroupWidget::init()
{
    nameEdit->resize(100, 30);
    nameEdit->move(50, 50);

    configButton->setText("确定");
    configButton->move(50, 100);
}

void AddgroupWidget::emit_signal_infosend()
{
    groupinfo gi;
    gi.id = getGroupsnum(username) + 1;
    gi.name = nameEdit->text();
    gi.friendsingroup = 0;
    newGroup(username, gi);
    emit infoSend(gi);
    close();
}
