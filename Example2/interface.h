#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include "viewwindow.h"
#include <QSpinBox>


class TInterface : public QWidget
{
    Q_OBJECT
    QLabel *lb_name;
    QLabel *lb_path;
    QLabel *lb_nodeActive;
    QSpinBox *sp_nodeActive;
    QPushButton *btn_chose;
    QHBoxLayout *hb1;
    QHBoxLayout *hb2;
    QVBoxLayout *vb;
    QPushButton *btn_draw;

    TGraphActive *graph;
    TViewWindow *vw;
public:
    TInterface(TGraphActive* , QWidget *parent = nullptr);
    ~TInterface();
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void openFile();
    void view();
signals:
    void dataReaded(TMatrix<qint16>);
    void changeAvtive(int);
public slots:
    void changeNodeActice(int);
};
#endif // TINTERFACE_H
