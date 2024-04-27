#include "matrix.h"

template <class T>
TMatrix<T>::TMatrix(int rows, int cols)
{
    if (rows > 0 && cols > 0)
    {
        this->rows = rows; this->cols = cols;
        matrix = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = 1;
            }
        }
    }
    else matrix = nullptr;
}

template <class T>
TMatrix<T>::~TMatrix()
{
    this->delMatrix();
}

// copy constructor
template <class T>
TMatrix<T>::TMatrix(const TMatrix<T> &other)
{
    ReFixMatrix(other.matrix, other.rows, other.cols);
}

// Copy assignment operator
template <class T>
TMatrix<T>& TMatrix<T>::operator = (const TMatrix<T> &other)
{
    if (this != &other)
    {
        ReFixMatrix(other.matrix, other.rows, other.cols);
    }
    return *this;
}

template <class T>
void TMatrix<T>::setAtElement(T val, int i, int j)
{
    matrix[i][j] = val;
}


template <class T>
void TMatrix<T>::ReFixMatrix(T **newArr, int newRows, int newCols)
{
    if (newRows > 0 && newCols > 0)
    {
        delMatrix();
        rows = newRows;
        cols = newCols;
        matrix = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = newArr[i][j];
            }
        }
    }
}

template <class T>
T** TMatrix<T>::getMatrix()
{
    return this->matrix;
}

template <class T>
int TMatrix<T>::getRowsMatrix()
{
    return this->rows;
}

template <class T>
T TMatrix<T>::valueAt(int i, int j)
{
    return this->matrix[i][j];
}

template <class T>
int TMatrix<T>::getColsMatrix()
{
    return this->cols;
}

template <class T>
ostream& operator << (ostream& os, TMatrix<T> &mat)
{
    int rows = mat.rows;
    int cols = mat.cols;
    cout << "Elements of matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            os << mat.matrix[i][j] << " ";
        }
        cout << endl;
    }
    return os;
}

template <class T>
T** TMatrix<T>::getTransMatrix()
{
    T **transMat = new T*[cols];
    for (int i = 0; i < cols; i++)
    {
        transMat[i] = new T[rows];
        for (int j = 0; j < rows; j++)
        {
            transMat[i][j] = matrix[j][i];
        }
    }
    return transMat;
}

template <class T>
int TMatrix<T>::getRankMatrix()
{
    T **triaArr = createEchelonMatrix();
    int rank = 0;
    for (int i = 0; i < rows; i++)
    {
        if (triaArr[i][i] != 0)
        {
            rank++;
        }
    }
    for (int i = 0; i < rows; i++)
    {
        delete[] triaArr[i];
    }
    delete[] triaArr;
    triaArr = nullptr;
    return rank;
}

template <class T>
T** TMatrix<T>::createEchelonMatrix()
{
    T **triaArr = new T*[rows];
    for (int i = 0; i < rows; i++)
    {
        triaArr[i] = new T[cols];
        for (int j = 0; j < cols; j++)
        {
            triaArr[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        int pivot = i;
        while (pivot < rows && triaArr[pivot][i] == 0)
        {
            pivot++;
        }
        if (pivot == rows)
        {
            continue;
        }
        if (pivot != i)
        {
            for (int j = 0; j < cols; j++)
            {
                swap(triaArr[i][j], triaArr[pivot][j]);
            }
        }
        for (int j = 0; j < cols; j++)
        {
            if (j != i)
            {
                for (int k = i + 1; k < rows; k++)
                {
                    triaArr[k][j] = triaArr[k][j] - (triaArr[k][i] * triaArr[i][j] / triaArr[i][i]);
                }
            }
        }
        for (int k = i + 1; k < rows; k++) triaArr[k][i] = 0;
    }
    return triaArr;
}

template <class T>
void TMatrix<T>::delMatrix()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
    this->matrix = nullptr;
    this->rows = 0;
    this->cols = 0;
}

template class TMatrix<int>;
