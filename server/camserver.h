#ifndef CAMSERVER_H
#define CAMSERVER_H

// c or c++
#include <cstdio>
#include <iostream>

//QT
#include <QTimer>

//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

//zeromq
#include <zmq.hpp>


class CamServer : public QObject
{
    Q_OBJECT
public:
    CamServer(QObject *parent);

private:
    cv::VideoCapture capture;
    cv::Mat cvimg, img_show;
    bool captureSuccess;
    QTimer *tmrTimer;
    zmq::context_t context;
    zmq::socket_t socket;

public slots:
    void processingImage();
};

#endif // CAMSERVER_H
