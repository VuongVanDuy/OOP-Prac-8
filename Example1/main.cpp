#include <QApplication>
#include "viewer.h"
#include "derivesample.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TDeriveSample s(8);
    TViewer w(&s);
    w.show();

    return a.exec();
}
