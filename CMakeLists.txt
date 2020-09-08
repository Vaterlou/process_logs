cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME logs)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(nlohmann_json CONFIG REQUIRED)


set(SOURCE_FILES  ./src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} nlohmann_json)
