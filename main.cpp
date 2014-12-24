#include "widget.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*

    Widget w("2012010526");
    w.show();
*/
    LoginDialog l;
    if(l.exec()==QDialog::Accepted)
    {
        QString name = l.getUsername();
        Widget w(name);
        w.show();
        return a.exec();
    }

    else
        return 0;


    return a.exec();
}
