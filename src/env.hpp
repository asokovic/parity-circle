#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Env {
public:
    static std::unordered_map<std::string, std::string> vars;

    static void load(const std::string& filename = "../.env") {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line[0] == '#') continue;

            size_t eq = line.find('=');
            if (eq == std::string::npos) continue;

            std::string key = line.substr(0, eq);
            std::string value = line.substr(eq + 1);

            // Trim whitespace around key/value
            auto trim = [](std::string& s) {
                while (!s.empty() && isspace(s.front())) s.erase(s.begin());
                while (!s.empty() && isspace(s.back())) s.pop_back();
            };

            trim(key);
            trim(value);

            vars[key] = value;
        }
    }

    static std::string get(const std::string& key) {
        return vars.count(key) ? vars[key] : "";
    }
};
