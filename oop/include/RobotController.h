#pragma once

#include "ApiClient.h"

#include <string>

class RobotController {
public:
    explicit RobotController(ApiClient apiClient);

    void run();
    void moveForward(int speed);
    void moveBackward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    void stop();

private:
    ApiClient apiClient_;
};
