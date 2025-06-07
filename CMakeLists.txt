cmake_minimum_required(VERSION 3.20)
project(CoolYtDowloader)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/qt_setup.cmake)

add_executable(${PROJECT_NAME} src/main.cpp include/MainWindow.hpp src/MainWindow.cpp)

setup_target(${PROJECT_NAME})