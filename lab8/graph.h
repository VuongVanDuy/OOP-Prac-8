#ifndef TGRAPH_H
#define TGRAPH_H
#include <QPainter>
#include <QPointF>
#include "matrix.h"

class TGraph
{
protected:
    TMatrix<int> adjMat;

public:
    TGraph();
    int getSizeAdjMat();
    int elementAt(int, int);
    void setAdjMat(const TMatrix<int>&);

    virtual void drawGraph(QPainter*,QRect);
    void drawStraightEdge(QPainter*, const QPointF&, const QPointF&, qreal);
    void drawCurvedEdge(QPainter* , const QPointF &, qreal , qreal );
};

#endif // TGRAPH_H
