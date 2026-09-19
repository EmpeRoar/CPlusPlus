#include <iostream>
#include "Rectangle.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    string variableName = "";

    cin >> variableName;
    cout << variableName << endl;

    const int LIGHT_SPEED = 299792458;


    float area = 64.74;
    double volume = 134.64;

    char test = 'x';

    const Rectangle RECT = Rectangle(5.0, 10.0);
    cout << "Area of the rectangle: " << RECT.area() << endl;

    return 0;
}

