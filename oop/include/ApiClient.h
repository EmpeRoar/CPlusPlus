#pragma once

#include <string>

class ApiClient {
public:
    std::string get(const std::string& url) const;
    std::string post(const std::string& url, const std::string& body) const;
};
