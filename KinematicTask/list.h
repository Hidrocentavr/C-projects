#ifndef LIST_H
#define LIST_H

template <class T> struct Element
{
    T point;
    Element *Next; //указатель на следующий элемент списка
};

//списки
template <class T> class List
{
private:
    Element<T> *Head_;                //голова списка (первый элемент)
    Element<T> *Tail_;                //хвост списка (последний элемент)
    int num_;

public:
    List();                     //конструктор
    ~List();                    //деструктор

    int numberOfElements();     //возвращает количество элементов.
    bool empty();               //проверка списка на заполненность (true - если список пуст)
    void add(T &element);  //метод для добавления нового звена в список
//    void show();                //метод для отображения списка
    T* search(int);      //поиск элемента в списке по номеру
    void del(int);         //метод для удаления элемента из списка по номеру

};

template <class T> List<T>::List() : Head_(nullptr), Tail_(nullptr), num_(0)
{

}

template <class T> List<T>::~List()
{
    while (Head_ != nullptr)
    {
        Element<T> *temp = Head_->Next;
        delete Head_;
        Head_ = temp;
    }
}

template <class T> int List<T>::numberOfElements()
{
    return num_;
}

template <class T> bool List<T>::empty()
{
    return (Head_ == nullptr);
}

template <class T> void List<T>::add(T &element)
{
    Element<T> *temp = new Element<T>;

    temp->point = element;
    temp->Next = nullptr;

    num_++;

    if (empty())
    {
        Head_ = temp;
    }
    else
    {
        Tail_->Next = temp;
    }
    Tail_ = temp;
}

template <class T> T *List<T>::search(int n)
{
    Element<T> *temp = Head_;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return &(temp->point);
}

template <class T> void List<T>::del(int n)
{
    Element<T> *temp = Head_, element;

    if (Head_ == Tail_)
    {
        delete Head_;
        Head_ = nullptr;
        Tail_ = nullptr;
        return;
    }

    if (n == 1)
    {
        delete Head_;
        Head_ = temp->Next;
        return;
    }

    temp->point = *search(n-1);

    if (temp->Next != Tail_)
    {
        element.Next = temp->Next->Next;
        delete temp->Next;
        temp->Next = element.Next;
    }
    else
    {
        delete Tail_;
        temp->Next = nullptr;
        Tail_ = temp;
    }
}

#endif // LIST_H
