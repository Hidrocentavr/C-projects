#include <iostream>
#include <stdio.h>
#include "matrix.h"

Matrix::Matrix() : rows_ (0), cols_ (0), data_ (NULL)
{

}

Matrix::Matrix(int n) : rows_ (n), cols_ (n)
{
    if (n == 0)
        std::cout << "Matrix constructor has 0 size" << std::endl;

    data_ = new double[n * n];
}

Matrix::Matrix(int rows, int cols) : rows_ (rows), cols_ (cols)
{
    if (rows == 0 || cols == 0)
        std::cout << "Matrix constructor has 0 size" << std::endl;

    data_ = new double[rows * cols];
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator= (int k)
{
    if (rows_ == cols_)
    {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
            {
                if (i == j)
                    data_[cols_*i+j] = k;
                else
                    data_[cols_*i+j] = 0;
            }
    }
    else
    {
        std::cout << "Матрица не квадратная" << std::endl;
    }

    return *this;
}

Matrix Matrix::operator= (Matrix m)
{
    if (m.cols_ == cols_ && m.rows_ == rows_)
    {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                data_[cols_*i+j] = m.data_[cols_*i+j];
    }
    else
    {
        std::cout << "Размеры матриц не совпадают" << std::endl;
    }

    return *this;
}

Matrix Matrix::operator+ (Matrix m)
{
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[cols_*i+j] = data_[cols_*i+j] + m.data_[cols_*i+j];

    return *this;
}

Matrix Matrix::operator* (Matrix m)
{
    Matrix tmp(rows_, m.cols_);
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < m.cols_; j++)
            for (int k = 0; k < cols_; k++)
                tmp.data_[tmp.cols_*i+j] += data_[cols_*i+k] * m.data_[m.cols_*k+j];
    return tmp;
}

void Matrix::show()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
            printf("%-10.3lf", data_[cols_*i+j]);
        std::cout << std::endl;
    }
}
