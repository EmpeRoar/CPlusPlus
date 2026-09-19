cmake_minimum_required(VERSION 3.16)
project(RaspberryPiRobot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(robot_app
    main.cpp
    src/ApiClient.cpp
    src/RobotController.cpp
)

target_include_directories(robot_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
