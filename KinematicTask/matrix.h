#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
    int rows_, cols_; //спрятать в методы и заприватить (инкапсуляция)
    double* data_;

    Matrix(int rows, int cols); //конструктор прямоугольной матрицы
    Matrix(int n);              //конструктор кавдратной матрицы
    ~Matrix();                  //деструктор

    double& operator() (int row, int col);    //перегрузка оператора ()
    Matrix& operator= (Matrix& m);            //перегрузка оператора =
    Matrix& operator+ (Matrix& m);            //перегрузка оператора +
    Matrix& operator* (Matrix& m);            //перегрузка оператора *
    Matrix& operator= (int k);                //перегрузка оператора = числом

    void show();
};

#endif // MATRIX_H
