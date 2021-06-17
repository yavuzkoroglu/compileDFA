/** \file mapping.h
 ** \brief Defines Mapping for Hashtable.
 **/
#ifndef MAPPING_H
	#define MAPPING_H
	#include "object.h"

	typedef struct MappingBody {
		char* key;
		Object value;
	} Mapping;

	#define ASSERT_MAPPING(mapping)		\
		ASSERT_NOT_NULL(mapping);		\
		ASSERT_NOT_NULL(mapping->key)
#endif
