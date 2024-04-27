#include "graph.h"

TGraph::TGraph(QObject *parent) : QObject(parent)
{
    count = 2;
    QVector<qint16> row1, row2;
    row1.append(0);
    row1.append(1);
    row2.append(0);
    row2.append(0);

    QVector<QVector<qint16>> m;
    m.append(row1);
    m.append(row2);

    TMatrix<qint16> newMatrix(count, count, m);

    matrix = newMatrix;
}

TGraph::TGraph(TMatrix<qint16> m, QObject *parent) : QObject(parent)
{
    matrix = m;
    count = matrix.getX();
}

int TGraph::getCount()
{
    return count;
}

void TGraph::setCount(int n)
{
    count = n;
}

TMatrix<qint16> TGraph::getMatrix()
{
    return matrix;
}

void TGraph::setMatrix(TMatrix<qint16> m)
{
    matrix = m;
}

void TGraph::changeMatrix(TMatrix<qint16> m)
{
    count = m.getX();
    matrix = m;
}

void TGraph::draw(QPainter *p, QRect r)
{
    qreal cw = 0.5*r.width();
    qreal ch = 0.5*r.height();
    qreal cr = 0.8*(cw>ch?ch:cw);
    qreal a = 2.0*M_PI/count;

    QPointF *t = new QPointF[count];
    for (int i=0; i<count; i++)
    {
        t[i] = QPointF(cw +cr*sin(i*a),ch - cr*cos(i*a));
    }

    QPen pen = QPen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    p->setPen(pen);

    QFont font;
    qreal cf = 0.15*cr;
    font.setPointSize(cf);
    font.setBold(true);
    p->setFont(font);

    qreal radius = 0.1*(cw>ch?ch:cw);
    qreal edge = sqrt(2)*radius;



    qreal arrowSize = 0.6*radius;
    for (int i=0; i<count; i++)
    {
        for (int j=0; j<count; j++)
        {
            if (matrix.valueAt(i,j)==1)
            {
                if (i!=j)
                {
                    QLineF line(t[i],t[j]);
                    qreal angle = atan2(line.dy(),line.dx());

                    line.setP1(line.p1()+QPoint(radius*cos(angle),radius*sin(angle)));
                    line.setP2(line.p2()+QPoint(-radius*cos(angle),-radius*sin(angle)));

                    QPointF arrowP1 = line.p2() - QPoint(cos(angle+M_PI/6)*arrowSize,sin(angle+M_PI/6)*arrowSize);
                    QPointF arrowP2 = line.p2() - QPoint(cos(angle-M_PI/6)*arrowSize,sin(angle-M_PI/6)*arrowSize);

                    QPolygonF arrow;
                    arrow << line.p2() << arrowP1 << arrowP2;

                    p->drawLine(line);
                    p->setBrush(QBrush(Qt::black));
                    p->drawPolygon(arrow);
                }
                else
                {
                    qreal r0 = 0.85*radius;
                    p->setBrush(QBrush(Qt::NoBrush));
                    QLineF line(t[i], r.center());
                    qreal angle = atan2(line.dy(),-line.dx());

                    qreal d = line.length();

                    line.setP1(line.p1()+QPoint(r0*cos(angle),-r0*sin(angle)));
                    p->drawEllipse(line.p1(),r0,r0);

                    qreal l = radius*radius/(2*r0);
                    qreal h = sqrt(radius*radius - l*l);
                    qreal k = sqrt(h*h+(d+l)*(d+l));
                    qreal w = atan2(h,d+l);

                    QPointF o = r.center() + QPoint(cos(w+angle)*k,-sin(w+angle)*k);

                    QPointF arrowP1 = o + QPoint(cos(angle+w+M_PI/6)*arrowSize,-sin(angle+w+M_PI/6)*arrowSize);
                    QPointF arrowP2 = o + QPoint(cos(angle+w-M_PI/6)*arrowSize,-sin(angle+w-M_PI/6)*arrowSize);

                    QPolygonF arrow;
                    arrow << o << arrowP1 << arrowP2;
                    p->setBrush(QBrush(Qt::black));
                    p->drawPolygon(arrow);
                }
            }
        }
    }



    p->setBrush(QBrush(Qt::white));
    for (int i=0; i<count; i++)
    {
        p->drawEllipse(t[i],radius,radius);
        p->drawText(QRectF(t[i].x()-edge/2,t[i].y()-edge/2,edge,edge),
                    QString().setNum(i+1),
                    QTextOption(Qt::AlignCenter));
    }
    delete[] t;
}
