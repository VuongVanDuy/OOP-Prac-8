#include "interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TGraphActive *graph = new TGraphActive();
    TInterface w(graph);
    w.show();
    return a.exec();
}
