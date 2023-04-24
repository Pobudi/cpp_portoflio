cmake_minimum_required(VERSION 3.24)
project(dodatkowy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -lcurl")
add_executable(dodatkowy main.cpp mail_handler.cpp mail_handler.h)


find_package(Poco REQUIRED Net)
target_link_libraries(dodatkowy PUBLIC Poco::Net curl)

