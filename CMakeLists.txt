project(trevi-interview)

set(CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY (googletest/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(filter main.cpp dfa_filter.cpp)

add_executable(unittest dfa_filter_test.cpp dfa_filter.cpp)
enable_testing()
target_link_libraries(unittest gtest gtest_main)
add_test(ssss unittest)