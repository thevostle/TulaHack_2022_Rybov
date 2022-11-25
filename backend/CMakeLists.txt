cmake_minimum_required(VERSION 3.1.0)

project(cpp-backend CXX)

add_subdirectory(third_party/drogon)

add_executable(cpp-backend main.cpp)

set_property(TARGET drogon PROPERTY CXX_STANDARD 17)

target_compile_features(cpp-backend PUBLIC cxx_std_20)
target_link_libraries(cpp-backend PRIVATE drogon)