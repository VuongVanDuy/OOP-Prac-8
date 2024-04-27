#include "viewwindow.h"

TViewWindow::TViewWindow(QWidget *parent) : QWidget(parent)
{

}

TViewWindow::TViewWindow(TGraphActive* f, QWidget *parent) : QWidget(parent)
{
    g = f;
    setFixedSize(QSize(450,400));

    vb = new QVBoxLayout();

    for (int i=0; i<g->getMatrix().getY(); i++)
    {
        QPushButton *btn = new QPushButton("Событие " + QString().setNum(i+1));
        ls_event.append(btn);
        vb->addWidget(btn);
        connect(btn, SIGNAL(pressed()), this, SLOT(ChangeState()));
    }


    hb = new QHBoxLayout(this);
    hb->addSpacing(400);
    hb->addLayout(vb);

    setWindowTitle("Граф состояний");
}

TViewWindow::~TViewWindow()
{
    for (int i=0; i<ls_event.count(); i++)
    {
        QPushButton *btn = ls_event.takeLast();
        vb->removeWidget(btn);
        delete btn;
    }
    delete vb;
    delete hb;
}

void TViewWindow::activeEvent()
{
    int node = g->getNodeActive();
    for (int i=0; i< ls_event.count(); i++)
    {
        if (g->getMatrix().valueAt(node-1,i)==0)
            ls_event[i]->setEnabled(false);
        else
            ls_event[i]->setEnabled(true);
    }
}

void TViewWindow::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);
    g->draw(&p,QRect(0,0,350,400));
    p.end();
}

void TViewWindow::Graphupdate()
{
    int count = ls_event.count();
    int n = g->getMatrix().getY() - count;
    while(n<0)
    {
        QPushButton * p = ls_event.takeLast();
        disconnect(p, SIGNAL(pressed()), this, SLOT(ChangeState()));
        vb->removeWidget(p);
        delete p;
        n++;
    }

    for (int i = 0; i<n; i++)
    {
        QPushButton *p = new QPushButton("Событие " + QString().setNum(i+1+count));
        connect(p, SIGNAL(pressed()), this, SLOT(ChangeState()));
        ls_event.append(p);
        vb->addWidget(p);
    }
    activeEvent();
    update();
}

void TViewWindow::ChangeState()
{
    QPushButton *btn = (QPushButton*)sender();
    for (int i=0; i<ls_event.count(); i++)
    {
        if (btn==ls_event[i])
        {
            g->newEvent(i);
        }
    }
    Graphupdate();
}
