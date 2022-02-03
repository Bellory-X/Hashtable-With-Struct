cmake_minimum_required(VERSION 3.21)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(untitled1 main.cpp hashtable.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        HashTableTest
        hashtable_test_2.cpp
        hashtable.cpp
        value.h hashtable_test_1.cpp)
target_link_libraries(
        HashTableTest
        gtest_main
)