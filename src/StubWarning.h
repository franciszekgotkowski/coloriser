#pragma once

#include <assert.h>
#include <stdio.h>

#define STUB_WARNING( Message ) \
	printf("Encountered stub!\t%s\n", Message); \
	assert(false);

#define STUB_NOT_IMPLEMENTED \
	printf("Encountered stub!\t FUNCTION IS NOT IMPLEMENTED\n"); \
	assert(false);