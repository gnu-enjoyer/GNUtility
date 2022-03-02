cmake_minimum_required(VERSION 3.16)

set(namespace "gnutility")

project("gnutility"
    VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9
)

FetchContent_Declare(
        simdjson
        GIT_REPOSITORY  https://github.com/simdjson/simdjson.git
        GIT_TAG 6698eb96b99576b8d53f8d90c9023717379e1c0f
)

FetchContent_MakeAvailable(fmt simdjson)

add_library(${PROJECT_NAME}
        src/gnutility.cpp
        )

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${simdjson_SOURCE_DIR}/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

set(public_headers
    include/gnutility.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(gnutility)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

#flatpack any deps
include(bundle)

add_library(gnutility-deps
        STATIC
        src/gnutility.cpp)

target_link_libraries(gnutility-deps
        fmt
        simdjson)

target_include_directories(gnutility-deps
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

bundle_static_library(gnutility-deps gnutils_bundle)

#CTest
enable_testing()

add_executable(gnutility-tests
        src/tests.cpp)

target_include_directories(gnutility-tests
        PUBLIC
        include)

target_link_libraries(gnutility-tests
        ${CMAKE_BINARY_DIR}/libgnutils_bundle.a)

add_test(gnutility-ctest
        gnutility-tests)
