#include "cache.h"
#include "work_with_request.h"
#include "output.h"
#include "city_codes.h"  

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <date> -s <direct|transfer> [transfer_city]" << std::endl;
        exit(1);
    }

    std::string date = argv[1];
    std::string search_type = argv[2];  
    std::string mode = argv[3];        

    std::string departure_city = "c2"; 
    std::string arrival_city = "c25";   

   
    std::map<std::string, std::string> city_codes = LoadCityCodes("./cities.txt");

    Cache cache;
    if (search_type == "-s") {
        if (mode == "direct-Pskov" || mode == "direct-SPb") {
            std::string actual_departure_city = (mode == "direct-Pskov") ? departure_city : arrival_city;
            std::string actual_arrival_city = (mode == "direct-Pskov") ? arrival_city : departure_city;
            std::vector<routeInf> routes = PostingRequest(actual_departure_city, actual_arrival_city, date);
            if (routes.empty()) {
                std::cout << "No direct routes found for the given date." << std::endl;
            } else {
                cache.addCache(date, actual_departure_city, actual_arrival_city, routes);
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
            exit(1);
        }
    } else {
        std::cerr << "Invalid arguments. Usage: " << argv[0] << " <date> -s <direct|transfer> [transfer_city]" << std::endl;
        exit(1);
    }

    return 0;
}