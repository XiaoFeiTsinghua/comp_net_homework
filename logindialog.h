#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <QPoint>
#include <QMouseEvent>
#include <QPixmap>
#include <QIcon>
#include <QtCore/QCoreApplication>
#include <QtSql>
#include <QPainter>
#include <QBitmap>
#include <QAxWidget>
#include <QtGui>
#include "database.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QDialog *parent = 0);
    void init_userCombo();
    void init_keyEdit();
    QString getUsername();

private:
    //QAxWidget *flash;
    QLabel *logoLabel, *photoLabel;
    QCheckBox *autologCheck, *rememberCheck;
    QComboBox *userCombo;
    QLineEdit *keyEdit;
    QPushButton *loginButton, *exitButton, *minButton;
    QPoint dPos;
    bool ismousepressed;

    QString username;

    QTcpSocket *log;
    void con();
    void beautify();
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    bool inButton(QPushButton *push, QPoint p);
    void on_loginButton_clicked();

signals:

public slots:


};

#endif // LOGINDIALOG_H
