/*
//в C для реализации модуля необходимо создавать 2 различные функции
int abs(int x);
float fabs(float x);

//в C++ для реализации модуля можно перегружать одну функцию
float abs(int x);
float abs(float x);
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

//интерфейс логгера
class logger //абстрактный класс, так как имеется виртуальный метод
{

public:
    virtual void log(const std::string &message = 0); //виртуальный метод

    void log(const std::exception &ex)
    {
        log(std::string(ex.what()));
    }

    virtual ~logger() {}
};

//реализация консольного логгера
class consolelogger : public logger
{

public:
    void log(const std::string &message) override
    {
        std::cout << message << std::endl;
    }
};

//реализация файлового логгера
class filelogger : public logger
{

public:
    filelogger(const std::string &fileName)
    {
        _file.open(fileName);
    }

    void log(const std::string &message) override
    {
        _file << message << std.endl;
    }

    ~filelogger()
    {
        _file.close();
    }

private:
    std::ofstream _file;
};

class arrlogger : public logger
{
public:
    arrlogger(const std::string &config)
    {
        int count = 2;
        arr = new logger * [2];
        arr[0] = new consolelogger();
        arr[1] = new filelogger("SomeName");
    }

    void log(const std::string &message) override
    {
        for (int i =0; i < count; i++)
        {
            arr[i]->log(message);
        }
    }

    ~arrlogger()
    {
        delete (consolelogger) arr[0];
        delete (filelogger) arr[1];
        delete arr;
    }

private:
    logger **arr;
};

//базовый класс
class Base
{
    //virtual - явное разрешение на переопределение методов
    virtual void method1()
    {
        std::cout << "Base method 1" << std::endl;
    }

    virtual void method2()
    {
        std::cout << "Base method 2" << std::endl;
    }

    virtual void method3() = 0; //чисто виртуальный метод

    virtual void method4() {} //виртуальный метод
};

//класс наследник 1
class Der1 : public Base
{
    void method1() override
    {
        Base::method1(); //явный вызов метода method1 базового класса
        std::cout << "Der method1" << std::endl;
    }
};

//класс наследник 2
class Der2 : public Base
{
    void method2() override
    {
        Base::method2(); //явный вызов метода method2 базового класса
        std::cout << "Der method2" << std::endl;
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

