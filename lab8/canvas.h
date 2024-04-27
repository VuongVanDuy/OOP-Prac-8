#ifndef TCANVAS_H
#define TCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QIcon>
#include <QVBoxLayout>
#include "graph_active.h"

class TCanvas : public QWidget
{
    Q_OBJECT

    TGraphActive *graph;
    QPushButton **btns = nullptr;
    QWidget *container;
    QVBoxLayout *layout;
public:
    TCanvas(TGraphActive*, QWidget *parent = 0);
    ~TCanvas();

    void setupBtns();
    void setEnabledBtns();
    void delBtns();

public slots:
    void changeState();

protected:
    void paintEvent(QPaintEvent*);

signals:
    void changeActive(int);
};

#endif // TCANVAS_H
