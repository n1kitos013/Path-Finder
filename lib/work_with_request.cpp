#include "city_codes.h"
#include "work_with_request.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::vector<routeInf> PostingRequest(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date) {
    std::string request = "https://api.rasp.yandex.net/v3.0/search/?apikey=a8842828-982c-426e-b751-20c673df289c&lang=ru_RU&limit=1000";
    request += "&from=" + city_dep_code + "&to=" + city_arr_code + "&date=" + date;
    request += "&transport_types=plane,train,bus"; 

    std::cout << "Request URL: " << request << std::endl;  

    cpr::Response response;
    try {
        response = cpr::Get(cpr::Url{request});
    } catch (const std::exception& e) {
        std::cerr << "Network error: " << e.what() << std::endl;
        exit(1);
    }

    if (response.status_code != 200) {
        std::cerr << "API request failed with status code: " << response.status_code << std::endl;
        std::cerr << "Response text: " << response.text << std::endl;  
        exit(1);
    }

    json responseJson;
    try {
        responseJson = json::parse(response.text);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        exit(1);
    }

    std::vector<routeInf> routes;

    try {
        for (const auto& segment : responseJson["segments"]) {
            routeInf route;
            route.route_title = segment["thread"]["title"];
            route.route_num = segment["thread"]["number"];
            route.route_transport_type = segment["thread"]["transport_type"];
            route.route_carrier = segment["thread"]["carrier"]["title"];
            route.station_from = segment["from"]["title"];
            route.station_to = segment["to"]["title"];
            route.time_departure = segment["departure"];
            route.time_arrival = segment["arrival"];
            route.time_duration = segment["duration"];

            routes.push_back(route);
        }
    } catch (const json::exception& e) {
        std::cerr << "Error parsing JSON segment: " << e.what() << std::endl;
        exit(1);
    }

    return routes;
}

std::vector<std::pair<routeInf, routeInf>> PostingRequestWithTransfer(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date, const std::string& transfer_city_name, const std::map<std::string, std::string>& city_codes) {
    std::vector<std::pair<routeInf, routeInf>> transferRoutes;
    std::string transfer_city_code = GetCityCode(city_codes, transfer_city_name);
    if (transfer_city_code.empty()) {
        std::cerr << "Transfer city not found: " << transfer_city_name << std::endl;
        exit(1);
    }
    transfer_city_code.erase(std::remove(transfer_city_code.begin(), transfer_city_code.end(), '\r'), transfer_city_code.end());
    // std::cout << "Transfer city code (raw): ";
    // for (char c : transfer_city_code) {
    //     std::cout << "[" << (int)c << "]";
    // }
    // std::cout << std::endl;

    std::vector<routeInf> firstSegment = PostingRequest(city_dep_code, transfer_city_code, date);

    std::vector<routeInf> secondSegment = PostingRequest(transfer_city_code, city_arr_code, date);

    for (const auto& first : firstSegment) {
        for (const auto& second : secondSegment) {
            if (first.time_arrival < second.time_departure) {
                transferRoutes.push_back({first, second});
            }
        }
    } 
    
    return transferRoutes;
}