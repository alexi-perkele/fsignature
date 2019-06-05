cmake_minimum_required(VERSION 3.14)
project(signature)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost COMPONENTS program_options REQUIRED)

set(WORKER_SOURCES reader.cpp)

set(SIGNATURE_SOURCES main.cpp)

add_executable(signature ${SIGNATURE_SOURCES} ${WORKER_SOURCES} )
target_include_directories(signature PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(signature pthread ${Boost_LIBRARIES})

install(TARGETS signature RUNTIME DESTINATION bin)

add_custom_command(TARGET signature POST_BUILD
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/touch_test.sh)

