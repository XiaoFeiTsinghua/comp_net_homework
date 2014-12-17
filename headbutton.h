#ifndef HEADBUTTON_H
#define HEADBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QSize>

class HeadButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HeadButton(QWidget *parent = 0);
    HeadButton(QPixmap icon_not, QPixmap icon, QWidget *parent = 0);
    void not_chosen();
    void chosen();
    void refresh();
private:
    QPixmap *icon_not_chosen;
    QPixmap *icon_chosen;
    int flag;
signals:

public slots:

};

#endif // HEADBUTTON_H
