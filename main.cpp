#include "widget.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    LoginDialog l;
    if(l.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }

    else
        return 0;

    return a.exec();
}
