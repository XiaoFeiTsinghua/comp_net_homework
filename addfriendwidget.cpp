#include "addfriendwidget.h"

AddfriendWidget::AddfriendWidget(QWidget *parent) :
    QWidget(parent)
{
}

AddfriendWidget::AddfriendWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    nameLabel = new QLabel(this);
    studentnumLabel = new QLabel(this);
    groupLabel = new QLabel(this);
    signLabel = new QLabel(this);
    nameEdit = new QLineEdit(this);
    signEdit = new QLineEdit(this);
    studentnumEdit = new QLineEdit(this);
    groupBox = new QComboBox(this);
    photoBox = new QComboBox(this);
    configButton = new QPushButton(this);

    username = name;

    connect(configButton, &QPushButton::clicked, this, &AddfriendWidget::emit_signal_infosend);
    init();
}

void AddfriendWidget::init()
{
    this->resize(400, 300);

    studentnumLabel->setText("学号");
    studentnumLabel->move(50, 50);

    nameLabel->setText("备注名");
    nameLabel->move(50, 100);

    groupLabel->setText("好友分组");
    groupLabel->move(50, 150);

    signLabel->setText("备注");
    signLabel->move(50, 200);

    studentnumEdit->move(100, 50);

    nameEdit->move(100, 100);

    signEdit->move(100, 200);

    groupBox->move(100, 150);
    int num_of_groups = getGroupsnum(username);
    for(int i = 0; i < num_of_groups; i++)
    {
        groupinfo gi = getGroupinfo(username, i + 1);
        groupBox->insertItem(i, gi.name);
    }

    photoBox->move(250, 50);
    for(int i = 0; i < 3; i++)
    {
        QString photopath = ":/image/system_photo" + QString::number(i + 1, 10);
        QString photoname = "系统头像" + QString::number(i + 1, 10);
        photoBox->addItem(QIcon(photopath), photoname);
    }

    configButton->setText("添加好友");
    configButton->move(75, 250);
}

void AddfriendWidget::emit_signal_infosend()
{
    friendinfo fi;
    fi.id = getFriendsnum(username) + 1;
    fi.name = nameEdit->text();
    fi.studentnum = studentnumEdit->text();
    fi.belongto = groupBox->currentIndex() + 1;
    fi.photo = "1";
    fi.sign = signEdit->text();
    newFriend(username, fi);
    emit infoSend(fi);
    close();
}
