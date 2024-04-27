#include "graph_active.h"
#include "math.h"
#include <vector>
#include <QDebug>
#define pi 3.1415926
#define SIZE 16

TGraphActive::TGraphActive()
{
    nodeActive = 2;
}

void TGraphActive::setNodeActive(int nodeActive)
{
    this->nodeActive = nodeActive;
}

int TGraphActive::getNodeActive()
{
    return nodeActive;
}

int TGraphActive::getNumEvents()
{
    return this->adjMat.getColsMatrix();
}

void TGraphActive::drawGraph(QPainter* p, QRect window)
{
    int count = this->adjMat.getRowsMatrix();
    qreal qsize = SIZE;
    if (count > 10 && count <= 60) qsize = SIZE/2;
    else if (count > 60) qsize = 5;

    qreal centerX = window.width()/2;
    qreal centerY = window.height()/2;
    qreal circleR = (centerX > centerY ? centerY : centerX) - qsize - 50 ;
    qreal qstep = 2.0*pi/count;
    QFont font; //шрифт текста /ниже настройка
    font.setFamily("Consalas");
    font.setPointSize(qsize); //
    p->setFont(font); //установка в пейнтер
    p->setPen(Qt::black);
    p->setRenderHint(QPainter::Antialiasing, true);

    QPointF *points = new QPointF[count];
    qreal coordX, coordY;

    for (int i = 0; i < count; i++)
    {
        coordX = centerX + circleR*sin(i*qstep);
        coordY = centerY - circleR*cos(i*qstep);
        points[i] = QPointF(coordX, coordY);
    }
    std::vector<int> arrIndex;
    int index;
    int cols = getNumEvents();
    for (int i = 0; i < count; i++)
    {
        arrIndex.clear();
        for (int j = 0; j < cols; j++)
        {
            index = this->adjMat.valueAt(i, j);
            bool is_present = std::find(arrIndex.begin(), arrIndex.end(), index) != arrIndex.end();
            if (!is_present) arrIndex.push_back(index);
            else continue;
            if (i == index - 1)
            {
                qreal phi = i*qstep;
                drawCurvedEdge(p, points[i], phi, qsize);
            }
            else if (index > 0)
                drawStraightEdge(p, points[i], points[index - 1], qsize);
        }
        if (i + 1 == this->nodeActive)
        {
            p->setBrush(Qt::red);
            p->drawEllipse(points[i], qsize, qsize);
            p->setBrush(Qt::NoBrush);
        }
        p->setBrush(Qt::NoBrush);
        p->drawEllipse(points[i], qsize, qsize);
        p->drawText(QRectF(points[i].x()-qsize,points[i].y()-qsize, 2.0*qsize,2.0*qsize),
                    QString().setNum(i+1), QTextOption(Qt::AlignCenter));
    }
    delete[] points;
}
