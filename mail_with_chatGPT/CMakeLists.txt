cmake_minimum_required(VERSION 3.24)
project(mail_with_chatGPT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -lcurl")
add_executable(mail_with_chatGPT main.cpp mail_handler.cpp mail_handler.h)


find_package(Poco REQUIRED Net)
target_link_libraries(mail_with_chatGPT PUBLIC Poco::Net curl)

