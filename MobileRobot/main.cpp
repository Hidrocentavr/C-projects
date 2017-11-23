#include <iostream>
#include <vector>

class Link;
class State;
class Automate
{
private:
    std::vector<State*> _states;
    State* _currentState;

public:
    float calculateOutput (int input);

};

int main()
{

}