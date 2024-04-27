#ifndef TGRAPH_H
#define TGRAPH_H
#include <math.h>
#include "matrix.h"
#include <QPainter>

#include <QObject>

class TGraph : public QObject
{
    Q_OBJECT
    int count;
    TMatrix<qint16> matrix;
public:
    TGraph(QObject *parent = nullptr);
    TGraph(TMatrix<qint16>, QObject *parent = nullptr);
    virtual void draw(QPainter*,QRect);
    int getCount();
    void setCount(int);
    TMatrix<qint16> getMatrix();
    void setMatrix(TMatrix<qint16>);
public slots:
    void changeMatrix(TMatrix<qint16>);
};

#endif // TGRAPH_H
