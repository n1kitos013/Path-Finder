#ifndef WORK_WITH_REQUEST_H
#define WORK_WITH_REQUEST_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cpr/cpr.h>
#include <stdexcept>

struct routeInf {
    std::string route_title;
    std::string route_num;
    std::string route_transport_type;
    std::string route_carrier;

    std::string station_from;
    std::string station_to;

    std::string time_departure;
    std::string time_arrival;
    int time_duration;
};

std::vector<routeInf> PostingRequest(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date);
std::vector<std::pair<routeInf, routeInf>> PostingRequestWithTransfer(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date, const std::string& transfer_city_name, const std::map<std::string, std::string>& city_codes);

#endif 