cmake_minimum_required(VERSION 3.5.0)
project(Travel)

set(CMAKE_CXX_STANDARD 20)

set(CPR_DIR "/usr/local/lib/cmake/cpr")
find_package(cpr REQUIRED)


add_subdirectory(lib)
add_subdirectory(bin)