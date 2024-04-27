#ifndef TGRAPHACTIVE_H
#define TGRAPHACTIVE_H
#include "graph.h"

class TGraphActive : public TGraph
{
    int nodeActive;
public:
    TGraphActive();
    void setNodeActive(int);
    int getNodeActive();
    int getNumEvents();
    void drawGraph(QPainter*, QRect);
};

#endif // TGRAPHACTIVE_H
