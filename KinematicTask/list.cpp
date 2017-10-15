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
List::List() : _Head(NULL), _Tail(NULL), _num(0)
{

}

inline
List::~List()
{
    while (_Head != NULL)
    {
        Element *temp = *_Head->Next;
        delete _Head;
        _Head = temp;
    }
    delete _num;
}

int List::NumberOfElements()
{
    return _num;
}

bool List::Empty()
{
    return (_Head == NULL);
}

void List::Add(Element element)
{
    Element *temp = new Element;

    temp->point = element.point;
    temp->Next = NULL;

    _num++;

    if (Empty())
    {
        _Head = temp;
    }
    else
    {
        _Tail->Next = temp;
    }
    _Tail = temp;
}

void List::Show()
{
    int i = 0;
    for (Element *temp = _Head; temp != NULL; temp = temp->Next)
    {
        cout << "----------------------------------" << endl;
        cout << "             Звено " << ++i << endl;
        cout << "----------------------------------" << endl;

        cout << (temp->point.type == 0 ? "Поступательная" : "Вращательная") << " кинематическая пара" << endl;

        if (temp->point.q == -1)
            cout << "Параметр q - обобщённая координата" << endl;
        else
            cout << "Параметр q = " << temp->point.q << endl;
        cout << "Параметр alpha = " << temp->point.alpha << endl;
        cout << "Параметр a = " << temp->point.a << endl;
        if (temp->point.d == -1)
            cout << "Параметр d - обобщённая координата" << endl;
        else
            cout << "Параметр d = " << temp->point.d << endl;
    }
}

Element* List::Search(int n)
{
    Element *temp = _Head;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return temp;
}

void List::Delete(int n)
{
    Element *temp = _Head, element;

    if (_Head == _Tail)
    {
        delete _Head;
        _Head = NULL;
        _Tail = NULL;
        return;
    }

    if (n == 1)
    {
        delete _Head;
        _Head = temp->Next;
        return;
    }

    temp = Search(n-1);

    if (temp->Next != Tail)
    {
        element.Next = temp->Next->Next;
        delete temp->Next;
        temp->Next = element.Next;
    }
    else
    {
        delete _Tail;
        temp->Next = NULL;
        _Tail = temp;
    }
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
