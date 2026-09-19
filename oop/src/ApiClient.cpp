#include "ApiClient.h"

#include <array>
#include <cstdio>
#include <sstream>
#include <stdexcept>

namespace {
std::string execCommand(const std::string& command) {
    std::array<char, 4096> buffer{};
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Failed to execute command.");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        result += buffer.data();
    }

    const int exitCode = pclose(pipe);
    if (exitCode != 0 && exitCode != -1) {
        return result;
    }

    return result;
}
} // namespace

std::string ApiClient::get(const std::string& url) const {
    std::stringstream command;
    command << "curl -sS -L \"" << url << "\"";
    return execCommand(command.str());
}

std::string ApiClient::post(const std::string& url, const std::string& body) const {
    std::stringstream command;
    command << "curl -sS -L -X POST -H \"Content-Type: application/json\" --data \""
            << body << "\" \"" << url << "\"";
    return execCommand(command.str());
}
