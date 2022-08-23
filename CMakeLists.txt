cmake_minimum_required(VERSION 3.16)

set(namespace "gnutility")

project("gnutility"
    VERSION 1.1.1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(public_headers
        include/gnutility.hpp)

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

add_library(gnutility
        STATIC
        src/gnutility.cpp
        )

target_include_directories(gnutility
        PUBLIC
        include)

target_link_libraries(gnutility
        PRIVATE
        fmt
        simdjson)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(bundle)

bundle_static_library(gnutility gnutility_bundle)

enable_testing()

add_subdirectory(tests)
