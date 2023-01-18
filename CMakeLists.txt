cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(battaglia_navale)

#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -g")
set(GCC_COVERAGE_COMPILE_FLAGS "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(Utils
    include/Utils/Utils.h
    src/Utils/Utils.cpp)

add_library(BattleShip
    include/BattleShip.h)

add_library(Army
    include/Army/Army.h
    src/Army/Army.cpp)

add_library(Ironclad
    include/Army/Ironclad/Ironclad.h
    src/Army/Ironclad/Ironclad.cpp)

add_library(Support
    include/Army/Support/Support.h
    src/Army/Support/Support.cpp)

add_library(Submarine
    include/Army/Submarine/Submarine.h
    src/Army/Submarine/Submarine.cpp)

add_library(Board
    include/Board/Board.h
    src/Board/Board.cpp)

add_library(Grid
    include/Board/Grid/Grid.h
    src/Board/Grid/Grid.cpp)

add_library(AttackGrid
    include/Board/Grid/AttackGrid/AttackGrid.h
    src/Board/Grid/AttackGrid/AttackGrid.cpp)

add_library(DefenceGrid
    include/Board/Grid/DefenceGrid/DefenceGrid.h
    src/Board/Grid/DefenceGrid/DefenceGrid.cpp)

add_library(Prompt
    include/Prompt/Prompt.h
    src/Prompt/Prompt.cpp)

add_executable(battaglia_navale
    src/main.cpp)

add_executable(replay_battaglia_navale
    src/replay.cpp)

set_target_properties(BattleShip PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Ironclad
    Army)

target_link_libraries(Support
    Army)

target_link_libraries(Submarine
    Army)

target_link_libraries(AttackGrid
    Grid)

target_link_libraries(DefenceGrid
    Grid)

target_link_libraries(Board
    Grid
    AttackGrid
    DefenceGrid
    BattleShip
    Army
    Ironclad
    Support
    Submarine)

target_link_libraries(Prompt
    Board
    Utils
    BattleShip)

target_link_libraries(battaglia_navale
    Prompt)

target_link_libraries(replay_battaglia_navale
    Prompt
    Board)