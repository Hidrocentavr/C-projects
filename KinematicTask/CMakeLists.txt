cmake_minimum_required(VERSION 2.8.3)
project(kinematic_task)

add_compile_options(-std=c++17)

find_package(Qt5Widgets)

add_executable(${PROJECT_NAME} main.cpp list.cpp matrix.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core)