#ifndef TEXTEDIT_NEW_H
#define TEXTEDIT_NEW_H

#include <QTextEdit>
#include <QKeyEvent>

class TextEdit_new : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit_new(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *e);

signals:
    void send_text();
public slots:

};

#endif // TEXTEDIT_NEW_H
