cmake_minimum_required(VERSION 3.4.1)

project(nekostrap C)

add_library(nekostrap SHARED nekostrap.c)

find_library(log-lib log)

target_link_libraries(nekostrap ${log-lib})
