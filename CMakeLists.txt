cmake_minimum_required(VERSION 3.21)
project(holyChess)

set(CMAKE_CXX_STANDARD 17)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(holyChess src/main.cpp src/piece.cpp src/piece.h src/board.cpp src/board.h src/holy_chess.cpp src/holy_chess.h)

target_link_libraries(holyChess sfml-graphics sfml-window sfml-system)
