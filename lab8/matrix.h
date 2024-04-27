#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>

using namespace std;

template <class T>
class TMatrix
{
protected:
    int rows, cols;
    T **matrix;

public:
    TMatrix(int rows = 2, int cols = 2);
    TMatrix(const TMatrix&);
    ~TMatrix();

    TMatrix& operator = (const TMatrix&);
    template <class type>
    friend ostream& operator << (ostream& os, TMatrix<type> &mat);

    T valueAt(int, int);
    void setAtElement(T, int, int);
    void ReFixMatrix(T**, int, int);
    T **getMatrix();
    int getRowsMatrix();
    int getColsMatrix();
    T **createEchelonMatrix();
    T **getTransMatrix();
    int getRankMatrix();
    void delMatrix();
};

#endif // TMATRIX_H
