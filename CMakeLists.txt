cmake_minimum_required(VERSION 2.6)
project(signature)

add_executable(signature main.cpp)

install(TARGETS signature RUNTIME DESTINATION bin)

add_custom_command(TARGET signature POST_BUILD
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/touch_test.sh)
