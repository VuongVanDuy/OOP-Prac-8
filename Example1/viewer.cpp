#include "viewer.h"

TViewer::TViewer(TDeriveSample* f, QWidget *parent)
    : QWidget(parent)
{
    s = f;
    setFixedSize(400,400);
}

TViewer::~TViewer()
{

}

void TViewer::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p,rect(),Qt::green);
    p.end();
}

void TViewer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  s->newEvent(false);
    if (event->button() == Qt::RightButton) s->newEvent(true);
    update();
}
