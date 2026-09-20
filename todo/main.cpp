#include <iostream>
#include <array>
#include <string>

using namespace std;

void displayList(array<string, 100> todos, int todoCount) {
    cout << "Todo List:" << endl;
    for(int i = 0; i < todoCount; i++) {
        cout << i + 1 << ". " << todos[i] << endl;
    }
}

int main() {

   array<string, 100> todos;
   int todoCount = 0;

   while(true) {
    cout << "Enter a todo Item: ";
    string todo;
    getline(cin, todo); // To consume the newline character after the first input
    todos[todoCount] = todo;
    todoCount++;


    displayList(todos, todoCount);
   }

    return 0;
}