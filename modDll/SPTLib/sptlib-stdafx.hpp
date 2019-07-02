#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>
#include "./Windows/minhook/include/MinHook.h"

#ifdef __MINGW32__
#include "../mingw.mutex.h"
#endif

#pragma comment( lib, "psapi.lib" )
#endif

#include <clocale>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <array>

#ifdef __MINGW32__
#include "../mingw.future.h"
#endif
#include <limits>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using std::uintptr_t;
using std::size_t;
