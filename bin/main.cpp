// #include <iostream>
// #include <string>
// #include "cache.h"
// #include "work_with_request.h"
// #include "output.h"

// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " <date>" << std::endl;
//         return 1;
//     }

//     std::string date = argv[1];
//     std::string departure_city = "c2";  // Код Санкт-Петербурга
//     std::string arrival_city = "c25";   // Код Пскова

//     Cache cache;

//     // Проверка кэша
//     if (cache.cacheSercher(date, departure_city, arrival_city)) {
//         std::vector<routeInf> cachedRoutes = cache.getCachedRoutes(date, departure_city, arrival_city);
//         DisplayOnBoard(cachedRoutes);
//         return 0;
//     }

//     // Запрос маршрутов
//     std::vector<routeInf> routes = PostingRequest(departure_city, arrival_city, date);

//     if (routes.empty()) {
//         std::cout << "No routes found for the given date." << std::endl;
//     } else {
//         cache.addCache(date, departure_city, arrival_city, routes);
//         DisplayOnBoard(routes);
//     }

//     return 0;
// }


// #include <iostream>
// #include <string>
// #include "cache.h"
// #include "work_with_request.h"
// #include "output.h"

// int main(int argc, char* argv[]) {
//     if (argc < 3) {
//         std::cerr << "Usage: " << argv[0] << " <date> -s <direct|transfer>" << std::endl;
//         return 1;
//     }

//     std::string date = argv[1];
//     std::string search_type = argv[2];  // Тип поиска: direct или transfer
//     std::string departure_city = "c2";  // Санкт-Петербург
//     std::string arrival_city = "c25";   // Псков

//     Cache cache;

//     if (search_type == "-s" && argc >= 4) {
//         std::string mode = argv[3];  // direct или transfer

//         if (mode == "direct") {
//             // Поиск прямых маршрутов
//             std::vector<routeInf> routes = PostingRequest(departure_city, arrival_city, date);

//             if (routes.empty()) {
//                 std::cout << "No direct routes found for the given date." << std::endl;
//             } else {
//                 cache.addCache(date, departure_city, arrival_city, routes);
//                 std::cout << "=== Direct routes ===" << std::endl;
//                 DisplayOnBoard(routes);
//             }
//         } else if (mode == "transfer") {
//             // Поиск маршрутов с пересадкой
//             std::vector<std::pair<routeInf, routeInf>> transferRoutes = PostingRequestWithTransfer(departure_city, arrival_city, date);

//             if (transferRoutes.empty()) {
//                 std::cout << "No transfer routes found for the given date." << std::endl;
//             } else {
//                 std::cout << "=== Transfer routes ===" << std::endl;
//                 DisplayTransferRoutes(transferRoutes);
//             }
//         } else {
//             std::cerr << "Invalid mode. Use 'direct' or 'transfer'." << std::endl;
//             return 1;
//         }
//     } else {
//         std::cerr << "Invalid arguments. Usage: " << argv[0] << " <date> -s <direct|transfer>" << std::endl;
//         return 1;
//     }

//     return 0;
// }

#include <iostream>
#include <string>
#include "cache.h"
#include "work_with_request.h"
#include "output.h"
#include "city_codes.h"  

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <date> -s <direct|transfer> [transfer_city]" << std::endl;
        return 1;
    }

    std::string date = argv[1];
    std::string search_type = argv[2];  
    std::string mode = argv[3];        

    std::string departure_city = "c2"; 
    std::string arrival_city = "c25";   

   
    std::map<std::string, std::string> city_codes = LoadCityCodes("./cities_ya_codes.csv");

    Cache cache;

    if (search_type == "-s") {
        if (mode == "direct") {
            std::vector<routeInf> routes = PostingRequest(departure_city, arrival_city, date);

            if (routes.empty()) {
                std::cout << "No direct routes found for the given date." << std::endl;
            } else {
                cache.addCache(date, departure_city, arrival_city, routes);
                std::cout << "=== Direct routes ===" << std::endl;
                DisplayOnBoard(routes);
            }
        } else if (mode == "transfer" && argc >= 5) {
           
            std::string transfer_city = argv[4];  
            std::vector<std::pair<routeInf, routeInf>> transferRoutes = PostingRequestWithTransfer(departure_city, arrival_city, date, transfer_city, city_codes);

            if (transferRoutes.empty()) {
                std::cout << "No transfer routes found for the given date." << std::endl;
            } else {
                std::cout << "=== Transfer routes ===" << std::endl;
                DisplayTransferRoutes(transferRoutes);
            }
        } else {
            std::cerr << "Invalid mode. Use 'direct' or 'transfer'." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Invalid arguments. Usage: " << argv[0] << " <date> -s <direct|transfer> [transfer_city]" << std::endl;
        return 1;
    }

    return 0;
}