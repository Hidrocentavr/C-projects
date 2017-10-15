#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    size_t rows_, cols_; //спрятать в методы и заприватить (инкапсуляция)

public:
    double *data_;

    Matrix();
    Matrix(int n);              //конструктор кавдратной матрицы
    Matrix(size_t rows, size_t cols); //конструктор прямоугольной матрицы
    ~Matrix();                  //деструктор

    double operator() (int row, int col);    //перегрузка оператора ()
    Matrix& operator= (int k);                //перегрузка оператора = числом
    Matrix& operator= (const Matrix& m);            //перегрузка оператора =
    Matrix& operator+ (const Matrix& m);            //перегрузка оператора +
    Matrix operator* (const Matrix& m);            //перегрузка оператора *

    void show();
};

#endif // MATRIX_H
