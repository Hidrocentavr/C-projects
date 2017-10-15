#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int rows_, cols_; //спрятать в методы и заприватить (инкапсуляция)

public:
    double *data_;

    Matrix();
    Matrix(int n);              //конструктор кавдратной матрицы
    Matrix(int rows, int cols); //конструктор прямоугольной матрицы
    ~Matrix();                  //деструктор

    double operator() (int row, int col);    //перегрузка оператора ()
    Matrix operator= (int k);                //перегрузка оператора = числом
    Matrix operator= (Matrix m);            //перегрузка оператора =
    Matrix operator+ (Matrix m);            //перегрузка оператора +
    Matrix operator* (Matrix m);            //перегрузка оператора *

    void show();
};

#endif // MATRIX_H
