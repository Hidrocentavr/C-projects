//в C для реализации модуля необходимо создавать 2 различные функции
int abs(int x);
float fabs(float x);

//в C++ для реализации модуля можно перегружать одну функцию
float abs(int x);
float abs(float x);

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

//базовый класс
class Base
{
    //virtual - явное разрешение на переопределение методов
    virtual void method1()
    {
        cout << "Base method 1" << endl;
    }

    virtual void method2()
    {
        cout << "Base method 2" << endl;
    }
};

//класс наследник 1
class Der1 : public Base
{
    void method1() override
    {
        Base::method1(); //явный вызов метода method1 базового класса
        cout << "Der method1" << endl;
    }
};

//класс наследник 2
class Der2 : public Base
{
    void method2() override
    {
        Base::method2(); //явный вызов метода method2 базового класса
        cout << "Der method2" << endl;
    }
};

void polymorth(Base *x)
{
    x->method1();
}

void test()
{
    Der1 der1;
    Der2 der2;

    polymorth(&der1);
    polymorth(&der2);
}

int main()
{



    return 0;
}

