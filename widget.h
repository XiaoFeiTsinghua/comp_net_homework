#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSize>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVector>
#include "choosewidget.h"
#include <QtNetwork>
#include <QMap>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setUsername(QString name);
    void init();
    ~Widget();

private slots:
    void receive_connection();
    void wait_for_id();
    void read_tcp();
    void new_conn(QString id, QString ip);
    void send_msg(QString id, QString msg);

signals:
    void rec_msg(QString id, QString msg);

private:
    Ui::Widget *ui;
    QSystemTrayIcon *trayIcon;
    QListWidget *list;
    QTreeWidget *tree;
    ChooseWidget *choosew;
    void createTray();
    QString username;

    QTcpServer* chat_server;
    QMap<QString, QTcpSocket*> socket_map;
    QTcpSocket* waiting_soc;
};

#endif // WIDGET_H
