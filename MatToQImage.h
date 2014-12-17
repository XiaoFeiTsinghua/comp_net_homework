
#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include <QtGui>
#include <QDebug>
#include <opencv.hpp>

using namespace cv;

QImage MatToQImage(const Mat&);

#endif
