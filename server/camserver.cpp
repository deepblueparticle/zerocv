#include "camserver.h"

using namespace cv;
using namespace std;
using namespace zmq;

CamServer::CamServer(QObject *parent = 0) : QObject(parent), context(1), socket(context, ZMQ_REP)
{
    socket.bind("tcp://*:5555");

    cout << "Capture from the camera" << endl;

    capture.open(0);
    if(!capture.isOpened() == true)
    {
        cout<<"failed to open"<<endl;
        return;
    }

    int captureWidth = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
    int captureHeight = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

    printf("Video open successful in (width=%d, height=%d)! \n", captureWidth, captureHeight);
    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processingImage()));
    tmrTimer->start();
}

void CamServer::processingImage()
{
    Mat img_src;
    captureSuccess = capture.read(img_src);

    if(captureSuccess)
    {
        img_src.copyTo(img_show);
    }
    else
    {
        cout<<"Unable to acquire image frame!"<<endl;
        return;
    }

    // create the message container
    zmq::message_t request;

    if(socket.recv(&request, ZMQ_DONTWAIT))
    {
        printf("Received request.... \n");

        if(captureSuccess)
        {
            size_t framesize = img_src.step[0] * img_src.rows;
            socket.send(img_show.data, framesize);
        }
    }
}
