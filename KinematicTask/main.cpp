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
};*/

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

    void Input(Point &point);

    Point *Next;
};

/*РАБОТА СО СПИСКАМИ ЗВЕНЬЕВ*/
class List
{
    Point *Head;

public:
    List()
    {
        Head = NULL;
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

    void Add(Point &point)
    {
        Point *temp = new Point;
        temp->Next = Head;

        temp->type = point.type;
        temp->a = point.a;
        temp->alpha = point.alpha;
        temp->d = point.d;
        temp->q = point.q;

        Head = temp;
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

    void Remove()
    {
        Po
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
