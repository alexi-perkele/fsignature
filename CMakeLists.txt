cmake_minimum_required(VERSION 2.6)
project(signature)

add_executable(signature main.cpp)

install(TARGETS signature RUNTIME DESTINATION bin)
