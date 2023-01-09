cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(battaglia_navale)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(Utils
    include/Utils/Utils.h
    src/Utils/Utils.cpp)

add_library(BattleShip
    include/BattleShip.h)

add_library(Army
    include/Army/Army.h
    src/Army/Army.cpp)

add_library(Board
    include/Board/Board.h
    src/Board/Board.cpp)

add_executable(battaglia_navale
    src/main.cpp)

set_target_properties(BattleShip PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(battaglia_navale
    Utils
    Board
    BattleShip
    Army)
