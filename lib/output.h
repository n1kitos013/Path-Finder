#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include <vector>
#include "work_with_request.h"

void DisplayOnBoard(const std::vector<routeInf>& routes);
void DisplayRoutesByType(const std::vector<routeInf>& routes, const std::string& transport_type);
void DisplayTransferRoutes(const std::vector<std::pair<routeInf, routeInf>>& transferRoutes);

#endif 