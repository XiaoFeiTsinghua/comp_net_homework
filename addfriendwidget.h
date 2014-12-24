#ifndef ADDFRIENDWIDGET_H
#define ADDFRIENDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include "database.h"
class AddfriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddfriendWidget(QWidget *parent = 0);
    AddfriendWidget(QString name, QWidget *parent = 0);
    void init();
private:
    QLabel *nameLabel, *studentnumLabel, *groupLabel, *signLabel;
    QLineEdit *nameEdit, *studentnumEdit, *signEdit;
    QComboBox *groupBox, *photoBox;
    QPushButton *configButton;
    QString username;

signals:
    void infoSend(friendinfo fi);
public slots:
    void emit_signal_infosend();

};

#endif // ADDFRIENDWIDGET_H
