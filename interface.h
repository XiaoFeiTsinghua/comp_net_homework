#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class interface;
}

class interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    ~interface();

    QTcpSocket *log;

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_login_clicked();

    void on_logout_clicked();

    void on_add_friends_clicked();

private:
    Ui::interface *ui;
    void con();
};

#endif // INTERFACE_H
