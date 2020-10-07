#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <cstdint>
#include <cstring>
#include <vector>
#include <sstream>
#include <stdio.h>

#include <unordered_set>
#include <unordered_map>
#include <type_traits>

#include "Glitch/Core/ErrorCodes.h"
#include "Glitch/Log/log.h"

using namespace std;

#ifdef GL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // GL_PLATFORM_WINDOWS