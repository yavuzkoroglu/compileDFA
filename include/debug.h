/** \file debug.h
 ** \brief Declares useful debugging macros.
 **/
#ifndef DEBUG_H
	#define DEBUG_H
	#include <string.h>
	#include "constants.h"
	#include "logging.h"

	#ifndef DECLARE_SOURCE
		#define DECLARE_SOURCE(name) static const char src[] = name
	#endif

	#ifndef DECLARE_FUNCTION
		#ifdef NDEBUG
			#define DECLARE_FUNCTION(name) static const char fn[] = "UNKNOWN_FN"
		#else
			#define DECLARE_FUNCTION(name) static const char fn[] = #name
		#endif
	#endif

	#ifndef ASSERT_EQUAL_STR
		#define ASSERT_EQUAL_STR(s1,s2) errorUnless(!strcmp(s1,s2), MSG_NOT_EQUAL(s1,s2))
	#endif

	#ifndef ASSERT_NULL
		#define ASSERT_NULL(ptr) errorUnless(!ptr, MSG_ERROR_NOT_NULL(ptr))
	#endif

	#ifndef ASSERT_NOT_NULL
		#define ASSERT_NOT_NULL(ptr) errorIf(!ptr, MSG_ERROR_NULL(ptr))
	#endif

	#ifndef ASSERT_EMPTY
		#define ASSERT_EMPTY(str) errorUnless(!strcmp(str,""), MSG_ERROR_NOT_EMPTY(str))
	#endif

	#ifndef ASSERT_NOT_EMPTY
		#define ASSERT_NOT_EMPTY(str) errorIf(!strcmp(str,""), MSG_ERROR_EMPTY(str))
	#endif

	#ifndef ASSERT_ZERO
		#define ASSERT_ZERO(var) errorUnless(!var, MSG_ERROR_NOT_ZERO(var))
	#endif

	#ifndef ASSERT_NOT_ZERO
		#define ASSERT_NOT_ZERO(var) errorIf(!var, MSG_ERROR_ZERO(var))
	#endif

	#ifndef ASSERT_NOT_NEGATIVE
		#define ASSERT_NOT_NEGATIVE(var) errorUnless(var >= 0, MSG_ERROR_NEGATIVE(var))
	#endif

	#ifndef ASSERT_PROBABILITY
		#define ASSERT_PROBABILITY(var) \
			errorUnless(geq_dbl(1.00,var) && geq_dbl(var,0.00), MSG_ERROR_NOT_A_PROBABILITY(var))
	#endif

	#ifndef ASSERT_VIGILANCE
		#define ASSERT_VIGILANCE(var,rho) \
			errorUnless(geq_dbl(rho,var) && geq_dbl(var,-rho), MSG_ERROR_NOT_VIGILANT(var))
	#endif

	#ifndef ASSERT_STRLEN_MATCH
		#define ASSERT_STRLEN_MATCH(str,len) \
			errorUnless(strlen(str) == len, MSG_ERROR_STRLEN_MISMATCH(str, len))
	#endif

	#ifndef ASSERT_NOT_TOO_LONG
		#define ASSERT_NOT_TOO_LONG(str,maxlen) \
			errorUnless(strlen(str) < maxlen, MSG_ERROR_STR_TOO_LONG(str, maxlen))
	#endif

	#ifndef ASSERT_FITS_IN_BOUND
		#define ASSERT_FITS_IN_BOUND(index,bound) \
			errorUnless((long)index < (long)bound, MSG_ERROR_OUT_OF_BOUNDS(index, bound))
	#endif
#endif
