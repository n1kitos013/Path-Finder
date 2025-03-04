// #include "work_with_request.h"
// #include <cpr/cpr.h>
// #include "nlohmann/json.hpp"
// #include <iostream>
// #include <stdexcept>

// using json = nlohmann::json;

// std::vector<routeInf> PostingRequest(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date) {
//     std::string request = "https://api.rasp.yandex.net/v3.0/search/?apikey=a8842828-982c-426e-b751-20c673df289c&lang=ru_RU&limit=1000";
//     request += "&from=" + city_dep_code + "&to=" + city_arr_code + "&date=" + date;
//     //request += "&transfers=true";
//     request += "&transport_types=plane,train,bus";  // Добавляем типы транспорта
    

//     std::cout << "Request URL: " << request << std::endl;  // Логирование запроса

//     cpr::Response response;
//     try {
//         response = cpr::Get(cpr::Url{request});
//     } catch (const std::exception& e) {
//         std::cerr << "Network error: " << e.what() << std::endl;
//         return {};
//     }

//     if (response.status_code != 200) {
//         std::cerr << "API request failed with status code: " << response.status_code << std::endl;
//         std::cerr << "Response text: " << response.text << std::endl;  // Логирование ответа
//         return {};
//     }

//     json responseJson;
//     try {
//         responseJson = json::parse(response.text);
//     } catch (const json::parse_error& e) {
//         std::cerr << "JSON parsing error: " << e.what() << std::endl;
//         return {};
//     }

//     std::vector<routeInf> routes;

//     try {
//         for (const auto& segment : responseJson["segments"]) {
//             routeInf route;
//             route.route_title = segment["thread"]["title"];
//             route.route_num = segment["thread"]["number"];
//             route.route_transport_type = segment["thread"]["transport_type"];
//             route.route_carrier = segment["thread"]["carrier"]["title"];
//             route.station_from = segment["from"]["title"];
//             route.station_to = segment["to"]["title"];
//             route.time_departure = segment["departure"];
//             route.time_arrival = segment["arrival"];
//             route.time_duration = segment["duration"];

//             routes.push_back(route);
//         }
//     } catch (const json::exception& e) {
//         std::cerr << "Error parsing JSON segment: " << e.what() << std::endl;
//         return {};
//     }

//     return routes;
// }


// #include "work_with_request.h"
// #include <cpr/cpr.h>
// #include "nlohmann/json.hpp"
// #include <iostream>
// #include <stdexcept>

// using json = nlohmann::json;

// std::vector<routeInf> PostingRequest(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date) {
//     std::string request = "https://api.rasp.yandex.net/v3.0/search/?apikey=a8842828-982c-426e-b751-20c673df289c&lang=ru_RU&limit=1000";
//     request += "&from=" + city_dep_code + "&to=" + city_arr_code + "&date=" + date;
//     request += "&transport_types=plane,train,bus";  // Фильтрация по типам транспорта

//     std::cout << "Request URL: " << request << std::endl;  // Логирование запроса

//     cpr::Response response;
//     try {
//         response = cpr::Get(cpr::Url{request});
//     } catch (const std::exception& e) {
//         std::cerr << "Network error: " << e.what() << std::endl;
//         return {};
//     }

//     if (response.status_code != 200) {
//         std::cerr << "API request failed with status code: " << response.status_code << std::endl;
//         std::cerr << "Response text: " << response.text << std::endl;  // Логирование ответа
//         return {};
//     }

//     json responseJson;
//     try {
//         responseJson = json::parse(response.text);
//     } catch (const json::parse_error& e) {
//         std::cerr << "JSON parsing error: " << e.what() << std::endl;
//         return {};
//     }

//     std::vector<routeInf> routes;

//     try {
//         for (const auto& segment : responseJson["segments"]) {
//             routeInf route;
//             route.route_title = segment["thread"]["title"];
//             route.route_num = segment["thread"]["number"];
//             route.route_transport_type = segment["thread"]["transport_type"];
//             route.route_carrier = segment["thread"]["carrier"]["title"];
//             route.station_from = segment["from"]["title"];
//             route.station_to = segment["to"]["title"];
//             route.time_departure = segment["departure"];
//             route.time_arrival = segment["arrival"];
//             route.time_duration = segment["duration"];

//             routes.push_back(route);
//         }
//     } catch (const json::exception& e) {
//         std::cerr << "Error parsing JSON segment: " << e.what() << std::endl;
//         return {};
//     }

//     return routes;
// }

// std::vector<std::pair<routeInf, routeInf>> PostingRequestWithTransfer(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date) {
//     std::vector<std::pair<routeInf, routeInf>> transferRoutes;

//     // Промежуточный город (например, Москва)
//     std::string transfer_city = "c213";

//     // Маршрут из Санкт-Петербурга в промежуточный город
//     std::vector<routeInf> firstSegment = PostingRequest(city_dep_code, transfer_city, date);

//     // Маршрут из промежуточного города в Псков
//     std::vector<routeInf> secondSegment = PostingRequest(transfer_city, city_arr_code, date);

//     // Объединяем маршруты с пересадкой
//     for (const auto& first : firstSegment) {
//         for (const auto& second : secondSegment) {
//             transferRoutes.push_back({first, second});
//         }
//     }

//     return transferRoutes;
// }



#include "city_codes.h"
#include "work_with_request.h"
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"
#include <iostream>
#include <stdexcept>

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
        return {};
    }

    if (response.status_code != 200) {
        std::cerr << "API request failed with status code: " << response.status_code << std::endl;
        std::cerr << "Response text: " << response.text << std::endl;  
        return {};
    }

    json responseJson;
    try {
        responseJson = json::parse(response.text);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return {};
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
        return {};
    }

    return routes;
}

std::vector<std::pair<routeInf, routeInf>> PostingRequestWithTransfer(const std::string& city_dep_code, const std::string& city_arr_code, const std::string& date, const std::string& transfer_city_name, const std::map<std::string, std::string>& city_codes) {
    std::vector<std::pair<routeInf, routeInf>> transferRoutes;
    std::string transfer_city_code = GetCityCode(city_codes, transfer_city_name);
    if (transfer_city_code.empty()) {
        std::cerr << "Transfer city not found: " << transfer_city_name << std::endl;
        return transferRoutes;
    }

   
    std::vector<routeInf> firstSegment = PostingRequest(city_dep_code, transfer_city_code, date);

    std::vector<routeInf> secondSegment = PostingRequest(transfer_city_code, city_arr_code, date);

    for (const auto& first : firstSegment) {
        for (const auto& second : secondSegment) {
            transferRoutes.push_back({first, second});
        }
    }

    return transferRoutes;
}