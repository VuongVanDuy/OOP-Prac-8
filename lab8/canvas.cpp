#include "canvas.h"

TCanvas::TCanvas(TGraphActive* graph, QWidget *parent)
    : QWidget(parent)
{
    this->graph = graph;
    setFixedSize(450, 400);
    setWindowTitle("Directed graph");
    setWindowIcon(QIcon("./graph.png"));
    layout = new QVBoxLayout(this);
    container = new QWidget(this);
    container->setFixedSize(100, 300);
    container->setLayout(layout);
    container->move(330,20);
    setupBtns();
}

void TCanvas::delBtns()
{
    if (btns != nullptr)
    {
        for (int i = 0; i < graph->getNumEvents(); i++)
        {
            if (btns[i] != nullptr)
                delete btns[i];
        }
        delete[] btns;
        btns = nullptr;
    }
}

void TCanvas::setupBtns()
{
    int numEvents = this->graph->getNumEvents();
    btns = new QPushButton*[numEvents];
    for (int i = 0; i < numEvents; i++)
    {
        btns[i] = new QPushButton(("Event " + QString().setNum(i+1)), this);
        layout->addWidget(btns[i]);
    }
    setEnabledBtns();
    for (int i = 0; i < numEvents; i++)
    {
        connect(btns[i], SIGNAL(pressed()), this, SLOT(changeState()));
    }
}

void TCanvas::setEnabledBtns()
{
    int numEvents = this->graph->getNumEvents();
    int nodeActive = this->graph->getNodeActive() - 1;
    for (int i = 0; i < numEvents; i++)
    {
        if (graph->elementAt(nodeActive, i) == 0)
            btns[i]->setEnabled(false);
        else btns[i]->setEnabled(true);
    }
}

TCanvas::~TCanvas()
{
    delBtns();
    delete layout;
    delete container;
}

void TCanvas::changeState()
{
    QPushButton *btn = (QPushButton*)sender();
    int index, newNodeActive;
    for (int i = 0; i < graph->getNumEvents(); i++)
    {
        if (btn == btns[i])
        {
            index = graph->getNodeActive() - 1;
            newNodeActive = graph->elementAt(index, i);
            if (newNodeActive > 0)
            {
                graph->setNodeActive(newNodeActive);
                emit this->changeActive(graph->getNodeActive());
                repaint();
                setEnabledBtns();
            }        
            break;
        }
    }
}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    graph->drawGraph(&p, QRect(0,0,300,300));
    p.end();
}

