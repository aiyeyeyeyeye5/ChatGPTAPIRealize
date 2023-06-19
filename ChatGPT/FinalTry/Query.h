#pragma once
#include<vector>
#include<string>
#include<iostream>
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include"my_curl_function.h"


class Query {
    std::vector < std:: string > sinQur;
public:
    Query(const std::string& s);
    std::string tot();
    void addUser(const std::string& s);
    void addAnser(const std::string& s);
    std::pair<std::string, std::string> qur2message(const std::string& s);
    void show();
    void showSingle();
    void post(int port, std::string modle, std::string key);
    std::string  getTitle();
    int size() { return sinQur.size(); }
    void debug() {
        for (auto& s : sinQur) {
            std::cout << s << std::endl;
        }
    }
};
