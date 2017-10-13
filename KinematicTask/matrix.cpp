#include <iostream>
#include "matrix.h"

using namespace std;

inline
Matrix::Matrix(int rows, int cols) : rows_ (rows), cols_ (cols)
{
    if (rows == 0 || cols == 0)
        cout << "Matrix constructor has 0 size" << endl;

    this->data_ = new double[rows * cols];
}

inline
Matrix::Matrix(int n) : rows_ (n), cols_ (n)
{
    if (n == 0)
        cout << "Matrix constructor has 0 size" << endl;
    this->data_ = new double[n * n];
}

inline
Matrix::~Matrix()
{
    delete[] this->data_;
}

inline
Matrix& Matrix::operator= (Matrix& m)
{
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < this->cols_; j++)
            this->data_[this->cols_*i+j] = m.data_[this->cols_*i+j];
    return *this;
}

inline
Matrix& Matrix::operator= (int k)
{
    this->data_ = {0};
    for(int i = 0, j = 0; i < this->rows_; i++, j++)
    {
        this->data_[this->cols_*i+j] = k;
    }
    return *this;
}

Matrix& Matrix::operator+ (Matrix& m)
{
    Matrix tmp(m.rows_, m.cols_);
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < this->cols_; j++)
            tmp.data_[this->cols_*i+j] = this->data_[this->cols_*i+j] + m.data_[this->cols_*i+j];
    return tmp;
}

Matrix& Matrix::operator* (Matrix& m)
{
    Matrix tmp(this->rows_, m.cols_);
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < m.cols_; j++)
            for(int k = 0; k < this->cols_; k++)
                tmp.data_[tmp.cols_*i+j] += this->data_[this->cols_*i+k] * m.data_[m.cols_*k+j];
    return tmp;
}

inline
void Matrix::show()
{
    for(int i = 0; i < this->rows_; i++)
    {
        for(int j = 0; j < this->cols_; j++)
            cout << this->data_[this->cols_*i+j] << " ";
        cout << endl;
    }
}
