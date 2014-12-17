#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>

class FriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FriendWidget(QWidget *parent = 0);
    FriendWidget(QString id, QPixmap p, QString n, QString s, QWidget *parent = 0);
    void init(QPixmap p, QString n, QString s);

    QString id;

signals:

public slots:
private:
    QLabel *photo;
    QLabel *name;
    QLabel *sign;
};

#endif // FRIENDWIDGET_H
