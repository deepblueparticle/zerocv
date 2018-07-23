#include <QCoreApplication>
#include "camserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CamServer cs(&a);

    return a.exec();
}
