cmake_minimum_required(VERSION 3.10)
project(nanocobs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME}
        STATIC
        src/nanocobs.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

include_directories(test/include)

add_executable(nanocobs_test test/main.cpp test/nanocobs_test.cpp src/nanocobs.cpp include/nanocobs.h)

enable_testing()
add_test(NAME cobs COMMAND nanocobs_test)

target_compile_definitions(nanocobs PUBLIC __STDC_LIMIT_MACROS __STDC_FORMAT_MACROS)