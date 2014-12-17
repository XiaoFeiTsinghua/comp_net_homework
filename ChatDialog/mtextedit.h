#ifndef MTEXTEDIT_H
#define MTEXTEDIT_H
#include <QWidget>
#include <QKeyEvent>
#include <QTextEdit>

class mTextEdit:public QTextEdit
{
    Q_OBJECT
public:
    explicit mTextEdit(QWidget *parent = 0);
   // QString msg_tobesent;

    void keyPressEvent(QKeyEvent *e);

signals:
    void send_text();

};

#endif // MTEXTEDIT_H
