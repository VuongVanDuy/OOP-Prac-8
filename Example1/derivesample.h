#ifndef DERIVESAMPLE_H
#define DERIVESAMPLE_H

#include "sample.h"

class TDeriveSample : public TSample
{
    int active;
public:
    TDeriveSample(int);
    void draw(QPainter*,QRect,QColor);
    void newEvent(bool);
};

#endif // DERIVESAMPLE_H
