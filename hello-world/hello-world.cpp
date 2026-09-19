#include <iostream>
using namespace std;

int main() {
    cout << "Hello, \n World!" << endl;
    cout << "This is a simple C++ program." << endl;
    cout << 3 << endl;
    string cool;
    cin >> cool;
    cout << 3 + 3 << endl;
    cout << 2 * 5 << endl;
    cout << cool << endl;

    int day = 4;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Invalid day" << endl;
    }
    return 0;
}
