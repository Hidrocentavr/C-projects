#include <QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "matrix.h" //мои матрицы
#include "list.h" //мои списки

using namespace std;

/*=============== ОСНОВНЫЕ ЭЛЕМЕНТЫ ПРОГРАММЫ ===============*/

class Manipulator : public List
{
public:
    Matrix SolveDirectKinematic(); //решатель
    Matrix AMatrix(float q, float alpha, float a, float d); //матрица переноса A
};

void SayHello();                //приветствие
void ShowMenu();                //описание меню
bool Menu(Manipulator manipulator);                    //реализация меню

/*=============== ГЛАВНАЯ ФУНКЦИЯ ===============*/

//List manipulator;

int main()
{
    setlocale(0, "");

    SayHello();
    ShowMenu();

    Manipulator manipulator;

    while(true)
    {
        if (!Menu(manipulator))
            exit(0);
    }

    return 0;
}

/*=============== ОПИСАНИЕ ФУНКЦИЙ, МЕТОДОВ, КОНСТРУКТОРОВ И ВСЕГО ОСТАЛЬНОГО ===============*/

//---------
//ИНТЕРФЕЙС
//---------
inline
void SayHello()
{
    cout << "Привет!" << endl;
    cout << "Ты запустил программу для решения прямой позиционной задачи." << endl;
    cout << "Ниже ты видишь меню, чтобы сделать выбор просто введи номер пункта." << endl;
    cout << "Например, если ты хочешь добавить новое звено манипулятору, то вводи 1." << endl;
    cout << "Удачи!" << endl;
    cout << endl;
}

inline
void ShowMenu()
{
    cout << "МЕНЮ" << endl;
    cout << "==================================================" << endl;
    cout << "1. Добавить новое звено" << endl;
    cout << "2. Удалить звено" << endl;
    cout << "3. Вывести список звеньев на экран" << endl;
    cout << "4. Решить прямую позиционную задачу" << endl;
    cout << "5. Решить прямую кинематическую задачу о скорости" << endl;
    cout << "6. Выход из программы" << endl;
    cout << "? - вывести меню на экран" << endl;
    cout << "==================================================" << endl;
}

bool Menu(Manipulator manipulator)
{
    char number;

    cout << "Твой выбор: "; cin >> number;

    switch (number)
    {
    case '1':
    {
        Element element;

        cout << "Звено " << manipulator.NumberOfElements() << endl;

        element.point.Input();
        manipulator.Add(element);

        cout << endl << "Звено успешно добавлено!" << endl;

        break;
    }

    case '2':
        int n;

        cout << "Введите номер звена: "; cin >> n;

        manipulator.Delete(n);
        cout << endl << "Звено успешно удалено!" << endl;

        break;

    case '3':
        manipulator.Show();

        break;

    case '4':
        manipulator.SolveDirectKinematic();

        cout << "Матрица T успешно вычислена!" << endl;
        break;

    case '5':
        cout << "Данный пункт меню находится в разработке." << endl;
        break;

    case '6':
        return 0;

    case '?':
        ShowMenu();
        break;

    default:
        cout << "Ошибка!" << endl;
        break;
    }

    cout << endl;

    return 1;
}

Matrix Manipulator::AMatrix(float q, float alpha, float a, float d) //перенести в структуру звена
{
    Matrix A(4);
    A.data_[0] = cos(q); A.data_[1] = -cos(alpha)*sin(q);
    A.data_[2] = sin(alpha)*sin(q); A.data_[3] = a*cos(q);
    A.data_[4] = sin(q); A.data_[5] = cos(alpha)*cos(q);
    A.data_[6] = -sin(alpha)*cos(q); A.data_[7] = a*sin(q);
    A.data_[8] = 0; A.data_[9] = sin(alpha);
    A.data_[10] = cos(alpha); A.data_[11] = d;
    A.data_[12] = 0; A.data_[13] = 0; A.data_[14] = 0; A.data_[15] = 0;

    return A;
}

Matrix Manipulator::SolveDirectKinematic()
{
    Matrix T(4);
    T = 1;
    int i = 0;
    Element *temp;

    cout << "Введите обобщённые координаты";

    for (temp = Search(1); temp != NULL; temp = temp->Next)
    {
        cout << "Звено " << i << ":";
        if (temp->point.type == 1)
            cin >> temp->point.q;
        else
            cin >> temp->point.d;

        T = T * AMatrix(temp->point.q, temp->point.alpha, temp->point.a, temp->point.d);
        i++;
    }

    return T;
}


/*=============== ЗАДУМКИ, КОТОРЫЕ ЕЩЁ МОГУТ ПРИГОДИТЬСЯ ===============*/

/*const float q_value[] = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

//Таймер
class MyTime
{
private:
    int time_ms;

public:

};

//Датчики
class Sensors
{
private:

public:
    //энкодеры
    class encoders
    {
    private:
        float q;
        float Time;

    public:
        float getValue(int number)
        {
            q = q_value(number);
            Time = MyTime.get("ms");
            return q;
        }
    };
};

//манипулятор
class Manipulator
{
private:
    struct point;

public:
    int NumberOfPoints;
    point points[NumberOfPoints];

    void input()
    {
        cout << "Количество звеньев: ";
        cin >> pointsnumber >> endl;
        for (int i = 0; i < NumberOfPoints; i++)
        {
            cout << "Звено " << i << endl;
            cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
            cin >> points[i].type >> endl;
            if (points[i].type == 0)
            {
                cout << "Введите параметры Денавита-Хартенберга:" << endl;
                cout << "Параметр q = ";
                cin >> points[i].q >> endl;
                cout << "Параметр alpha = ";
                cin >> points[i].alpha >> endl;
                cout << "Параметр a = ";
                cin >> points[i].a >> endl;
            }
            else
            {
                cout << "Введите параметры Денавита-Хартенберга (если параметр" << endl;
                cout << "Параметр alpha = ";
                cin >> points[i].alpha >> endl;
                cout << "Параметр a = ";
                cin >> points[i].a >> endl;
                cout << "Параметр d = ";
                cin >> points[i].d >> endl;
            }
        }
    }
};

class Solver : public List
{
public:


AMatrix(int n)
    {
        Point point;
        point = List.Search(n);
        float A[4][4]={
            {cos(point.q), -cos(point.alpha)*sin(q), sin(point.alpha)*sin(point.q), a*cos(point.q)},
            {sin(point.q), cos(point.alpha)*cos(point.q), -sin(point.alpha)*cos(point.q), a*sin(point.q)},
            {0, sin(point.aplha), cos(point.alpha), point.d},
            {0, 0, 0, 1}
        };
        return A;
    }

    float TMatrix()
    {
        Point point = Head;
        float T[4][4] = AMatrix(point);

        while (point.Next)
        {
            T = T * AMatrix(point.Next);
            point = point.Next;
        }
        return T;
    }
};

//Решатель
class RobotArmSolver
{
private:

public:
    //Вычисление матрицы перехода по известным обобщённым координатам
    float SolveDirectKinematic(float* q)
    {



        T = q; //вычисление матрицы
        return T;
    }
};

//-------
//ДАТЧИКИ
//-------
inline
void Sensor::Input(Sensor encoder, List mp)
{
    cout << "Введите обобщённые координаты";
    for (int i = 0; i < mp.NumberOfPoints; i++)
        cout << "Звено " << i << ":"; cin >> encoder.data[i];
}
*/
