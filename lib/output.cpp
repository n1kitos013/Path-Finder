// #include "output.h"
// #include <iostream>

// void DisplayOnBoard(const std::vector<routeInf>& routes) {
//     if (routes.empty()) {
//         std::cout << "No routes to display." << std::endl;
//         return;
//     }

//     for (const auto& route : routes) {
//         std::cout << "Transport: " << route.route_transport_type << std::endl;
//         std::cout << "Carrier: " << route.route_carrier << std::endl;
//         std::cout << "From: " << route.station_from << " To: " << route.station_to << std::endl;
//         std::cout << "Departure: " << route.time_departure << " Arrival: " << route.time_arrival << std::endl;
//         std::cout << "Duration: " << route.time_duration / 3600 << " hours" << std::endl;
//         std::cout << "-------------------------" << std::endl;
//     }
// }

// void DisplayRoutesByType(const std::vector<routeInf>& routes, const std::string& transport_type) {
//     if (routes.empty()) {
//         std::cout << "No " << transport_type << " routes found." << std::endl;
//         return;
//     }

//     std::cout << "=== " << transport_type << " routes ===" << std::endl;
//     for (const auto& route : routes) {
//         std::cout << "Transport: " << route.route_transport_type << std::endl;
//         std::cout << "Carrier: " << route.route_carrier << std::endl;
//         std::cout << "From: " << route.station_from << " To: " << route.station_to << std::endl;
//         std::cout << "Departure: " << route.time_departure << " Arrival: " << route.time_arrival << std::endl;
//         std::cout << "Duration: " << route.time_duration / 3600 << " hours" << std::endl;
//         std::cout << "-------------------------" << std::endl;
//     }
// }

// void DisplayTransferRoutes(const std::vector<std::pair<routeInf, routeInf>>& transferRoutes) {
//     if (transferRoutes.empty()) {
//         std::cout << "No transfer routes found." << std::endl;
//         return;
//     }

//     std::cout << "=== Transfer routes ===" << std::endl;
//     for (const auto& [firstSegment, secondSegment] : transferRoutes) {
//         std::cout << "First segment:" << std::endl;
//         std::cout << "  Transport: " << firstSegment.route_transport_type << std::endl;
//         std::cout << "  Carrier: " << firstSegment.route_carrier << std::endl;
//         std::cout << "  From: " << firstSegment.station_from << " To: " << firstSegment.station_to << std::endl;
//         std::cout << "  Departure: " << firstSegment.time_departure << " Arrival: " << firstSegment.time_arrival << std::endl;
//         std::cout << "  Duration: " << firstSegment.time_duration / 3600 << " hours" << std::endl;

//         std::cout << "Second segment:" << std::endl;
//         std::cout << "  Transport: " << secondSegment.route_transport_type << std::endl;
//         std::cout << "  Carrier: " << secondSegment.route_carrier << std::endl;
//         std::cout << "  From: " << secondSegment.station_from << " To: " << secondSegment.station_to << std::endl;
//         std::cout << "  Departure: " << secondSegment.time_departure << " Arrival: " << secondSegment.time_arrival << std::endl;
//         std::cout << "  Duration: " << secondSegment.time_duration / 3600 << " hours" << std::endl;

//         std::cout << "-------------------------" << std::endl;
//     }
// }


#include "output.h"
#include <iostream>

void DisplayOnBoard(const std::vector<routeInf>& routes) {
    if (routes.empty()) {
        std::cout << "No routes to display." << std::endl;
        return;
    }

    for (const auto& route : routes) {
        std::cout << "Transport: " << route.route_transport_type << std::endl;
        std::cout << "Carrier: " << route.route_carrier << std::endl;
        std::cout << "From: " << route.station_from << " To: " << route.station_to << std::endl;
        std::cout << "Departure: " << route.time_departure << " Arrival: " << route.time_arrival << std::endl;
        std::cout << "Duration: " << route.time_duration / 3600 << " hours" << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

void DisplayRoutesByType(const std::vector<routeInf>& routes, const std::string& transport_type) {
    if (routes.empty()) {
        std::cout << "No " << transport_type << " routes found." << std::endl;
        return;
    }

    std::cout << "=== " << transport_type << " routes ===" << std::endl;
    for (const auto& route : routes) {
        std::cout << "Transport: " << route.route_transport_type << std::endl;
        std::cout << "Carrier: " << route.route_carrier << std::endl;
        std::cout << "From: " << route.station_from << " To: " << route.station_to << std::endl;
        std::cout << "Departure: " << route.time_departure << " Arrival: " << route.time_arrival << std::endl;
        std::cout << "Duration: " << route.time_duration / 3600 << " hours" << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

void DisplayTransferRoutes(const std::vector<std::pair<routeInf, routeInf>>& transferRoutes) {
    if (transferRoutes.empty()) {
        std::cout << "No transfer routes found." << std::endl;
        return;
    }

    std::cout << "=== Transfer routes ===" << std::endl;
    for (const auto& [firstSegment, secondSegment] : transferRoutes) {
        std::cout << "First segment:" << std::endl;
        std::cout << "  Transport: " << firstSegment.route_transport_type << std::endl;
        std::cout << "  Carrier: " << firstSegment.route_carrier << std::endl;
        std::cout << "  From: " << firstSegment.station_from << " To: " << firstSegment.station_to << std::endl;
        std::cout << "  Departure: " << firstSegment.time_departure << " Arrival: " << firstSegment.time_arrival << std::endl;
        std::cout << "  Duration: " << firstSegment.time_duration / 3600 << " hours" << std::endl;

        std::cout << "Second segment:" << std::endl;
        std::cout << "  Transport: " << secondSegment.route_transport_type << std::endl;
        std::cout << "  Carrier: " << secondSegment.route_carrier << std::endl;
        std::cout << "  From: " << secondSegment.station_from << " To: " << secondSegment.station_to << std::endl;
        std::cout << "  Departure: " << secondSegment.time_departure << " Arrival: " << secondSegment.time_arrival << std::endl;
        std::cout << "  Duration: " << secondSegment.time_duration / 3600 << " hours" << std::endl;

        std::cout << "-------------------------" << std::endl;
    }
}