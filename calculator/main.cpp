#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to our calculator!" << endl;

    cout << "Please enter two numbers: ";
    double num1, num2;

    cin >> num1 >> num2;

    cout << "Please enter an operator (+, -, *, /): ";
    char op;
    cin >> op;

    double result;
    switch(op) {

        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if(num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "Error: Division by zero!";
                return 1;
            }
            break;
        default:
            cout << "Error: Invalid operator!";
            return 1;
    }

    cout << "Result: " << result;
    cout << "\n";


    return 0;
}