cmake_minimum_required(VERSION 2.6)
project(signature)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(signature main.cpp)

target_link_libraries(signature pthread ${Boost_LIBRARIES})

install(TARGETS signature RUNTIME DESTINATION bin)

add_custom_command(TARGET signature POST_BUILD
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/touch_test.sh)

