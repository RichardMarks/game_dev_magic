cmake_minimum_required(VERSION 3.27)
project(PROJECT_NAME C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(game src/main.c)

target_include_directories(game PRIVATE SDL2::SDL2)
target_link_libraries(game PRIVATE SDL2::SDL2)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dist")

