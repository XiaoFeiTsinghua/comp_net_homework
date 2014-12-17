#include "mtextedit.h"

mTextEdit::mTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
}


void mTextEdit::keyPressEvent(QKeyEvent *e)
 {
     if(e->key()==Qt::Key_Enter || Qt::Key_Return)
     {
         //if(toPlainText()== "") { QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok); return;}
         emit send_text();
         //msg_tobesent=toPlainText();
         //ui->usrNumLbl->setText(msg_tobesent);
     }
 };
