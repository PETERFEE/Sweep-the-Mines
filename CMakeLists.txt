cmake_minimum_required(VERSION 3.30)
project(Minesweeper)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Minesweeper main.cpp
        Tile.h
        Board.h
        TextureManager.h
        Leaderboard.h
        Leaderboard.cpp
        WelcomeScreen.cpp
        WelcomeScreen.h)
target_compile_features(Minesweeper PRIVATE cxx_std_20)
target_link_libraries(Minesweeper PRIVATE sfml-graphics)