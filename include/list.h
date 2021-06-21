/** \file list.h
 ** \brief Defines Array and List related macros.
 **/
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "debug.h"
#include "logging.h"
#include "stdlibplus.h"
#include "stringplus.h"
#include "unless.h"

#define ASSERT_ARRAY(array,size,capacity)		\
	ASSERT_NOT_NULL(array);						\
	ASSERT_FITS_IN_BOUND(array->size,capacity)	\

#define ASSERT_LIST(list,size,capacity) ASSERT_ARRAY(list,size,capacity)

#ifdef DECLARE_ARRAY_OF
	#undef DECLARE_ARRAY_OF
#endif
#define DECLARE_ARRAY_OF(Object,capacity,size,objects,abbreviation)	\
	typedef struct Object##ArrayBody {								\
		Object objects[capacity];									\
		unsigned int size;											\
	} Object##Array;												\
	Object##Array* initialize_##abbreviation(Object##Array*);		\
	Object* get_##abbreviation(Object##Array*,unsigned int);		\
	Object* getNew_##abbreviation(Object##Array*);					\
	void clear_##abbreviation(Object##Array*);						\
	char* toString_##abbreviation(char*,const Object##Array*)

#ifdef DECLARE_LIST_OF
	#undef DECLARE_LIST_OF
#endif
#define DECLARE_LIST_OF(Object,capacity,size,objects,abbreviation)			\
	typedef struct Object##ListBody {										\
		Object* objects[capacity];			 								\
		unsigned int size;													\
	} Object##List;															\
	Object##List* initialize_##abbreviation(Object##List*);					\
	void add##Object##_##abbreviation(Object##List*,Object*);				\
	Object##List* appendArray_##abbreviation(Object##List*,Object##Array*);	\
	Object##List* listOf_##abbreviation(Object##List*,Object##Array*);		\
	Object* get_##abbreviation(Object##List*,unsigned int);					\
	void clear_##abbreviation(Object##List*);								\
	char* toString_##abbreviation(char*,const Object##List*)

#ifdef IMPLEMENT_ARRAY_FUNCTIONS_OF
	#undef IMPLEMENT_ARRAY_FUNCTIONS_OF
#endif
#define IMPLEMENT_ARRAY_FUNCTIONS_OF(Object,capacity,size,objects,abbr,subabbr) \
	Object##Array* initialize_##abbr(Object##Array* array)						\
	{																			\
		DECLARE_FUNCTION(initialize_##abbr);									\
		unless(array)															\
			SAFE_MALLOC(array, Object##Array, 1);								\
		array->size = 0;														\
		return array;															\
	}																			\
	Object* get_##abbr(Object##Array* array, unsigned int index)				\
	{																			\
		DECLARE_FUNCTION(get_##abbr);											\
		ASSERT_ARRAY(array,size,capacity);										\
		ASSERT_FITS_IN_BOUND(index,array->size);								\
		return array->objects + index;											\
	}																			\
	Object* getNew_##abbr(Object##Array* array)									\
	{																			\
		DECLARE_FUNCTION(get_##abbr);											\
		Object* object;															\
		ASSERT_ARRAY(array,size,capacity);										\
		object = array->objects + array->size++;								\
		ASSERT_ARRAY(array,size,capacity);										\
		return object;															\
	}																			\
	void clear_##abbr(Object##Array* array)										\
	{																			\
		DECLARE_FUNCTION(clear_##abbr);											\
		ASSERT_ARRAY(array,size,capacity);										\
		array->size = 0;														\
	}																			\
	char* toString_##abbr(char* str, const Object##Array* array)				\
	{																			\
		DECLARE_FUNCTION(toString_##abbr);										\
		const Object* object;													\
		char buffer[BUFFER_SIZE], *itemstr = buffer;							\
		char* ptr;																\
		ASSERT_ARRAY(array,size,capacity);										\
		unless(str)																\
			SAFE_MALLOC(str, char, BUFFER_LARGE_SIZE);							\
		if (array->size) {														\
			object = array->objects;											\
			itemstr = toString_##subabbr(buffer, object);						\
			ASSERT_NOT_NULL(itemstr);											\
			ASSERT_NOT_EMPTY(itemstr);											\
			ptr = fromPattern(str, BUFFER_SIZE, "%s", itemstr);					\
			ASSERT_NOT_NULL(ptr);												\
			ASSERT_NOT_EMPTY(ptr);												\
			for (object++; object < array->objects + array->size; object++) {	\
				ptr += strlen(ptr);												\
				itemstr = toString_##subabbr(buffer, object);					\
				ASSERT_NOT_NULL(itemstr);										\
				ASSERT_NOT_EMPTY(itemstr);										\
				ptr = fromPattern(ptr, BUFFER_SIZE, "\n%s", itemstr);			\
				ASSERT_NOT_NULL(ptr);											\
				ASSERT_NOT_EMPTY(ptr);											\
			}																	\
		} else {																\
			ptr = fromPattern(str, BUFFER_SIZE, "%s", CONTAINER_EMPTY_KEYWORD);	\
			ASSERT_NOT_NULL(ptr);												\
			ASSERT_NOT_EMPTY(ptr);												\
		}																		\
		ASSERT_NOT_NULL(str);													\
		ASSERT_NOT_TOO_LONG(str, BUFFER_LARGE_SIZE);							\
		return str;																\
	}

#ifdef IMPLEMENT_LIST_FUNCTIONS_OF
	#undef IMPLEMENT_LIST_FUNCTIONS_OF
#endif
#define IMPLEMENT_LIST_FUNCTIONS_OF(Object,cap,size,objs,aobjs,abbr,subabbr)	\
	Object##List* initialize_##abbr(Object##List* list)							\
	{																			\
		DECLARE_FUNCTION(initialize_##abbr);									\
		unless(list)															\
			SAFE_MALLOC(list, Object##List, 1);									\
		list->size = 0;															\
		return list;															\
	}																			\
	void add##Object##_##abbr(Object##List* list, Object* element)				\
	{																			\
		DECLARE_FUNCTION(add##Object##_##abbr);									\
		ASSERT_LIST(list,size,cap);												\
		list->objs[list->size++] = element;										\
		ASSERT_LIST(list,size,cap);												\
	}																			\
	Object##List* appendArray_##abbr(Object##List* list, Object##Array* array)	\
	{																			\
		DECLARE_FUNCTION(listOf_##abbr);										\
		Object* obj;															\
		ASSERT_ARRAY(array,size,cap);											\
		ASSERT_LIST(list,size,cap);												\
		for (obj = array->aobjs; obj < array->aobjs + array->size; obj++)		\
			add##Object##_##abbr(list, obj);									\
		ASSERT_LIST(list,size,cap);												\
		return list;															\
	}																			\
	Object##List* listOf_##abbr(Object##List* list, Object##Array* array)		\
	{																			\
		DECLARE_FUNCTION(listOf_##abbr);										\
		ASSERT_ARRAY(array,size,cap);											\
		list = initialize_##abbr(list);											\
		ASSERT_LIST(list,size,cap);												\
		return appendArray_##abbr(list, array);									\
	}																			\
	Object* get_##abbr(Object##List* list, unsigned int index)					\
	{																			\
		DECLARE_FUNCTION(get_##abbr);											\
		ASSERT_LIST(list,size,cap);												\
		ASSERT_FITS_IN_BOUND(index,list->size);									\
		return list->objs[index];												\
	}																			\
	void clear_##abbr(Object##List* list)										\
	{																			\
		DECLARE_FUNCTION(clear_##abbr);											\
		ASSERT_LIST(list,size,cap);												\
		list->size = 0;															\
	}																			\
	char* toString_##abbr(char* str, const Object##List* list)					\
	{																			\
		DECLARE_FUNCTION(toString_##abbr);										\
		unsigned int i;															\
		const Object* object;													\
		char buffer[BUFFER_SIZE], *itemstr = buffer;							\
		char* ptr;																\
		ASSERT_LIST(list,size,cap);												\
		unless(str)																\
			SAFE_MALLOC(str, char, BUFFER_LARGE_SIZE);							\
		if (list->size) {														\
			object = list->objs[0];												\
			itemstr = toString_##subabbr(buffer, object);						\
			ASSERT_NOT_NULL(itemstr);											\
			ASSERT_NOT_EMPTY(itemstr);											\
			ptr = fromPattern(str, BUFFER_SIZE, "%s", itemstr);					\
			ASSERT_NOT_NULL(ptr);												\
			ASSERT_NOT_EMPTY(ptr);												\
			for (i = 1; i < list->size; i++) {									\
				ptr += strlen(ptr);												\
				object = list->objs[i];											\
				itemstr = toString_##subabbr(buffer, object);					\
				ASSERT_NOT_NULL(itemstr);										\
				ASSERT_NOT_EMPTY(itemstr);										\
				ptr = fromPattern(ptr, BUFFER_SIZE, "\n%s", itemstr);			\
				ASSERT_NOT_NULL(ptr);											\
				ASSERT_NOT_EMPTY(ptr);											\
			}																	\
		} else {																\
			ptr = fromPattern(str, BUFFER_SIZE, "%s", CONTAINER_EMPTY_KEYWORD);	\
			ASSERT_NOT_NULL(ptr);												\
			ASSERT_NOT_EMPTY(ptr);												\
		}																		\
		ASSERT_NOT_NULL(str);													\
		ASSERT_NOT_TOO_LONG(str, BUFFER_LARGE_SIZE);							\
		return str;																\
	}
