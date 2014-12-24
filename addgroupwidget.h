#ifndef ADDGROUPWIDGET_H
#define ADDGROUPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "database.h"

class AddgroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddgroupWidget(QWidget *parent = 0);
    AddgroupWidget(QString name, QWidget *parent = 0);
    void init();
private:
    QPushButton *configButton;
    QLineEdit *nameEdit;
    QString username;
signals:
    void infoSend(groupinfo gi);
public slots:
    void emit_signal_infosend();
};

#endif // ADDGROUPWIDGET_H
