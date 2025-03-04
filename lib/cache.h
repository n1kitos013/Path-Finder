#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <string>
#include <vector>
#include "work_with_request.h"

class Cache {
private:
    std::map<std::string, std::vector<routeInf>> cache_container;

public:
    bool cacheSercher(const std::string& date, const std::string& dep_code, const std::string& arr_code) {
        std::string key = date + "&" + dep_code + "&" + arr_code;
        return cache_container.find(key) != cache_container.end();
    }

    void addCache(const std::string& date, const std::string& dep_code, const std::string& arr_code, const std::vector<routeInf>& routes) {
        std::string key = date + "&" + dep_code + "&" + arr_code;
        cache_container[key] = routes;
    }

    std::vector<routeInf> getCachedRoutes(const std::string& date, const std::string& dep_code, const std::string& arr_code) {
        std::string key = date + "&" + dep_code + "&" + arr_code;
        return cache_container[key];
    }
};

#endif 

