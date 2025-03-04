add_library(TravelLib
    cache.cpp
    work_with_request.cpp 
    work_with_request.h 
    city_codes.h 
    city_codes.cpp
    cache.h 
    output.h 
    output.cpp
)

target_include_directories(TravelLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TravelLib PRIVATE cpr::cpr)
