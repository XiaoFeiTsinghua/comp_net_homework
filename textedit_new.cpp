#include "textedit_new.h"

TextEdit_new::TextEdit_new(QWidget *parent) :
    QTextEdit(parent)
{
}

void TextEdit_new::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        emit send_text();
    }
    else
        QTextEdit::keyPressEvent(e);
}
