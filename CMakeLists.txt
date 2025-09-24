cmake_minimum_required(VERSION 3.6)
project(nekostrap)

add_library(nekostrap SHARED nekostrap.cpp)

find_library(log-lib log)

target_link_libraries(nekostrap ${log-lib})
