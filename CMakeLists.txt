cmake_minimum_required(VERSION 3.20)
project(CoolYtDowloader)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/qt_setup.cmake)
include(cmake/sqlite3_setup.cmake)
include(cmake/path.cmake)

add_executable(${PROJECT_NAME} ${HPP_FILES} ${CPP_FILES}) 

config_sqlite3(${PROJECT_NAME})
setup_target(${PROJECT_NAME})