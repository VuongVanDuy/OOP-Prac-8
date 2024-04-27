#ifndef TGRAPHACTIVE_H
#define TGRAPHACTIVE_H

#include <QObject>
#include "graph.h"

class TGraphActive : public TGraph
{
    Q_OBJECT
    int nodeActive;
public:
    TGraphActive();
    TGraphActive(TMatrix<qint16> m);
    void draw(QPainter*,QRect);
    int getNodeActive();
    void newEvent(int);
signals:
    void changeNodeActive(int);
public slots:
    void changeActive(int);
};

#endif // TGRAPHACTIVE_H
