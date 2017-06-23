cmake_minimum_required(VERSION 3.8)
project(lab8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/ReqProcessor.cpp include/ReqProcessor.h src/JsonFormer.cpp include/JsonFormer.h include/json.hpp)
include_directories(include)
add_executable(lab8 ${SOURCE_FILES})
target_link_libraries(lab8 event)