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
    Point *Next;                //указатель на следующий элемент списка

    void Input(Point &point);   //метод для ввода параметров звена
};

struct Element //элемент списка, а point - значение этого элемента
{

};

//датчики
struct Sensor
{
    int data[10] = {0};

    //    void Input(Sensor encoder, List mp);   //метод для получения данных с датчиков
};


//списки
class List
{
protected:
    Point *Head;                //голова списка (первый элемент)
    Point *Tail;                //хвост списка (последний элемент)

public:
    int NumberOfPoints = 0; //NumberOfElements (перенести в метод)

    List();                     //конструктор
    ~List();                    //деструктор

    bool Empty();               //проверка списка на заполненность (true - если список пуст)
    void Add(Point &point);     //метод для добавления нового звена в список
    void Show();                //метод для отображения списка
    Point* Search(int n);       //поиск элемента в списке по номеру
    void Delete(int n);         //метод для удаления элемента из списка по номеру

    //определить в новый класс

//    Matrix AMatrix(float q, float alpha, float a, float d); //матрица переноса A
//    Matrix Solver(Sensor encoder); //решатель
};

#endif // LIST_H
