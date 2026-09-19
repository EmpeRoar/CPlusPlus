# C++ .h and .cpp files explained

In C++, a project is usually split into two main file types:

- .h files = header files
- .cpp files = source files

## 1. What is a header file (.h)?
A header file is used to declare the structure of a class or function.
It tells the compiler:
- what functions exist
- what class members exist
- what types are used
- but not necessarily how the logic is implemented

Example:

```cpp
#pragma once

class RobotController {
public:
    void moveForward();
    void moveBackward();
    void stop();
};
```

This file says:
- there is a class named RobotController
- it has methods moveForward, moveBackward, and stop

It does not contain the actual working code.

Use header files for:
- class declarations
- function prototypes
- shared type definitions
- interfaces between files

## 2. What is a source file (.cpp)?
A source file contains the real implementation.
This is where the actual code runs.

Example:

```cpp
#include "RobotController.h"
#include <iostream>

void RobotController::moveForward() {
    std::cout << "Moving forward" << std::endl;
}
```

This file says:
- here is the actual logic for moveForward

Use .cpp files for:
- method definitions
- business logic
- calculations
- HTTP calls
- sensor handling
- robot movement logic

## 3. Why use both?
This is important in C++ projects because it keeps code organized.

The header file gives the blueprint.
The source file gives the implementation.

This helps with:
- cleaner project structure
- easier code reuse
- less duplication
- better team collaboration
- easier maintenance

## 4. In this robot project
This project has:

- include/ApiClient.h
  - declares the ApiClient class
- src/ApiClient.cpp
  - defines how the API client makes GET and POST calls

- include/RobotController.h
  - declares the robot behavior methods
- src/RobotController.cpp
  - defines how the robot moves and responds

- main.cpp
  - is the entry point of the application
  - starts the program and calls the robot logic

## 5. Simple idea
Think of it like this:

- .h file = the recipe card
- .cpp file = the actual cooking instructions

The header tells other files what exists.
The source file tells C++ how it works.

## 6. Example from this project
main.cpp includes the headers:

```cpp
#include "ApiClient.h"
#include "RobotController.h"
```

Then it uses the classes without needing to know the full implementation details.
The compiler knows the interface from the header files, and the linker connects those calls to the actual implementations in the .cpp files.

## 7. Summary
- .h files declare interfaces
- .cpp files implement logic
- together they make modular C++ programs

This is the standard way to organize C++ projects, especially for robot systems and bigger applications.
