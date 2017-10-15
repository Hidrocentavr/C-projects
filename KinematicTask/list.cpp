#include <iostream>
#include "list.h"

using namespace std;

void Point::Input() {
    cout << "Тип кинематической пары (0 - поступательная, 1 - вращательная): ";
    cin >> type;
    if (type == 0) {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q = ";
        cin >> q;
        cout << "Параметр alpha = ";
        cin >> alpha;
        cout << "Параметр a = ";
        cin >> a;
        cout << "Параметр d - обобщённая координата" << endl;
        d = -1;
    } else {
        cout << "Введите параметры Денавита-Хартенберга:" << endl;
        cout << "Параметр q - обобщённая координата" << endl;
        q = -1;
        cout << "Параметр alpha = ";
        cin >> alpha;
        cout << "Параметр a = ";
        cin >> a;
        cout << "Параметр d = ";
        cin >> d;
    }
}