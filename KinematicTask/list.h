#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <QtCore/QtCore>

//звенья списка
struct Point
{
    int type;
    float q;
    float alpha;
    float a;
    float d;

    void Input();   //метод для ввода параметров звена
};

//списки
template <class T>
class List {
private:
    struct Element {
        T value;
        Element* Next; //указатель на следующий элемент списка
    };

    Element* Head_;                //голова списка (первый элемент)
    Element* Tail_;                //хвост списка (последний элемент)
    int num_;

public:
    List() : Head_(NULL), Tail_(NULL), num_(0) {};                     //конструктор
    ~List() {
        while (Head_ != NULL) {
            Element* temp = Head_->Next;
            delete Head_;
            Head_ = temp;
        }
    }                    //деструктор

    int NumberOfElements() const {
        return num_;
    }     //возвращает количество элементов.
    bool Empty() {
        return (Head_ == NULL);
    }               //проверка списка на заполненность (true - если список пуст)
    void Add(const T& point) {
        Element* temp = new Element;

        temp->value = point;
        temp->Next = NULL;

        num_++;

        if (Empty()) {
            Head_ = temp;
        } else {
            Tail_->Next = temp;
        }
        Tail_ = temp;
    }  //метод для добавления нового звена в список
    void Show() {
        using namespace std;

        int i = 0;
        for (Element* temp = Head_; temp != NULL; temp = temp->Next) {
            cout << "----------------------------------" << endl;
            cout << "             Звено " << ++i << endl;
            cout << "----------------------------------" << endl;

            cout << (temp->value.type == 0 ? "Поступательная" : "Вращательная") << " кинематическая пара" << endl;

            if (temp->value.q == -1)
                cout << "Параметр q - обобщённая координата" << endl;
            else
                cout << "Параметр q = " << temp->value.q << endl;
            cout << "Параметр alpha = " << temp->value.alpha << endl;
            cout << "Параметр a = " << temp->value.a << endl;
            if (temp->value.d == -1)
                cout << "Параметр d - обобщённая координата" << endl;
            else
                cout << "Параметр d = " << temp->value.d << endl;
        }
    }            //метод для отображения списка
    Element* Search(int n) {
        Element* temp = Head_;
        while (n > 1) {
            temp = temp->Next;
            n--;
        }
        return temp;
    }      //поиск элемента в списке по номеру

    void Delete(int n) {
        Element* temp = Head_, element;

        if (Head_ == Tail_) {
            delete Head_;
            Head_ = NULL;
            Tail_ = NULL;
            return;
        }

        if (n == 1) {
            delete Head_;
            Head_ = temp->Next;
            return;
        }

        temp = Search(n - 1);

        if (temp->Next != Tail_) {
            element.Next = temp->Next->Next;
            delete temp->Next;
            temp->Next = element.Next;
        } else {
            delete Tail_;
            temp->Next = NULL;
            Tail_ = temp;
        }
    }         //метод для удаления элемента из списка по номеру

};

#endif // LIST_H
