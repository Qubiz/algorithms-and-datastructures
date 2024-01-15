cmake_minimum_required(VERSION 3.27)
project(algorithms_and_datastructures)

include(cmake/CPM.cmake)

CPMAddPackage("gh:boost-ext/ut@2.0.1")

set(CMAKE_CXX_STANDARD 23)

add_executable(a_and_d)
target_sources(a_and_d
        PRIVATE
        src/main.cpp
)

target_link_libraries(a_and_d
        PRIVATE
        Boost::ut
)
