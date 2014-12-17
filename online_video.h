#ifndef ONLINE_VIDEO_H
#define ONLINE_VIDEO_H

#include <QWidget>
#include <QtNetwork>
#include <opencv.hpp>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

using namespace cv;

namespace Ui {
class online_video;
}

class online_video : public QWidget
{
    Q_OBJECT

public:
    explicit online_video(QString server_address, QWidget *parent = 0);
    ~online_video();


private slots:
    void UpdateFrame();
    void readPendingDatagrams();

protected:
    void closeEvent();

private:
    Ui::online_video *ui;
    VideoCapture* cap;
    Mat frame;
    QTimer* timer;
    QUdpSocket* sender;
    QUdpSocket* receiver;
    int count=  0;
    QString server_address;
};

#endif // ONLINE_VIDEO_H
