#include "RobotController.h"

#include <iostream>
#include <string>

RobotController::RobotController(ApiClient apiClient)
    : apiClient_(std::move(apiClient)) {}

void RobotController::moveForward(int speed) {
    std::cout << "Driving forward at speed " << speed << std::endl;
}

void RobotController::moveBackward(int speed) {
    std::cout << "Driving backward at speed " << speed << std::endl;
}

void RobotController::turnLeft(int speed) {
    std::cout << "Turning left at speed " << speed << std::endl;
}

void RobotController::turnRight(int speed) {
    std::cout << "Turning right at speed " << speed << std::endl;
}

void RobotController::stop() {
    std::cout << "Stopping robot." << std::endl;
}

void RobotController::run() {
    std::cout << "Raspberry Pi robot starting..." << std::endl;

    const std::string status = R"({"status":"online","battery":92,"speed":50})";
    std::cout << "Posting status: " << status << std::endl;
    std::string response = apiClient_.post("https://example.com/robot/status", status);
    std::cout << "Status response: " << response << std::endl;

    std::cout << "Checking for remote command..." << std::endl;
    std::string command = apiClient_.get("https://example.com/robot/command");

    if (command.find("forward") != std::string::npos) {
        moveForward(60);
    } else if (command.find("backward") != std::string::npos) {
        moveBackward(60);
    } else if (command.find("left") != std::string::npos) {
        turnLeft(50);
    } else if (command.find("right") != std::string::npos) {
        turnRight(50);
    } else {
        stop();
    }
}
