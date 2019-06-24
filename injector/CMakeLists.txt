cmake_minimum_required(VERSION 3.9)
project(injector)

set(CMAKE_CXX_STANDARD 17)

add_executable(injector main.cpp)
add_dependencies(injector modDll)

add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/)
