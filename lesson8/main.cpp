/* Пространства имён, потоки, исключения, const */

#include <iostream>
#include <functional>
#include <fstream>
#include <string>

namespace lab8
{
    int func() {return 0;}
    namespace Inner
    {
        struct SomeStruct {};
    }

}

using lab8::func;

//tsypedef std::shared_ptr<std::function<int(float*)>> FuncP;

//Исключения
namespace My
{

    struct Exception : std::exception
    {
        const char* what() const noexcept override
        {
            return "Something wrong!";
        }
    };

}

//const
void somefunc(const std::string& a)
{

}

class MyClass
{
public:
    int a;
    void method() const
    {
//        a = 3; //error
    }
    void nonconst()
    {
        a = 3;
    }
};

int main()
{
    //Пространства имён
//    lab8::func();

//    lab8::Inner::SomeStruct x;

    //Потоки
    std::cout << "SomeString" << std::endl;
    std::cerr << "Error";
    int x;
    std::cin >> x;

    std::ofstream f;
    f.open("file_path");

    f << "FirstString" << std::endl;

    f.close();

//    std::sstream s;

    //Исключения
    try
    {

    }

    catch (std::exception& ex)
    {

    }

    catch (My::Exception& ex)
    {
        ///
        std::cerr << ex.what();
    }

    catch (...)
    {

    }

    throw My::Exception();

    //const
    int a;
    std::cin >> a;

    const int b = a;
//    b = 3; будет ошибка!

    const int* const ptr1 = &b; //константный указатель на константу
    const int* ptr2; //указатель на константу
    ptr2 = &a;
//    *ptr = 3; //error

    int* const ptr3 = &c;
    *ptr3 = 4;
//    ptr3 = nullptr; //error

    somefunc("asdas");
    std::string xstr = "safdxz";
    somefunc(xstr);

    const MyClass instance;
    instance.method();
//    instance.nonconst(); //error (unexpected behavior)

    const int dang = 5;
//    *((int*)&dang) = 7; //error

    const int dang = 5 * std::_Pow_int(2, 3);
//    float array[dang]; //error

    return 0;
}

