#include "graph.h"
#include <QStringList>
#include <QApplication>
#include <QPainterPath>
#include "math.h"
#define pi 3.1415926
#define SIZE 16

TGraph::TGraph()
{
    this->adjMat = TMatrix<int>(2, 2);
}

int TGraph::getSizeAdjMat()
{
    return this->adjMat.getRowsMatrix();
}

int TGraph::elementAt(int i, int j)
{
    return this->adjMat.valueAt(i, j);
}
void TGraph::setAdjMat(const TMatrix<int> &mat)
{
    this->adjMat = mat;
}

void TGraph::drawGraph(QPainter* p, QRect window)
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
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (i == j && this->adjMat.valueAt(i, j))
            {
                qreal phi = i*qstep;
                drawCurvedEdge(p, points[i], phi, qsize);
            }
            else if (this->adjMat.valueAt(i, j))
                drawStraightEdge(p, points[i], points[j], qsize);
        }
        p->setBrush(Qt::NoBrush);
        p->drawEllipse(points[i], qsize, qsize);
        p->drawText(QRectF(points[i].x()-qsize,points[i].y()-qsize, 2.0*qsize,2.0*qsize),
                    QString().setNum(i+1), QTextOption(Qt::AlignCenter));
    }
    delete[] points;
}


void TGraph::drawStraightEdge(QPainter* p, const QPointF &point1, const QPointF &point2, qreal qsize)
{
    // Вычислить угол между линией и горизонтальной осью
    qreal angle = std::atan2(point2.y() - point1.y(), point2.x() - point1.x());
    qreal dx = qsize*cos(angle);
    qreal dy = qsize*sin(angle);
    qreal arrowSize = SIZE/2;
    QPointF startP, endP, arrowP1, arrowP2;
    startP = QPointF(point1.x() + dx, point1.y() + dy);
    endP = QPointF(point2.x() - dx, point2.y() - dy);
    p->drawLine(startP, endP);
    arrowP1 = endP - QPointF(sin(-angle + pi/3) * arrowSize,
                             cos(-angle + pi/3) * arrowSize);
    arrowP2 = endP - QPointF(sin(-angle + pi - pi/3) * arrowSize,
                             cos(-angle + pi - pi/3) * arrowSize);
    QPolygonF arrowHead;
    arrowHead << endP << arrowP1 << arrowP2;
    p->setBrush(Qt::black);
    p->drawPolygon(arrowHead);
}

void TGraph::drawCurvedEdge(QPainter* p, const QPointF &nodeCenter, qreal phi, qreal qsize)
{

    QPointF startP(nodeCenter.x() + qsize*sin(phi - pi/3), nodeCenter.y() - qsize*cos(phi - pi/3));
    QPointF endP(nodeCenter.x() + qsize*sin(phi + pi/3), nodeCenter.y() - qsize*cos(phi + pi/3));
    QPointF midP(nodeCenter.x() + qsize*sin(phi), nodeCenter.y() - qsize*cos(phi));
    QPointF controlP(midP.x() + 2*qsize*sin(phi), midP.y() - 2*qsize*cos(phi));
    QPainterPath path;
    path.moveTo(startP);
    path.quadTo(controlP, endP);
    p->setBrush(Qt::NoBrush);
    p->drawPath(path);
    QPolygonF arrowHead;
    qreal arrowSize = SIZE/2;
    QPointF arrowP1 = path.pointAtPercent(0.95);
    qreal angle = std::atan2(-controlP.y() + arrowP1.y(), controlP.x() - arrowP1.x());
    arrowHead << arrowP1
              << QPointF(arrowP1.x() + arrowSize * sin(angle + pi / 3),
                         arrowP1.y() + arrowSize * cos(angle + pi / 3))
              << QPointF(arrowP1.x() + arrowSize * sin(angle + pi - pi / 3),
                         arrowP1.y() + arrowSize * cos(angle + pi - pi / 3));

    p->setBrush(Qt::black);
    p->drawPolygon(arrowHead);
}
