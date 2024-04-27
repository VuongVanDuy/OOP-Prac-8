#include "interface.h"


TInterface::TInterface(TGraphActive *graph, QWidget *parent)
    : QWidget{parent}
{
    this->graph = graph;
    this->view = nullptr;
    setFixedSize(200, 200);
    setWindowIcon(QIcon("./draw.png"));
    btn_1 = new QPushButton("Choose file", this);
    btn_2 = new QPushButton("Show graph", this);
    label = new QLabel("Default graph!", this);
    label->setWordWrap(true);
    label_1 = new QLabel("Active vertex:", this);
    spinbox = new QSpinBox(this);
    spinbox->setMinimum(1);
    spinbox->setMaximum(this->graph->getSizeAdjMat());
    spinbox->setValue(1);
    this->graph->setNodeActive(spinbox->value());

    layout = new QVBoxLayout(this);
    layout->addWidget(btn_1);
    layout->addWidget(label);
    layout->addWidget(label_1);
    layout->addWidget(spinbox);
    layout->addWidget(btn_2);

    connect(btn_1, SIGNAL(pressed()), this, SLOT(chooseFile()));
    connect(btn_2, SIGNAL(pressed()), this, SLOT(showGraph()));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(activeVerChanged(int)));
}

TInterface::~TInterface()
{
    delete btn_1;
    delete btn_2;
    delete label;
    delete label_1;
    delete spinbox;
    delete layout;
    delete view;
}

void TInterface::closeEvent(QCloseEvent*)
{
    if (view!=nullptr)
        view->close();
}

QString& operator << (QString& m, const QString& s)
{
    m += s;
    m.append(";");
    return m;
}

void TInterface::changeVerActive(int vertex)
{
    spinbox->setValue(vertex);
}

void TInterface::activeVerChanged(int vertex)
{
    if (vertex > 0)
    {
        this->graph->setNodeActive(vertex);
        if (view != nullptr && view->isVisible())
        {
            view->setEnabledBtns();
            showGraph();
        }
    }
}

void TInterface::chooseFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "", ("Graph (*.txt)"));
    if (fileName != nullptr)
    {
        bool check = readTextFile(fileName);
        if (!check)
        {
            label->setText("Default graph!");
            TMatrix<int> defaultGraph(2, 2);
            this->graph->setAdjMat(defaultGraph);
            spinbox->setMaximum(this->graph->getSizeAdjMat());
            spinbox->setValue(1);
            graph->setNodeActive(spinbox->value());
            showMessage(false, "Error! Invalid data has been read!");
        }
        else
        {
            showMessage(true, "Success! Finished reading\n the file! Valid data!");
            label->setText("Path to file: " + fileName);
        }
        return;
    }
}

bool TInterface::readTextFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        showMessage(false, "Error! Can not open file!" + fileName);
        return false;
    }
    QTextStream in(&file);
    QString s;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        s << line;
    }
    QStringList strValues = s.split(";");
    strValues.removeLast();
    bool check;
    int rows = strValues[0].toInt(&check);
    if (!check || rows <= 0) return false;
    else
    {
        if (strValues.length() != rows + 1) return false;
        int cols = strValues[1].split(" ").length();
        TMatrix<int> mat(rows, cols);
        for (int i = 1; i <= rows; i++)
        {
            QStringList values = strValues[i].split(" ");
            if (values.length() != cols) return false;
            for (int j = 0; j < cols; j++)
            {
                int a = values[j].toInt(&check);
                if (!check || (a > rows)) return false;
                else mat.setAtElement(a, i - 1, j);
            }
        }
        spinbox->setMaximum(rows);
        spinbox->setValue(1);
        graph->setNodeActive(spinbox->value());
        if (view != nullptr)
        {
            view->delBtns();
            view->close();
        }
        this->graph->setAdjMat(mat);
        if (view != nullptr) view->setupBtns();
    }
    file.close();
    return true;
}

void TInterface::showGraph()
{
    if (view == nullptr)
        view = new TCanvas(this->graph);
    else
        view->repaint();
    connect(view, SIGNAL(changeActive(int)), this, SLOT(changeVerActive(int)));
    view->show();
}
void TInterface::showMessage(bool status, const QString &message)
{
    if (status)
        QMessageBox::information(this, "Success!", message, QMessageBox::Ok);
    else
        QMessageBox::critical(this, "Error!", message, QMessageBox::Ok);
}
