cmake_minimum_required(VERSION 3.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY C:/Users/chatz/Desktop/dev/cpp/WitcherMod/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY C:/Users/chatz/Desktop/dev/cpp/WitcherMod/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/chatz/Desktop/dev/cpp/WitcherMod/build/)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -m64")

add_subdirectory(injector)
add_subdirectory(modDll)
