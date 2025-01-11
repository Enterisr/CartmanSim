cmake_minimum_required(VERSION 3.21)
project(Bonus)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bonus main.cpp)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(Bonus 
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)