cmake_minimum_required(VERSION 3.20)

project(FrontEnd VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/CompressionLibrary/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} CompressionLibrary Qt5::Core Qt5::Quick)
