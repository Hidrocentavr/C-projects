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
    Point *Next;                //указатель на следующий элемент списка

    void Input(Point &point);   //метод для ввода параметров звена
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
    int NumberOfPoints = 0;

    List();                     //конструктор
    ~List();                    //деструктор

    bool Empty();               //проверка списка на заполненность (true - если список пуст)
    void Add(Point &point);     //метод для добавления нового звена в список
    void Show();                //метод для отображения списка
    Point *Search(int n);       //поиск элемента в списке по номеру
    void Delete(int n);         //метод для удаления элемента из списка по номеру
    Matrix *AMatrix(float q, float alpha, float a, float d); //матрица переноса A
    Matrix *Solver(Sensor encoder); //решатель
};

//матрицы
class Matrix
{
private:

public:
    int rows_, cols_;
    double* data_;

    Matrix(int rows, int cols); //конструктор прямоугольной матрицы
    Matrix(int n);              //конструктор кавдратной матрицы
    ~Matrix();                  //деструктор

    double& operator() (int row, int col);    //перегрузка оператора ()
    Matrix& operator= (Matrix& m);            //перегрузка оператора =
    Matrix& operator+ (Matrix& m);            //перегрузка оператора +
    Matrix& operator* (Matrix& m);            //перегрузка оператора *

    void show();
};

void SayHello();                //приветствие
void ShowMenu();                //описание меню
void Menu();                    //реализация меню

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

Point* List::Search(int n)
{
    Point *temp = Head;
    while(n > 1)
    {
        temp = temp->Next;
        n--;
    }
    return temp;
}

void List::Delete(int n)
{
    Point *temp = Head, element;

    if (Head == Tail)
    {
        Head = NULL;
        Tail = NULL;
        return;
    }

    if (n == 1)
    {
        delete Head;
        Head = temp->Next;
        return;
    }

    temp = Search(n-1);

    if (temp->Next != Tail)
    {
        element.Next = temp->Next->Next;
        delete temp->Next;
        temp->Next = element.Next;
    }
    /* else
    {
        element = temp->Next;
        delete element;
        temp->Next = NULL;
    }*/
}

Matrix& List::AMatrix(float q, float alpha, float a, float d)
{
    Matrix A(4);
    A.data_ =
    {
        {cos(q), -cos(alpha)*sin(q), sin(alpha)*sin(q), a*cos(q)},
        {sin(q), cos(alpha)*cos(q), -sin(alpha)*cos(q), a*sin(q)},
        {0, sin(aplha), cos(alpha), d},
        {0, 0, 0, 1}
    };
    return A;
}

Matrix& List::Solver(Sensor encoder)
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
}

//-------
//МАТРИЦЫ
//-------
inline
Matrix::Matrix(int rows, int cols) : rows_ (rows), cols_ (cols)
{
    if (rows == 0 || cols == 0)
        cout << "Matrix constructor has 0 size" << endl;
    this->data_ = new double[rows * cols];
}

inline
Matrix::Matrix(int n) : rows_ (n), cols_ (n)
{
    if (n == 0)
        cout << "Matrix constructor has 0 size" << endl;
    this->data_ = new double[n * n];
}

inline
Matrix::~Matrix()
{
    delete[] this->data_;
}

inline
Matrix& Matrix::operator= (Matrix& m)
{
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < this->cols_; j++)
            this->data_[this->cols_*i+j] = m.data_[this->cols_*i+j];
    return *this;
}

inline
Matrix& Matrix::operator= (int k)
{
    this->data_ = {0};
    for(int i = 0, j = 0; i < this->rows_; i++, j++)
    {
        this->data_[this->cols_*i+j] = k;
    }
    return *this;
}

Matrix& Matrix::operator+ (Matrix& m)
{
    Matrix tmp(m.rows_, m.cols_);
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < this->cols_; j++)
            tmp.data_[this->cols_*i+j] = this->data_[this->cols_*i+j] + m.data_[this->cols_*i+j];
    return tmp;
}

Matrix& Matrix::operator* (Matrix& m)
{
    Matrix tmp(this->rows_, m.cols_);
    for(int i = 0; i < this->rows_; i++)
        for(int j = 0; j < m.cols_; j++)
            for(int k = 0; k < this->cols_; k++)
                tmp.data_[tmp.cols_*i+j] += this->data_[this->cols_*i+k] * m.data_[m.cols_*k+j];
    return tmp;
}

inline
void Matrix::show()
{
    for(int i = 0; i < this->rows_; i++)
    {
        for(int j = 0; j < this->cols_; j++)
            cout << this->data_[this->cols_*i+j] << " ";
        cout << endl;
    }
}


//---------
//ИНТЕРФЕЙС
//---------
inline
void SayHello()
{
    cout << "Привет!" << endl;
    cout << "Ты запустил программу для решения прямой позиционной задачи." << endl;
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
        Sensor encoder;
        manipulator.Solver(encoder);
        cout << "Матрица T успешно вычислена!" << endl;
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
};

//-------
//ДАТЧИКИ
//-------
inline
void Sensor::Input(Sensor encoder, List mp)
{
    cout << "Введите обобщённые координаты";
    for (int i = 0; i < mp.NumberOfPoints; i++)
        cout << "Звено " << i << ":"; cin >> encoder.data[i];
}
*/
