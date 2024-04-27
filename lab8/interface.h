#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>
#include "canvas.h"
#include "graph_active.h"

class TInterface : public QWidget
{
    Q_OBJECT
    TGraphActive *graph;
    TCanvas *view;
    QLabel *label, *label_1;
    QPushButton *btn_1, *btn_2;
    QSpinBox *spinbox;
    QVBoxLayout *layout;
public:
    TInterface(TGraphActive*, QWidget *parent = nullptr);
    ~TInterface();

    bool readTextFile(const QString&);
    void showMessage(bool, const QString&);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void chooseFile();
    void showGraph();

public slots:
    void activeVerChanged(int);
    void changeVerActive(int);
};

#endif // TINTERFACE_H
