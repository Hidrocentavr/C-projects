//lab 6

template<class T> class MyArray
{
    T* _pointer;
    int _size;

public:
    MyArray(int size)
    {
        _pointer = new T[size];
        _size = size;
    }

    ~MyArray()
    {
        delete[] _pointer;
    }

    void setElem(T value, int index) { _pointer[index] = value; }
    T getElem(int index) { return _pointer[index]; }

    T getMaxElem()
    {
        T max = _pointer[0];

        for (int i = 0; i < _size; i++)
            if (_pointer[i] > max) //для комплексных чисел ошибка возникает в этом месте (>)
                max = _pointer[i];

        return max;
    }

};

struct Complex
{
    float Re, Im;
};

void lab6()
{
    MyArray<int> int_array(5);
    for (int i = 0; i < 5; i++)
    {
        int_array.setElem(-i, i);
    }
    int max = int_array.getMaxElem();

    MyArray<Complex> complex_array(3);
    for (int i = 0; i < 3; i++)
    {
        Complex x = {i, -i};
        complex_array.setElem(x, i);
    }
//    Complex cmax = complex_array.getMaxElem(); //ошибка, так как не определено сравнение комплексных чисел
}

int main()
{


    return 0;
}

