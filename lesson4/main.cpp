//в C для реализации модуля необходимо создавать 2 различные функции
int abs(int x);
float fabs(float x);

//в C++ для реализации модуля можно перегружать одну функцию
float abs(int x);
float abs(float x);

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//базовый класс
class Base
{
    void method1();
    void method2();
};

//класс наследник 1
class Der1 : public Base
{

};

//класс наследник 2
class Der2 : public Base
{

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

