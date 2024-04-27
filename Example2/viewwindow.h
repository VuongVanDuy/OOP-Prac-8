#ifndef TVIEWWINDOW_H
#define TVIEWWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include "graphactive.h"

class TViewWindow : public QWidget
{
    Q_OBJECT
    TGraphActive *g;
    QVector<QPushButton*> ls_event;
    QVBoxLayout *vb;
    QHBoxLayout *hb;

    void activeEvent();
public:
    TViewWindow(QWidget *parent =0);
    TViewWindow(TGraphActive*, QWidget *parent = 0);
    ~TViewWindow();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void ChangeState();
public slots:
    void Graphupdate();
};

#endif // TVIEWWINDOW_H
