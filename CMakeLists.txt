cmake_minimum_required(VERSION 3.10)

project(trevi-interview)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED program_options)


ADD_SUBDIRECTORY (googletest/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(filter main.cpp dfa_filter.cpp acc_filter.cpp)
target_link_libraries(filter ${Boost_LIBRARIES})

add_executable(unittest dfa_filter_test.cpp dfa_filter.cpp acc_filter.cpp acc_filter_test.cpp)
target_link_libraries(unittest gtest gtest_main)