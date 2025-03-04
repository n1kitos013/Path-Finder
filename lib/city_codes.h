#ifndef CITY_CODES_H
#define CITY_CODES_H

#include <map>
#include <string>

std::map<std::string, std::string> LoadCityCodes(const std::string& filename);
std::string GetCityCode(const std::map<std::string, std::string>& city_codes, const std::string& city_name);

#endif 