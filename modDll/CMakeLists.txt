cmake_minimum_required(VERSION 3.9)
project(modDll)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-fpermissive) # CMake 2.8.11 or older

set (SPT_SOURCE_FILES
        SPTLib/IHookableModule.cpp
        SPTLib/IHookableDirFilter.cpp
        SPTLib/IHookableNameFilter.cpp
        SPTLib/IHookableNameFilterOrdered.cpp
        SPTLib/Hooks.cpp
        SPTLib/MemUtils.cpp
        SPTLib/sptlib.cpp


        SPTLib/Windows/minhook/src/hook.c
        SPTLib/Windows/minhook/src/buffer.c
        SPTLib/Windows/minhook/src/trampoline.c
        SPTLib/Windows/minhook/src/HDE/hde64.c
        )


set (WINDOWS_FILES
        SPTLib/Windows/DetoursUtils.cpp
        SPTLib/Windows/Hooks_win.cpp
        SPTLib/Windows/MemUtils_win.cpp
        SPTLib/Windows/DetoursUtils.hpp
        Windows/conutils.cpp
        Windows/dllmain.cpp
        Windows/interprocess.cpp
        Windows/conutils.hpp)

include_directories ("SPTLib/Windows/minhook/include")


set (SOURCE_FILES
        Windows/dllmain.cpp
        Windows/conutils.cpp
        Windows/interprocess.cpp

        modules/WitcherModule.cpp)

set (SOURCE_FILES ${SOURCE_FILES} ${SPT_SOURCE_FILES} ${WINDOWS_FILES} ${HEADER_FILES})


add_library(modDll SHARED



        ${SOURCE_FILES}
        )

target_link_libraries(modDll -lpsapi)