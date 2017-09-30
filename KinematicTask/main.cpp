#include <QCoreApplication>
#include <iostream>

using namespace std;

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
};*/

/*//Решатель
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
};*/

/*ЗВЕНО*/
struct Point
{
    int type;
    float q;
    float alpha;
    float a;
    float d;
    Point *Next;

    void Input(Point &point)
    {
        cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
        cin >> point.type >> endl;
        if (point.type == 0)
        {
            cout << "Введите параметры Денавита-Хартенберга:" << endl;
            cout << "Параметр q = "; cin >> point.q >> endl;
            cout << "Параметр alpha = "; cin >> point.alpha >> endl;
            cout << "Параметр a = "; cin >> point.a >> endl;
            point.d = -1; //-1 - обобщённая координата
        }
        else
        {
            cout << "Введите параметры Денавита-Хартенберга (если параметр" << endl;
            cout << "Параметр alpha = "; cin >> point.alpha >> endl;
            cout << "Параметр a = "; cin >> point.a >> endl;
            cout << "Параметр d = "; cin >> point.d >> endl;
            point.q = -1; //-1 - обобщённая координата
        }
    }
};

/*РАБОТА СО СПИСКАМИ ЗВЕНЬЕВ*/
class List
{
    Point *Head;
    Point *Tail;

public:
    List()
    {
        Head = NULL;
        Head->Next = Tail;
        Tail = NULL;
    }

    ~List()
    {
        while (Head != NULL)
        {
            Point *temp = Head->Next;
            delete Head;
            Head = temp;
        }
    }

    bool Empty()
    {
        return (Head == NULL);
    }

    void Add(Point &point)
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

    void Show()
    {
        Point *temp = Head;

        while (temp != NULL)
        {
            cout << temp->type << endl;
            cout << temp->a << endl;
            cout << temp->alpha << endl;
            cout << temp->d << endl;
            cout << temp->q << endl;

            temp = temp->Next;
        }
    }

    void Delete(int n)
    {
        Point *temp = Head;

        if (Head == Tail)
        {
            List();
            return;
        }

        if (n == 1)
        {
            Head = temp->Next;
            delete temp;
            return;
        }

        do
        {
            temp = temp->Next;
            n--;
            if (temp=NULL) return;
        }
        while (n != 2);

        if (temp->Next != Tail)
        {
            temp->Next = temp->Next->Next;
        }

        delete temp->Next;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(0, "");

    cout << "Hello world!" << endl;
    manipulator::input();
    cout << "The end!" << endl;

    return a.exec();
}
