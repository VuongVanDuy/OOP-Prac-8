#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>

class TSample
{
protected:
    int count;
public:
    TSample(int);
    void draw(QPainter*,QRect,QColor);
};

#endif // SAMPLE_H
