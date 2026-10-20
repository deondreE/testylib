#pragma once

#include <string>
#include <vector>
using std::vector;
using std::string;

#ifdef NDEBUG
#define ASSERT(COND) ((void)0)
#else
#define T_ASSERT(COND) \
	do { \
		if (!(COND)) { \
			throw std::runtime_error("Assertion failed: " #COND); \
		} \
	} while (0)
#endif
