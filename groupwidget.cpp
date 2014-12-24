#include "groupwidget.h"

GroupWidget::GroupWidget(QWidget *parent) :
    QWidget(parent)
{
}
GroupWidget::GroupWidget(int id, QString n, int f, QWidget *parent) :
    QWidget(parent), id(id)
{
    name = n;
    friendsingroup = f;
    nameLabel = new QLabel(this);
    init();
}

void GroupWidget::init()
{
    nameLabel->move(0, 0);
    nameLabel->setText(name);
}

