#include <iostream>
#include <optional>

using namespace std;

void displayOptions()
{
    cout << "\nSelect what you want to do!" << endl;
    cout << "1. Add a todo item" << endl;
    cout << "2. Display todo list" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice: ";
}

optional<int> getUserInput()
{
    int choice;

    if (cin >> choice)
    {
        return choice;
    }

    // Clear the error state
    cin.clear();

    // Remove invalid input
    cin.ignore(10000, '\n');

    return nullopt;
}

void displayTodoList()
{
    // Placeholder for displaying the todo list
    cout << "Displaying the todo list..." << endl;
    // Logic to display the todo list goes here
}
int main()
{
    optional<int> choice = nullopt;

    while (true)
    {
        displayOptions();

        choice = getUserInput();

        // No valid input
        if (!choice.has_value())
        {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice.value())
        {
            case 1:
                cout << "You chose to add a todo item." << endl;
                // Add todo logic
                break;

            case 2:
                cout << "You chose to display the todo list." << endl;
                displayTodoList();
                break;

            case 3:
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}