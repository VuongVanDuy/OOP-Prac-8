#ifndef TMATRIX_H
#define TMATRIX_H

#include <QVector>

template <class T>
class TMatrix
{
    int x;
    int y;
    QVector<QVector<T>> data;
public:
    TMatrix();
    TMatrix(int, int, QVector<QVector<T>>);
    TMatrix(const TMatrix&);
    TMatrix& operator = (TMatrix);
    int getX();
    int getY();
    QVector<QVector<T>> getData();
    T valueAt(int, int);
};
template<class T>
TMatrix<T>::TMatrix()
{

}

template<class T>
TMatrix<T>::TMatrix(int a, int b, QVector<QVector<T>> d)
{
    x = a;
    y = b;
    data = d;
}

template<class T>
TMatrix<T>::TMatrix(const TMatrix& m)
{
    x = m.x;
    y = m.y;
    data = m.data;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator =(TMatrix<T> m)
{
    x = m.getX();
    y = m.getY();
    data = m.getData();
    return *this;
}

template<class T>
T TMatrix<T>::valueAt(int i, int j)
{
    return data[i][j];
}

template<class T>
int TMatrix<T>::getX()
{
    return x;
}

template<class T>
int TMatrix<T>::getY()
{
    return y;
}

template<class T>
QVector<QVector<T>> TMatrix<T>::getData()
{
    return data;
}

#endif // TMATRIX_H
