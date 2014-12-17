#include "headbutton.h"

HeadButton::HeadButton(QWidget *parent) :
    QPushButton(parent)
{
}

HeadButton::HeadButton(QPixmap icon_not, QPixmap icon, QWidget *parent) :
    QPushButton(parent)
{
    this->setFlat(true);
    this->setStyleSheet("QPushButton{border:none;}");
    this->setCheckable(true);

    this->resize(50, 30);
    icon_not_chosen = new QPixmap();
    *icon_not_chosen = icon_not;
    icon_chosen = new QPixmap();
    *icon_chosen = icon;
    flag = 0;
    not_chosen();
}

void HeadButton::not_chosen()
{
    this->setIcon(QIcon(*icon_not_chosen));
    this->setIconSize(QSize(50, 30));
}

void HeadButton::chosen()
{
    this->setFlat(true);
    this->setIcon(QIcon(*icon_chosen));
    this->setIconSize(QSize(50, 30));
}

void HeadButton::refresh()
{
    if(this->isChecked())
        chosen();
    else
        not_chosen();
}
