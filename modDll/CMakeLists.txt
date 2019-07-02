cmake_minimum_required(VERSION 3.9)
project(modDll)



	# Enable link-time code generation.
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} /GL")
	set (CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS} ${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")
	set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG:incremental")

	# Switch to the static runtime.
	set (flag_variables
		CMAKE_C_FLAGS_DEBUG
		CMAKE_C_FLAGS_MINSIZEREL
		CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_RELWITHDEBINFO
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_MINSIZEREL
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_RELWITHDEBINFO
	)

	foreach (variable ${flag_variables})
		if (${variable} MATCHES "/MD")
			string (REPLACE "/MD" "/MT" ${variable} "${${variable}}")
		endif ()
	endforeach ()

	# If we're building for Windows XP, add a special compiler flag to fix a crash on Windows XP.
	# http://stackoverflow.com/a/32953859/4214632
	if (CMAKE_GENERATOR_TOOLSET MATCHES "_xp")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:threadSafeInit-")
	endif ()


set (SPT_SOURCE_FILES
        SPTLib/IHookableModule.cpp
        SPTLib/IHookableDirFilter.cpp
        SPTLib/IHookableNameFilter.cpp
        SPTLib/IHookableNameFilterOrdered.cpp
        SPTLib/Hooks.cpp
        SPTLib/MemUtils.cpp
        SPTLib/sptlib.cpp
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


set (SOURCE_FILES
        Windows/dllmain.cpp
        Windows/conutils.cpp
        Windows/interprocess.cpp
        witcher/witchertypes.cpp

        modules/WitcherModule.cpp)



include_external_msproject (MinHook "${CMAKE_SOURCE_DIR}/modDll/SPTLib/Windows/minhook/build/VC15/libMinHook.vcxproj")
include_directories ("SPTLib/Windows/minhook/include")

set (SOURCE_FILES ${SOURCE_FILES} ${SPT_SOURCE_FILES} ${WINDOWS_FILES} ${HEADER_FILES})


add_library(modDll SHARED
	${SOURCE_FILES}
)

set_target_properties(modDll PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON) 

add_dependencies (modDll MinHook)
