cmake_minimum_required(VERSION 3.24)
project(dodatkowy)

set(CMAKE_CXX_STANDARD 17)
add_executable(dodatkowy main.cpp mail_handler.cpp mail_handler.h)

#set(POCO_PREFIX "/home/bartosz/TPT/poco/cmake-build/install")
#set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
#set(POCO_LIB_DIR "${POCO_PREFIX}/lib")
#
#set(POCO_LIBS "${POCO_LIB_DIR}/libPocoFoundation.so")
#target_include_directories(dodatkowy PRIVATE "${POCO_INCLUDE_DIR}")
#target_link_libraries(dodatkowy "${POCO_LIBS}")
find_package(Poco REQUIRED Net)
target_link_libraries(dodatkowy PUBLIC Poco::Net)

