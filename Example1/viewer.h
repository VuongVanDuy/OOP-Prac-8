#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QMouseEvent>
#include "derivesample.h"

class TViewer : public QWidget
{
    Q_OBJECT

    TDeriveSample* s;
public:
    TViewer(TDeriveSample*,QWidget *parent = 0);
    ~TViewer();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif // VIEWER_H
