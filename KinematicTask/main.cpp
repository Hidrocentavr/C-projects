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
        cin >> point.type;
        if (point.type == 0)
        {
            cout << "Введите параметры Денавита-Хартенберга:" << endl;
            cout << "Параметр q = "; cin >> point.q;
            cout << "Параметр alpha = "; cin >> point.alpha;
            cout << "Параметр a = "; cin >> point.a;
            cout << "Параметр d - обобщённая координата"; point.d = -1;
        }
        else
        {
            cout << "Введите параметры Денавита-Хартенберга (если параметр" << endl;
            cout << "Параметр q - обобщённая координата"; point.q = -1;
            cout << "Параметр alpha = "; cin >> point.alpha;
            cout << "Параметр a = "; cin >> point.a;
            cout << "Параметр d = "; cin >> point.d;
        }
        cout << endl;
    }
};

/*РАБОТА СО СПИСКАМИ ЗВЕНЬЕВ*/
class List
{
    Point *Head;
    Point *Tail;

public:

    int NumberOfPoints = 0;

    List()
    {
        Head = NULL;
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
            cout << (temp->type == 0 ? "Поступательная" : "Вращательная") << " кинематическая пара";
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
            if (!temp)
                return;
        }
        while (n != 2);

        if (temp->Next != Tail)
        {
            temp->Next = temp->Next->Next;
        }

        delete temp->Next;
    }
};

void SayHello()
{
    cout << "Привет!" << endl;
    cout << "Ты запустил программу для решения прямой кинематической задачи манипулятора." << endl;
    cout << "Ниже ты видишь меню, чтобы сделать выбор просто введи номер пункта." << endl;
    cout << "Например, если ты хочешь добавить новое звено манипулятору, то вводи 1." << endl;
    cout << "Удачи!" << endl;
    cout << endl;
}

void ShowMenu()
{
    cout << "МЕНЮ" << endl;
    cout << "==================================================" << endl;
    cout << "1. Добавить новое звено" << endl;
    cout << "2. Удалить звено" << endl;
    cout << "3. Вывести список звеньев на экран" << endl;
    cout << "4. Решить прямую кинематическую задачу о положении" << endl;
    cout << "5. Решить прямую кинематическую задачу о скорости" << endl;
    cout << "6. Выход из программы" << endl;
    cout << "? - вывести меню на экран" << endl;
    cout << "==================================================" << endl;
}

void Menu()
{
    char number;

    cout << "Твой выбор: "; cin >> number;

    switch (number)
    {
    case '1':
        manipulator.NumberOfPoints++;
        Point point;
        cout << "Звено " << manipulator.NumberOfPoints << endl;
        point.Input(point);
        manipulator.Add(point);
        cout << endl << "Звено успешно добавлено!" << endl;
        break;
    case '2':
        manipulator.NumberOfPoints--;
        int n;
        cout << "Введите номер звена: "; cin >> n;
        manipulator.Delete(n);
        cout << endl << "Звено успешно удалено!" << endl;
        break;
    case '3':
        manipulator.Show();
        break;
    case '4':
        cout << "Данный пункт меню находится в разработке." << endl;
        break;
    case '5':
        cout << "Данный пункт меню находится в разработке." << endl;
        break;
    case '6':
        exit(0);
    case '?':
        ShowMenu();
        break;
    default:
        cout << "Ошибка!" << endl;
        break;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(0, "");

    List manipulator;

    SayHello();
    ShowMenu();

    while(true)
    {
        Menu();
    }
    return a.exec();
}
