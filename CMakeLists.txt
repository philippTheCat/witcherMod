cmake_minimum_required(VERSION 3.9)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)

if (MSVC)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
else ()
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
endif ()

add_subdirectory(injector)
add_subdirectory(modDll)
