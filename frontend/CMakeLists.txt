cmake_minimum_required(VERSION 3.20)

project(FrontEnd VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

include_directories(${CMAKE_SOURCE_DIR}/CompressionLibrary/include)
include_directories(${CMAKE_SOURCE_DIR}/utility)
file(GLOB_RECURSE QML_FILES "*.qml")
qt5_add_resources(QRC_SOURCES "qml.qrc")

add_executable(${PROJECT_NAME} ${QML_FILES} ${QRC_SOURCES} ${HEADERS} ${SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME} CompressionLibrary Utility Qt5::Core Qt5::Quick)
