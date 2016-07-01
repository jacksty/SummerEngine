#pragma once
#include "stdafx.h"
#include "LogManager.h"


#if ASSERTIONS_ENABLED
#define ASSERT(expr) \
	if(expr) {} \
	else \
	{ \
		SE::LogManager::LogAssertionFailure(#expr, __FILE__, __LINE__);\
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