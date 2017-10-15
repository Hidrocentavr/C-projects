#ifndef LIST_H
#define LIST_H

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

struct Element
{
    Point point;
    Element *Next; //указатель на следующий элемент списка
};

//списки
class List
{
private:
    Element *Head_;                //голова списка (первый элемент)
    Element *Tail_;                //хвост списка (последний элемент)
    int num_;

public:
    List();                     //конструктор
    ~List();                    //деструктор

    int NumberOfElements();     //возвращает количество элементов.
    bool Empty();               //проверка списка на заполненность (true - если список пуст)
    void Add(Element element);  //метод для добавления нового звена в список
    void Show();                //метод для отображения списка
    Element* Search(int n);      //поиск элемента в списке по номеру
    void Delete(int n);         //метод для удаления элемента из списка по номеру

};

#endif // LIST_H
