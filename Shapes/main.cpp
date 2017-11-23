#include <iostream>
#include <math.h>
#include <list>

//Точка
class Point
{
    float _x;
    float _y;

public:
    Point(float x, float y) : _x(x), _y(y) {}
    Point() : _x(0), _y(0) {}
    ~Point() {}

    float getX() { return _x; }
    float getY() { return _y; }

    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }

    Point getXY()
    {
        Point a(_x, _y);
        return a;
    }

    void setXY(float x, float y)
    {
        _x = x;
        _y = y;
    }
};

//Фигура
class Figure
{
protected:
    float _square;    
    std::string _name;
    Point _center;

    Figure() {}

public:
    void move(Point to) { _center = to; }
    void move(float x, float y) { _center.setXY(x, y); }
    Point where() { return _center; }
    float getSquare() { return _square; }
    std::string getName() { return _name; }
};

//Круг
class Circle : public Figure
{
    float _radius;

public:
    Circle(float r) : _radius(r), _center(0, 0), _name("circle")
    {
        _square = r*r*3.14;
    }

    float getRadius() { return _radius; }
    bool operator > (Figure b)
    {
        if (this->getSquare() > b.getSquare())
            return true;
        else
            return false;
    }
    bool operator < (Figure b)
    {
        if (this->getSquare() < b.getSquare())
            return true;
        else
            return false;
    }
    bool operator == (Figure b)
    {
        if (this->getSquare() == b.getSquare())
            return true;
        else
            return false;
    }
};

//Прямоугольник
class Rectangle : public Figure
{
    float _length;
    float _width;

public:
    Rectangle(float l, float w) : _length(l), _width(w), _square(l*w), _center(0, 0), _name("rectangle") {}
    float getLength() { return _length; }
    float getWidth() { return _width; }
};

//Треугольник
/*class Triangle : public Figure
{
    float _side;

public:
    Triangle(float a) : _side(a), _square(sqrt(3)/4*pow(a, 2)), _center(0, 0), _name("triangle") {}
    float getSide() { return _side; }
};

//самая большая фигура
Figure& maxSquare(std::list& l)
{
    Figure maxS = l.begin();
    for (std::list<Figure>::iterator i = l.begin(); i != l.end(); i++)
    {
        if (maxS > i)
            maxS = i;
    }
    return maxS;
}

//расстояние между точками
float Distance(Point a, Point b)
{
    return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}

//самая удалённая фигура
Figure& maxDistance(std::list& l, Point point)
{
    Figure maxD = l.begin();
    float distance = Distance(maxD.where(), point);

    fot(auto iter = l.begin(); iter != l.end(); ++iter)
    {
       (*iter)->

       int a=0;
       int b = a++;
    }

    for (Figure* i : l)
    {
        d = Distance(i.where(), point);
        if (d > distance)
        {
            maxD = i;
            distance = d;
        }
    }
    return maxD;
}*/

int main()
{
/*    std::list<Figure> l;

    Circle a(5);
    a.move(10, 10);
    l.push_back(a);

    Rectangle b(4, 2);
    b.move(-10, -10);
    l.push_back(b);

    Triangle c(6);
    c.move(-10, 10);
    l.push_back(c);

    Point myPoint(1, 1);

    std::cout << "Max square has " << maxSquare(l).getName() << std::endl;
    std::cout << "Max distance has " << maxDistance(l, myPoint).getName() << std::endl;
*/
    return 0;
}

