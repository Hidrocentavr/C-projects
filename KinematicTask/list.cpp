#include <iostream>
#include "list.h"

using namespace std;

void Point::Input(Point &point)
{
    cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
    cin >> point.type;
    if (point.type == 0)
    {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q = "; cin >> point.q;
        cout << "Параметр alpha = "; cin >> point.alpha;
        cout << "Параметр a = "; cin >> point.a;
        cout << "Параметр d - обобщённая координата" << endl; point.d = -1;
    }
    else
    {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q - обобщённая координата" << endl; point.q = -1;
        cout << "Параметр alpha = "; cin >> point.alpha;
        cout << "Параметр a = "; cin >> point.a;
        cout << "Параметр d = "; cin >> point.d;
    }
}

inline
List::List()
{
    Head = NULL;
    Tail = NULL;
}

inline
List::~List()
{
    while (Head != NULL)
    {
        Point *temp = Head->Next;
        delete Head;
        Head = temp;
    }
}

inline
bool List::Empty()
{
    return (Head == NULL);
}

void List::Add(Point &point)
{
    Point *temp = new Point;

    temp->type = point.type;
    temp->a = point.a;
    temp->alpha = point.alpha;
    temp->d = point.d;
    temp->q = point.q;

    if (List::Empty())
    {
        Head = temp;
    }
    else
    {
        Tail->Next = temp;
    }
    temp->Next = NULL;
    Tail = temp;
}

void List::Show()
{
    Point *temp = Head;
    int i=0;
    while (temp != NULL)
    {
        cout << "----------------------------------" << endl;
        cout << "             Звено " << ++i << endl;
        cout << "----------------------------------" << endl;
        cout << (temp->type == 0 ? "Поступательная" : "Вращательная") << " кинематическая пара" << endl;
        if (temp->q == -1)
            cout << "Параметр q - обобщённая координата" << endl;
        else
            cout << "Параметр q = " << temp->q << endl;
        cout << "Параметр alpha = " << temp->alpha << endl;
        cout << "Параметр a = " << temp->a << endl;
        if (temp->d == -1)
            cout << "Параметр d - обобщённая координата" << endl;
        else
            cout << "Параметр d = " << temp->d << endl;

        temp = temp->Next;
    }
}

Point* List::Search(int n)
{
    Point *temp = Head;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return temp;
}

void List::Delete(int n)
{
    Point *temp = Head, element;

    if (Head == Tail)
    {
        Head = NULL;
        Tail = NULL;
        return;
    }

    if (n == 1)
    {
        delete Head;
        Head = temp->Next;
        return;
    }

    temp = Search(n-1);

    if (temp->Next != Tail)
    {
        element.Next = temp->Next->Next;
        delete temp->Next;
        temp->Next = element.Next;
    }
    /* else
    {
        element = temp->Next;
        delete element;
        temp->Next = NULL;
    }*/
}

/*Matrix List::AMatrix(float q, float alpha, float a, float d) //перенести в структуру звена
{
    Matrix A(4);
    A.data_ =
    {
        {cos(q), -cos(alpha)*sin(q), sin(alpha)*sin(q), a*cos(q)},
        {sin(q), cos(alpha)*cos(q), -sin(alpha)*cos(q), a*sin(q)},
        {0, sin(alpha), cos(alpha), d},
        {0, 0, 0, 1}
    };
    return A;
}

Matrix List::Solver(Sensor encoder)
{
    Matrix T(4);
    T.data_ = 1;

    Point *temp = Head;

    cout << "Введите обобщённые координаты";
    for (int i = 0; temp != NULL; i++)
    {
        cout << "Звено " << i << ":";
        if (temp->type == 1)
            temp->q = cin >> encoder.data[i];
        else
            temp->d = cin >> encoder.data[i];

        T = T * AMatrix(temp->q, temp->alpha, temp->a, temp->d);
        temp = temp->Next;
    }

    return T;
}*/
