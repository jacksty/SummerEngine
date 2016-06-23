#pragma once

#include <intrin.h>

#include <thread>
#include <mutex>

#include <unordered_map>
#include <vector>

#include <fstream>
#include <sstream>
#include <ctime>

#include "Types.h"


#define ASSERTIONS_ENABLED 1
#define PERFORMANCE_CRITICAL_ASSERTIONS_ENABLED 1


#if ASSERTIONS_ENABLED
#define ASSERT(expr) \
	if(expr) {} \
	else \
	{ \
		LogManager::LogAssertionFailure(#expr, __FILE__, __LINE__);\
		__debugbreak(); \
	}
#else
#define ASSERT(expr)
#endif

#if PERFORMANCE_CRITICAL_ASSERTIONS_ENABLED
#define SLOW_ASSERT(expr) ASSERT(expr)
#else
#define SLOW_ASSERT(expr)
#endif
