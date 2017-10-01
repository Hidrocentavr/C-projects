#include <QCoreApplication>
#include <iostream>
#include <stdio.h>

using namespace std;

/*=============== ОСНОВНЫЕ ЭЛЕМЕНТЫ ПРОГРАММЫ ===============*/

//звенья списка
struct Point
{
    int type;
    float q;
    float alpha;
    float a;
    float d;
    Point *Next;

    void Input(Point &point);
};

//списки
class List
{
protected:
    Point *Head;
    Point *Tail;

public:
    int NumberOfPoints = 0;

    List();
    ~List();

    bool Empty();
    void Add(Point &point);
    void Show();
    Point Search(int n);
    void Delete(int n);
};

//матрицы
class Matrix
{
private:
    unsigned rows_, cols_;
    double* data_;

public:
    Matrix(unsigned rows, unsigned cols);
    Matrix(const Matrix& m);
    ~Matrix();

    double& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
    double  operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs
    Matrix& operator= (const Matrix& m);                    // Assignment operator
    Matrix operator+(Matrix obj);
    Matrix operator*(Matrix obj);

    void show();
};

void SayHello();//приветствие
void ShowMenu();//описание меню
void Menu();//реализация меню

/*=============== ГЛАВНАЯ ФУНКЦИЯ ===============*/

List manipulator;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(0, "");

    SayHello();
    ShowMenu();

    while(true)
    {
        Menu();
    }
    return a.exec();
}

/*=============== ОПИСАНИЕ ФУНКЦИЙ, МЕТОДОВ, КОНСТРУКТОРОВ И ВСЕГО ОСТАЛЬНОГО ===============*/

//-------------
//ЗВЕНЬЯ СПИСКА
//-------------
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

//------
//СПИСКИ
//------
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

Point List::Search(int n)
{
    Point *temp = Head;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return *temp;
}

void List::Delete(int n)
{
    Point *temp = Head;

    if (Head == Tail)
    {
        delete temp;
        return;
    }

    if (n == 1)
    {
        Head = temp->Next;
        delete temp;
        return;
    }

    //temp = List.Search(n-1);

    if (temp->Next != Tail)
    {
        temp->Next = temp->Next->Next;
    }

    delete temp->Next;
}

//-------
//МАТРИЦЫ
//-------
inline
Matrix::Matrix(unsigned rows, unsigned cols) : rows_ (rows), cols_ (cols)
{
    if (rows == 0 || cols == 0)
        cout << "Matrix constructor has 0 size" << endl;
    data_ = new double[rows * cols];
}

inline
Matrix::~Matrix()
{
    delete[] data_;
}

inline
double& Matrix::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        cout << "Matrix subscript out of bounds" << endl;
    return data_[cols_*row + col];
}

inline
double Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        cout << "const Matrix subscript out of bounds" << endl;
    return data_[cols_*row + col];
}

/*Matrix Matrix::operator+(Matrix obj)
{
    Matrix tmp(0);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            tmp[i][j] = matr[i][j] + obj[i][j];
    return tmp;
}*/

/*Matrix Matrix::operator*(Matrix obj)
{
    Matrix tmp(0);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                tmp[i][j] += matr[i][k] * obj[k][j];
    return tmp;
}*/

/*inline
void Matrix::show()
{
    for(int i = 0; i < rows_; i++)
    {
        for(int j = 0; j < cols_; j++)
            printf("%3d",matr[i][j]);
        cout << endl;
    }
}*/


//---------
//ИНТЕРФЕЙС
//---------
inline
void SayHello()
{
    cout << "Привет!" << endl;
    cout << "Ты запустил программу для решения прямой кинематической задачи манипулятора." << endl;
    cout << "Ниже ты видишь меню, чтобы сделать выбор просто введи номер пункта." << endl;
    cout << "Например, если ты хочешь добавить новое звено манипулятору, то вводи 1." << endl;
    cout << "Удачи!" << endl;
    cout << endl;
}

inline
void ShowMenu()
{
    cout << "МЕНЮ" << endl;
    cout << "==================================================" << endl;
    cout << "1. Добавить новое звено" << endl;
    cout << "2. Удалить звено" << endl;
    cout << "3. Вывести список звеньев на экран" << endl;
    cout << "4. Решить прямую позиционную задачу" << endl;
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

/*=============== ЗАДУМКИ, КОТОРЫЕ ЕЩЁ МОГУТ ПРИГОДИТЬСЯ ===============*/

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
};

class Solver : public List
{
public:
    float AMatrix(int n)
    {
        Point point;
        point = List.Search(n);
        float A[4][4]={
            {cos(point.q), -cos(point.alpha)*sin(q), sin(point.alpha)*sin(point.q), a*cos(point.q)},
            {sin(point.q), cos(point.alpha)*cos(point.q), -sin(point.alpha)*cos(point.q), a*sin(point.q)},
            {0, sin(point.aplha), cos(point.alpha), point.d},
            {0, 0, 0, 1}
        };
        return A;
    }

    float TMatrix()
    {
        Point point = Head;
        float T[4][4] = AMatrix(point);

        while (point.Next)
        {
            T = T * AMatrix(point.Next);
            point = point.Next;
        }
        return T;
    }
};

//Решатель
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
