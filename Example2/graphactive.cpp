#include "graphactive.h"
TGraphActive::TGraphActive() : TGraph()
{
    QVector<qint16> row1, row2;
    row1.append(2);
    row2.append(1);

    QVector<QVector<qint16>> m;
    m.append(row1);
    m.append(row2);

    TMatrix<qint16> newMatrix(2, 1, m);

    setMatrix(newMatrix);
    nodeActive = 1;
}


TGraphActive::TGraphActive(TMatrix<qint16> m)
    :TGraph(m)
{
    nodeActive = 1;
}

void TGraphActive::newEvent(int p)
{
    nodeActive = getMatrix().valueAt(nodeActive-1,p);
    emit changeNodeActive(nodeActive);
}

int TGraphActive::getNodeActive()
{
    return nodeActive;
}

void TGraphActive::changeActive(int n)
{
    nodeActive = n;
}

void TGraphActive::draw(QPainter *p, QRect r)
{
    qreal cw = 0.5*r.width();
    qreal ch = 0.5*r.height();
    qreal cr = 0.8*(cw>ch?ch:cw);
    qreal a = 2.0*M_PI/getCount();

    QPointF *t = new QPointF[getCount()];
    for (int i=0; i<getCount(); i++)
    {
        t[i] = QPointF(cw +cr*sin(i*a),ch - cr*cos(i*a));
    }

    QPen pen = QPen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    p->setPen(pen);

    QFont font;

    qreal radius = 0.1*(cw>ch?ch:cw);
    qreal edge = sqrt(2)*radius;
    qreal cf = 0.15*cr;


    qreal arrowSize = 0.6*radius;

    font.setPointSize(cf*0.5);
    font.setBold(true);
    p->setFont(font);

    for (int i=0; i<getMatrix().getX(); i++)
    {
        for (int j=0; j<getMatrix().getY(); j++)
        {
            int temp = getMatrix().valueAt(i,j);
            if (temp>0)
            {
                int count = 1;
                for (int k=0; k<j; k++)
                    if (temp==getMatrix().valueAt(i,k))
                        count++;

                if (i!=temp-1)
                {
                    QLineF line(t[i],t[temp-1]);
                    qreal angle = atan2(line.dy(),line.dx());

                    line.setP1(line.p1()+QPoint(radius*cos(angle),radius*sin(angle)));
                    line.setP2(line.p2()+QPoint(-radius*cos(angle),-radius*sin(angle)));

                    QPointF m = line.p1() + QPoint(radius*cos(angle),radius*sin(angle))*count;

                    QPointF arrowP1 = line.p2() - QPoint(cos(angle+M_PI/6)*arrowSize,sin(angle+M_PI/6)*arrowSize);
                    QPointF arrowP2 = line.p2() - QPoint(cos(angle-M_PI/6)*arrowSize,sin(angle-M_PI/6)*arrowSize);

                    QPolygonF arrow;
                    arrow << line.p2() << arrowP1 << arrowP2;

                    p->drawLine(line);

                    p->setPen(Qt::blue);
                    p->drawText(QRectF(m.x()-radius/2,m.y()-radius/2,radius,radius),
                                QString().setNum(j+1),
                                QTextOption(Qt::AlignCenter));
                    p->setPen(Qt::black);
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

                    QPointF m = line.p1()+QPoint(r0*cos(angle),-r0*sin(angle))*count*0.75;
                    p->setPen(Qt::blue);
                    p->drawText(QRectF(m.x()-radius/2,m.y()-radius/2,radius,radius),
                                QString().setNum(j+1),
                                QTextOption(Qt::AlignCenter));
                    p->setPen(Qt::black);

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

    font.setPointSize(cf);
    font.setBold(true);
    p->setFont(font);

    p->setBrush(QBrush(Qt::white));
    for (int i=0; i<getMatrix().getX(); i++)
    {
        if (i == nodeActive-1)
        {
            p->setBrush(QBrush(Qt::yellow));
            p->drawEllipse(t[i],radius,radius);
            p->setBrush(QBrush(Qt::white));
        }
        else
            p->drawEllipse(t[i],radius,radius);
        p->drawText(QRectF(t[i].x()-edge/2,t[i].y()-edge/2,edge,edge),
                    QString().setNum(i+1),
                    QTextOption(Qt::AlignCenter));
    }
    delete[] t;
}
