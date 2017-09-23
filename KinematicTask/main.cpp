#include <QCoreApplication>
#include <iostream>

using namespace std;

const float q_value[] = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

class MyTime
{
private:
    int time_ms;

public:

};

class Sensors
{
private:

public:
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

class RobotArmSolver
{
private:
    int number_of_points;
    int point[][];

public:
    //вычисление матрицы перехода по известным обобщённым координатам
    float SolveDirectKinematic(float* q)
    {
        T = q; //вычисление матрицы
        return T;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(0, "");

    cout << "Hello world!" << endl;




    return a.exec();
}
