#include "interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TGraphActive g;
    TInterface w(&g);
    w.show();
    return a.exec();
}
