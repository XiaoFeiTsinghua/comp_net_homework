#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include <QTextEdit>
#include <QKeyEvent>
#include<QMessageBox>
#include <QMainWindow>
#include "mtextedit.h"
#include <QtNetwork>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatDialog(QString id, QWidget *parent = 0);
    ~ChatDialog();
    //void msgTxtEdit::keyPressEvent ( QKeyEvent * ev );
    //bool eventFilter(QObject *obj, QKeyEvent * ev);
private slots:
    void on_fontCbx_currentFontChanged(const QFont &f);

    void on_sizeCbx_currentIndexChanged(const QString &arg1);

    void on_sendBtn_clicked();

    void rec_msg(QString id, QString msg);

signals:
    void send_msg(QString id, QString msg);

private:
    Ui::ChatDialog *ui;
    QString msg_tobesent;



    QString id;
};


#endif // CHATDIALOG_H
