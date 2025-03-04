#include "city_codes.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, std::string> LoadCityCodes(const std::string& filename) {
    std::map<std::string, std::string> city_codes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return city_codes;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string city_name, city_code;
        std::getline(ss, city_name, ';');
        std::getline(ss, city_code, ';'); 
        std::getline(ss, city_code, ';');  
        city_codes[city_name] = "c" + city_code;  

       
    }

    file.close();
    return city_codes;
}

std::string GetCityCode(const std::map<std::string, std::string>& city_codes, const std::string& city_name) {
    auto it = city_codes.find(city_name);
    if (it != city_codes.end()) {
        return it->second;
    }
    return "";  