#include <QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "matrix.h" //мои матрицы
#include "list.h" //мои списки

/////////////////////////////////////////////////////////////////////////////////////////////
////*=========================== ОСНОВНЫЕ ЭЛЕМЕНТЫ ПРОГРАММЫ ===========================*////
/////////////////////////////////////////////////////////////////////////////////////////////

class Point
{
private:
    int _type;
    float _q;
    float _alpha;
    float _a;
    float _d;
    float* _oc;

public:
    void input();   //метод для ввода параметров звена
    void show();
    int get_type(){ return _type; }
    float get_q(){ return _q; }
    float get_alpha(){ return _alpha; }
    float get_a(){ return _a; }
    float get_d(){ return _d; }
    void inputGenCoor();
};

class ManipulatorSolver
{
private:
    Matrix _result{4};
    Matrix AMatrix(float, float, float, float); //матрица переноса A

public:
    ManipulatorSolver() { _result = 1; }
    void SolveDirectKinematic(List<Point>&); //решатель
    void showResult();
};

/////////////////////////////////////////////////////////////////////////////////////////////
////*====================================== Point ======================================*////
/////////////////////////////////////////////////////////////////////////////////////////////

void Point::input()
{
    std::cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
    std::cin >> _type;
    std::cout << std::endl;

    if (_type == 0)
    {
        std::cout << "Введите параметры Денавита-Хартенберга:" << std::endl << std::endl;
        std::cout << "Параметр q = "; std::cin >> _q;
        std::cout << "Параметр alpha = "; std::cin >> _alpha;
        std::cout << "Параметр a = "; std::cin >> _a;
        std::cout << "Параметр d - обобщённая координата" << std::endl; _d = -1;
        *_oc = _d;
    }
    else
    {
        std::cout << "Введите параметры Денавита-Хартенберга:" << std::endl << std::endl;
        std::cout << "Параметр q - обобщённая координата" << std::endl; _q = -1;
        std::cout << "Параметр alpha = "; std::cin >> _alpha;
        std::cout << "Параметр a = "; std::cin >> _a;
        std::cout << "Параметр d = "; std::cin >> _d;
        *_oc = _q;
    }
}

void Point::show()
{
    std::cout << (this->_type == 0 ? "Поступательная" : "Вращательная") << " кинематическая пара" << std::endl;

    if (_q == -1)
        std::cout << "Параметр q - обобщённая координата" << std::endl;
    else
        std::cout << "Параметр q = " << _q << std::endl;
    std::cout << "Параметр alpha = " << _alpha << std::endl;
    std::cout << "Параметр a = " << _a << std::endl;
    if (_d == -1)
        std::cout << "Параметр d - обобщённая координата" << std::endl;
    else
        std::cout << "Параметр d = " << _d << std::endl;
}

void Point::inputGenCoor()
{
    std::cin >> *_oc;
}

/////////////////////////////////////////////////////////////////////////////////////////////
////*================================ ManipulatorSolver ================================*////
/////////////////////////////////////////////////////////////////////////////////////////////

void ManipulatorSolver::showResult()
{
    _result.show();
}

Matrix ManipulatorSolver::AMatrix(float q, float alpha, float a, float d) //перенести в структуру звена
{
    Matrix A(4);
    A.data_[0] = cos(q); A.data_[1] = -cos(alpha)*sin(q);
    A.data_[2] = sin(alpha)*sin(q); A.data_[3] = a*cos(q);
    A.data_[4] = sin(q); A.data_[5] = cos(alpha)*cos(q);
    A.data_[6] = -sin(alpha)*cos(q); A.data_[7] = a*sin(q);
    A.data_[8] = 0; A.data_[9] = sin(alpha);
    A.data_[10] = cos(alpha); A.data_[11] = d;
    A.data_[12] = 0; A.data_[13] = 0; A.data_[14] = 0; A.data_[15] = 1;

    return A;
}

void ManipulatorSolver::SolveDirectKinematic(List<Point>& list)
{
    Matrix T(4);
    T = 1;
    int i = 1;

    std::cout << "Введите обобщённые координаты" << std::endl;

    do
    {
        Point *temp = list.search(i);
        std::cout << "Звено " << i << ": ";
        temp->inputGenCoor();

        T = T * AMatrix(temp->get_q(), temp->get_alpha(), temp->get_a(), temp->get_d());

        i++;
    }
    while (i <= list.numberOfElements());
    _result = T;
}

/////////////////////////////////////////////////////////////////////////////////////////////
////*===================================== Функции =====================================*////
/////////////////////////////////////////////////////////////////////////////////////////////

void SayHello()
{
    std::cout << "Привет!" << std::endl;
    std::cout << "Ты запустил программу для решения прямой позиционной задачи." << std::endl;
    std::cout << "Ниже ты видишь меню, чтобы сделать выбор просто введи номер пункта." << std::endl;
    std::cout << "Например, если ты хочешь добавить новое звено манипулятору, то вводи 1." << std::endl;
    std::cout << "Удачи!" << std::endl;
    std::cout << std::endl;
}


void ShowMenu()
{
    std::cout << "МЕНЮ" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "1. Добавить новое звено" << std::endl;
    std::cout << "2. Удалить звено" << std::endl;
    std::cout << "3. Вывести список звеньев на экран" << std::endl;
    std::cout << "4. Решить прямую позиционную задачу" << std::endl;
    std::cout << "5. Показать матрицу Т" << std::endl;
    std::cout << "6. Выход из программы" << std::endl;
    std::cout << "? - вывести меню на экран" << std::endl;
    std::cout << "==================================================" << std::endl;
}

bool Menu(List<Point>& l, ManipulatorSolver& s)
{
    char number;

    std::cout << std::endl << "Твой выбор: ";
    std::cin >> number;
    std::cout << std::endl;

    switch (number)
    {
    case '1':
    {
        Point el;
        std::cout << "Звено " << l.numberOfElements()+1 << std::endl;

        el.input();
        l.add(el);

        std::cout << std::endl << "Звено успешно добавлено!" << std::endl;

        break;
    }

    case '2':
    {
        int n;

        std::cout << "Введите номер звена: "; std::cin >> n;

        l.del(n);
        std::cout << std::endl << "Звено успешно удалено!" << std::endl;

        break;
    }

    case '3':
    {
            int i = 1;
            for (Point *temp = l.search(i); i <= l.numberOfElements(); temp = l.search(i))
            {
                std::cout << "----------------------------------" << std::endl;
                std::cout << "             Звено " << i++ << std::endl;
                std::cout << "----------------------------------" << std::endl;

                temp->show();
            }

        break;
    }

    case '4':
        s.SolveDirectKinematic(l);

        std::cout << "Матрица T успешно вычислена!" << std::endl;
        break;

    case '5':
        std::cout << "Матрица Т:" << std::endl;
        s.showResult();
        break;

    case '6':
        return 0;

    case '?':
        ShowMenu();
        break;

    default:
        std::cout << "Ошибка!" << std::endl;
        break;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
////*================================= ГЛАВНАЯ ФУНКЦИЯ =================================*////
/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    SayHello();
    ShowMenu();

    List<Point> manipulator;
    ManipulatorSolver solver;

    while(true)
    {
        if (!Menu(manipulator, solver))
            std::exit(0);
    }

    return 0;
}
