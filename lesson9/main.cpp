//Занятие 9. Константы компилирования. Неоднозначные (опасные!) возможности языка.
#include <iostream>

//Константы компилирования
constexpr int c = 3 * 7;

constexpr int pow_int(int x, int p) //данная функция вычисляется на этапе компиляции
{
    return p>1?pow_int(x,p-1)*x:x;
}

constexpr int x = 5 * pow_int(2,5);

char array[x];

//Неоднозначные (опасные!) возможности языка. Использовать очень аккуратно!
//Ничто не должно помешать программисту выстрелить себе в ногу.
//1. Дружба (Friendship); (Может использоваться для фабрик, модифаеров)
class A
{
    int _x;

public:

    friend class B;

    friend int f(const A &a); //функция, не метод класса
};

class B
{
    int y;

public:
    B(const A &a):y(a._x)
    {

    }
};

int f(const A &a)
{
    return a._x;
}

//2. Перегрузка операторов. Можно перегружать операторы только для пользовательских типов!!!;

//2.1. Операторы, безопасные для перегрузки:

// a) [==, !=, >, <, <=, >=]
///int cnp(const A &x, const A &y);

// b) [=]
/// A a;
/// A b(a); //конструктор копирования
/// A c = a; //конструктор копирования
/// b = c; //оператор присваивания

// c) приведение типа

//2.2. Операторы, которые стоит перегружать с осторожностью:

// a) [+, -, un+, un-, *, /, %, &, |, +=, &=, *=, []] //un - унарный

// b) псевдосинтаксис (только для больших библиотек или общепринятых неявных интерфейсов)
// << >> - яркий пример перегрузки операторов побитового сдвига в библиотеке std
// *a - используется для разименования умных указателей, включая итераторы (неявный общий интерфейс)
// () - функторы
///vector<int> v; // для библиотеки boost
///v += 1, 2, 3, 5, 0; // перегрузка оператора ,
///int a = std::cout << "Hello, World!", 5; //антипаттерн!

class C
{
    int x;

public:
    bool operator == (const C& right)
    {
        return this->x == right.x;
    }

    /*
    bool operator != (const C& right)
    {
        return !(*this == right);
    }

    C operator+ (int right)
    {
        C res = *this;
        res.x += right;
        return res;
    }*/

    friend C operator+ (int left, const C& right);
};

/*bool operator != (const C& left, const C& right)
{
    return !(left == right);
}*/

C operator+ (int left, const C& right)
{
    C res = right;
    res.x += left;
    return res;
}

//Проблема
C a;
C aaa = 3 + a;

//Приведение типов
float a1 = 4; //неявное приведение типов (inplicit)
int x1 = (int)5.2; //явное приведение типов (explicit)
int a2 = 7;
const int* ptr = &a2;

*ptr;

//Операторы приведения:

// a) static_cast<type>(exp)
int x2 = static_cast<int>(5.2); //вызывает перегруженные + системные приведения

// b) dynamic_cast<DerRefType>(BaseRef)
class Base
{
   virtual void f() = 0;
};

class Der:Base
{
    void f() {}
};
void f(Base *a)
{
    Der* b = dynamic_cast<Der*>(a); //приведение указателей (рефлексия)
}

// c) reinterpret_cast<type>(exp) //подменяет тип, а все байты остаются неизменными, работает только для указателей
struct X
{
    int a;
};

struct Y
{
    int b;
};

struct Z
{
    char array[4];
};

X xas = {3};
Y* yas = reinterpret_cast<Y*>(&xas);
Z* zas = reinterpret_cast<Z*>(&yas);

// d) const_cast<non_const_type>(const_value) //удаляет константность

int main()
{

}
