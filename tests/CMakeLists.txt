cmake_minimum_required(VERSION 3.16)

project(gnutility-tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(gnutility-tests
        tests.cpp)

target_include_directories(gnutility-tests
        PRIVATE
        include)

target_link_libraries(gnutility-tests
        PRIVATE
        gnutility)

add_test(NAME gnutility-tests
        COMMAND gnutility-tests)