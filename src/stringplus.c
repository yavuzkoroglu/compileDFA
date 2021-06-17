/** \file stringplus.c
 ** \brief Implements some extremely useful non-standard string manipulation functions.
 **/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "debug.h"
#include "logging.h"
#include "stdlibplus.h"
#include "unless.h"

DECLARE_SOURCE("STRINGPLUS");

/** \brief Constructs a new string from a given pattern.
 ** \param string The string
 ** \param pattern The pattern
 ** \param args A variadic list of parameters
 ** \returns A pointer to the string or NULL.
 **/
char* vFromPattern(char* string, unsigned int capacity, const char* pattern, va_list args)
{
	DECLARE_FUNCTION(vFromPattern);

	/* Checks. */
	ASSERT_NOT_ZERO(capacity);
	ASSERT_FITS_IN_BOUND(capacity, BUFFER_LARGE_SIZE+1);
	ASSERT_NOT_NULL(pattern);

	unless (string)
		SAFE_MALLOC(string, char, capacity+1);

	/* vsnprintf() is a non-standard C library function. */
	#ifdef VSNPRINTF_SUPPORTED
		vsnprintf(string, capacity+1, pattern, args);
	#else
		vsnprintf_rpl(string, capacity+1, pattern, args);
	#endif
	va_end(args);

	ASSERT_NOT_TOO_LONG(string, capacity);
	return string;
}

/** \brief Constructs a new string from a given pattern.
 ** \param pattern The pattern
 ** \param ... Additional parameters
 ** \returns A pointer to a new string in heap, or NULL if there is a BUFFER_OVERFLOW.
 **/
char* fromPattern(char* string, unsigned int capacity, const char* pattern, ...)
{
	DECLARE_FUNCTION(fromPattern);

	/* Variable declaration. */
	va_list args;

	/* Checks. */
	ASSERT_NOT_ZERO(capacity);
	ASSERT_FITS_IN_BOUND(capacity, BUFFER_LARGE_SIZE + 1);
	ASSERT_NOT_NULL(pattern);

	va_start(args, pattern);
	return vFromPattern(string, capacity, pattern, args);
}
