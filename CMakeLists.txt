cmake_minimum_required(VERSION 3.10)
project(SZTronics_TUI VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "source/*.cpp")

add_library(sztronics_tui STATIC ${SOURCES})
target_link_libraries(sztronics_tui PRIVATE sztronics_miscellaneous)
target_link_libraries(sztronics_tui PRIVATE ncurses)

target_include_directories(sztronics_tui PUBLIC headers)