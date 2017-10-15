#include <iostream>
#include "list.h"

using namespace std;

void Point::Input()
{
    cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
    cin >> type;
    if (type == 0)
    {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q = "; cin >> q;
        cout << "Параметр alpha = "; cin >> alpha;
        cout << "Параметр a = "; cin >> a;
        cout << "Параметр d - обобщённая координата" << endl; d = -1;
    }
    else
    {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q - обобщённая координата" << endl; q = -1;
        cout << "Параметр alpha = "; cin >> alpha;
        cout << "Параметр a = "; cin >> a;
        cout << "Параметр d = "; cin >> d;
    }
}

List::List() : Head_(NULL), Tail_(NULL), num_(0)
{

}

List::~List()
{
    while (Head_ != NULL)
    {
        Element *temp = Head_->Next;
        delete Head_;
        Head_ = temp;
    }
}

int List::NumberOfElements()
{
    return num_;
}

bool List::Empty()
{
    return (Head_ == NULL);
}

void List::Add(Element element)
{
    Element *temp = new Element;

    temp->point = element.point;
    temp->Next = NULL;

    num_++;

    if (Empty())
    {
        Head_ = temp;
    }
    else
    {
        Tail_->Next = temp;
    }
    Tail_ = temp;
}

void List::Show()
{
    int i = 0;
    for (Element *temp = Head_; temp != NULL; temp = temp->Next)
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
    Element *temp = Head_;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return temp;
}

void List::Delete(int n)
{
    Element *temp = Head_, element;

    if (Head_ == Tail_)
    {
        delete Head_;
        Head_ = NULL;
        Tail_ = NULL;
        return;
    }

    if (n == 1)
    {
        delete Head_;
        Head_ = temp->Next;
        return;
    }

    temp = Search(n-1);

    if (temp->Next != Tail_)
    {
        element.Next = temp->Next->Next;
        delete temp->Next;
        temp->Next = element.Next;
    }
    else
    {
        delete Tail_;
        temp->Next = NULL;
        Tail_ = temp;
    }
}
