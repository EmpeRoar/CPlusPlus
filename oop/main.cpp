#include "ApiClient.h"
#include "RobotController.h"

#include <iostream>

int main() {
    try {
        ApiClient apiClient;
        RobotController robot(apiClient);
        robot.run();
    } catch (const std::exception& ex) {
        std::cerr << "Robot error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
