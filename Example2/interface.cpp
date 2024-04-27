#include "interface.h"


TInterface::TInterface(TGraphActive* g,QWidget *parent)
    : QWidget(parent)
{
    graph = g;
    lb_nodeActive = new QLabel("Активная вершина:");
    sp_nodeActive = new QSpinBox();
    sp_nodeActive->setMinimum(1);
    sp_nodeActive->setMaximum(graph->getCount());
    sp_nodeActive->setValue(1);
    hb1 = new QHBoxLayout();
    hb1->addWidget(lb_nodeActive);
    hb1->addWidget(sp_nodeActive);

    lb_name = new QLabel("Путь к файлу:");
    lb_path = new QLabel("Граф по умольчанию!");
    lb_path->setMinimumWidth(180);
    lb_path->setWordWrap(true);
    btn_chose = new QPushButton("Выбрать файл");

    hb2 = new QHBoxLayout();
    hb2->addWidget(lb_name);
    hb2->addWidget(btn_chose);

    vb = new QVBoxLayout(this);
    vb->addLayout(hb1);
    vb->addLayout(hb2);
    vb->addWidget(lb_path);
    btn_draw = new QPushButton("Отображение графа");
    vb->addWidget(btn_draw);
    setFixedSize(QSize(400,150));


    vw = nullptr;

    connect(btn_chose,SIGNAL(pressed()),this,SLOT(openFile()));
    connect(this,SIGNAL(dataReaded(TMatrix<qint16>)),graph,SLOT(changeMatrix(TMatrix<qint16>)));
    connect(btn_draw,SIGNAL(pressed()),this,SLOT(view()));
    connect(sp_nodeActive,SIGNAL(valueChanged(int)),graph,SLOT(changeActive(int)));
    connect(graph,SIGNAL(changeNodeActive(int)),this,SLOT(changeNodeActice(int)));


    setWindowTitle("Работа №7");
}

void TInterface::changeNodeActice(int value)
{
    sp_nodeActive->setValue(value);
}

TInterface::~TInterface()
{
    delete graph;
    delete vw;
    delete hb2;
    delete hb1;
    delete lb_nodeActive;
    delete sp_nodeActive;
    delete lb_name;
    delete lb_path;
    delete btn_chose;
    delete vb;
    delete btn_draw;
}

void TInterface::view()
{
    if(vw==nullptr)
    {
        vw = new TViewWindow(graph);
        connect(sp_nodeActive, SIGNAL(valueChanged(int)), vw, SLOT(Graphupdate()));
    }
    vw->show();
}

void TInterface::closeEvent(QCloseEvent*)
{
    if (vw!=nullptr)
    {
        vw->close();
        disconnect(sp_nodeActive, SIGNAL(valueChanged(int)), vw, SLOT(Graphupdate()));
    }
}

void TInterface::openFile()
{
    QString nameFile = QFileDialog::getOpenFileName(this, "Выберите файл с матрицей смежности");
    if (nameFile!=nullptr)
    {
        lb_path->setText(nameFile);

        QFile file(nameFile);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            bool flag = true;
            QTextStream data(&file);
            QVector<QVector<qint16>> matrix;
            int sizeColumn = 0;
            int sizeRow = 0;

            QVector<QStringList> buff;
            while (!data.atEnd() && flag)
            {
                QString line = data.readLine();
                line = line.trimmed();
                QStringList numList = line.split(" ");
                if (sizeColumn==0)
                    sizeColumn = numList.count();
                else
                {
                    if (numList.count()!=sizeColumn)
                    {
                        flag = false;
                        QMessageBox::warning(this, "Неправильный формат файла", "Нужно вводить матрицу m*n!");
                        lb_path->setText("Граф по умальчанию!");
                        return;
                    }
                }
                buff.append(numList);
            }
            sizeRow = buff.count();

            for (int i=0; i<sizeRow; i++)
            {
                QVector<qint16> temp;

                for (int j=0; j<sizeColumn; j++)
                {
                    int t = buff[i][j].toInt();
                    if (t<0 || t>sizeRow)
                    {
                        flag = false;
                        QMessageBox::warning(this, "Неправильный формат файла", "Элементами матрицы смежности не могут быть символы " + QString().setNum(t) + " !");
                        lb_path->setText("Граф по умальчанию!");
                        break;
                    }
                    temp.append(t);
                }
                if (flag==false)
                    break;
                matrix.append(temp);
            }


            if (flag == true)
            {
                emit dataReaded(TMatrix<qint16>(sizeRow,sizeColumn,matrix));
                if (vw!=nullptr)
                {
                    vw->close();
                    vw->Graphupdate();
                }

                sp_nodeActive->setMaximum(graph->getCount());
            }
        }
        else
        {
            QMessageBox::warning(this, "Сообщение", "Не может открыть файл!");
        }
    }
    else
    {
        QMessageBox::warning(this, "Сообщение", "Файл не был выбран!");
        lb_path->setText("Граф по умальчанию!");
    }
}
