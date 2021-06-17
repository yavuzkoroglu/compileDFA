/** \file hash.c
 ** \brief Implements the hash() function
 **/
#include "debug.h"

DECLARE_SOURCE("HASH");

/** \brief Calculates the hash of a given string
 ** \param str A constant string
 ** \returns An unsigned long integer
 ** \related HashTable
 **
 ** This hash function is faster than many of its alternatives.
 **/
unsigned long hash(const char* str)
{
	DECLARE_FUNCTION(hash);

	/* Variable declarations. */
	unsigned long hash;
	int c;

	/* Check. */
	ASSERT_NOT_NULL(str);

	/* hash = hash * 33 + c */
	for (hash = 5381; (c = *str++); hash = ((hash << 5) + hash) + c);

	return hash;
}
