/** \file constants.h
 ** \brief Stores all the constants.
 **
 ** The constants in this file are in the form of preprocessor macros with macro guards.
 ** This allows any constant to be overwritten either at compilation via the -D flag or
 ** at the source code level before this file is included.
 **/
#ifndef CONSTANTS_H
	#define CONSTANTS_H

	/** \defgroup BUFFER Buffer Constants **/
	/** \defgroup CONTAINER Container Constants **/
	/** \defgroup LOG Logging Constants **/
	/** \defgroup MSG Message Constants **/
	/** \defgroup XML Xml Constants **/

	/** \def BUFFER_SIZE
	 ** \brief The maximum size of string preparation buffer.
	 ** \addtogroup BUFFER
	 **
	 ** BUFFER_SIZE: The maximum size of string preparation buffer.
	 **/
	#ifndef BUFFER_SIZE
		#define BUFFER_SIZE LOG_SAY_MAX
	#endif

	/** \def BUFFER_LARGE_SIZE
	 ** \brief The maximum size of string preparation buffer for very large strings.
	 ** \addtogroup BUFFER
	 **
	 ** BUFFER_LARGE_SIZE: The maximum size of string preparation buffer for very large strings.
	 **/
	#ifndef BUFFER_LARGE_SIZE
		#define BUFFER_LARGE_SIZE 131072
	#endif

	/** \def CONTAINER_EMPTY_KEYWORD
	 ** \brief A keyword indicating the user that a container is empty.
	 ** \addtogroup CONTAINER
	 **
	 ** CONTAINER_EMPTY_KEYWORD: A keyword indicating the user that a container is empty.
	 **/
	#ifndef CONTAINER_EMPTY_KEYWORD
		#define CONTAINER_EMPTY_KEYWORD "(empty)"
	#endif

	/** \def LOG_PATH
	 ** \brief The path to the log file.
	 ** \addtogroup LOG
	 ** \related logging.h
	 **
	 ** LOG_PATH: The path to the log file.
	 **/
	#ifndef LOG_PATH
		#define LOG_PATH "log.txt"
	#endif

	/** \def LOG_SAY_MAX
	 ** \brief The maximum number of characters that can be written to the screen.
	 ** \addtogroup LOG
	 ** \related logging.h
	 **
	 ** LOG_SAY_MAX: The maximum number of characters that can be written to the screen.
	 **/
	#ifndef LOG_SAY_MAX
		#define LOG_SAY_MAX 8192
	#endif

	/** \def MSG_ERROR_BAD_OUTPUT
	 ** \brief Message for bad outputs.
	 **
	 ** MSG_ERROR_BAD_OUTPUT: Message for bad outputs.
	 **/
	#ifndef MSG_ERROR_BAD_OUTPUT
		#ifdef NDEBUG
			#define MSG_ERROR_BAD_OUTPUT "%s: Bad Output\n", src
		#else
			#define MSG_ERROR_BAD_OUTPUT \
				"%s[%s()]: Bad Output @ FILE %s, Line %u\n", \
				src, fn, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_ENUM_TYPE_MISMATCH
	 ** \brief Message for enum type mismatch.
	 **
	 ** MSG_ERROR_ENUM_TYPE_MISMATCH: Message for enum type mismatch.
	 **/
	#ifndef MSG_ERROR_ENUM_TYPE_MISMATCH
		#ifdef NDEBUG
			#define MSG_ERROR_ENUM_TYPE_MISMATCH(tid, expected) "%s: [%u] does NOT match %s\n", src, tid, expected
		#else
			#define MSG_ERROR_ENUM_TYPE_MISMATCH(tid, expected) \
				"%s[%s()]: [%u] does NOT match %s @ FILE %s, Line %u\n", \
				src, fn, tid, expected, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NEGATIVE
	 ** \brief Message for unexpected negative values.
	 **
	 ** MSG_ERROR_NEGATIVE: Message for unexpected negative values.
	 **/
	#ifndef MSG_ERROR_NEGATIVE
		#ifdef NDEBUG
			#define MSG_ERROR_NEGATIVE(var) "%s: Unexpected Negative Variable", src
		#else
			#define MSG_ERROR_NEGATIVE(var) \
				"%s[%s()]: Unexpected Negative Variable '%s' @ FILE %s, Line %u\n", \
				src, fn, #var, __FILE__,__LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NOT_A_PROBABILITY
	 ** \brief Message for invalid probabilities.
	 **
	 ** MSG_ERROR_NOT_A_PROBABILITY: Message for invalid probabilities.
	 **/
	#ifndef MSG_ERROR_NOT_A_PROBABILITY
		#ifdef NDEBUG
			#define MSG_ERROR_NOT_A_PROBABILITY(var) \
				"%s: %s = %.3lf is NOT a probability\n", \
				src, #var, var
		#else
			#define MSG_ERROR_NOT_A_PROBABILITY(var) \
				"%s[%s()]: %s = %.3lf is NOT a probability @ FILE %s, Line %u \n", \
				src, fn, #var, var, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_NOT_EQUAL
	 ** \brief Message for different variables.
	 **
	 ** MSG_NOT_EQUAL: Message for different variables.
	 **/
	#ifndef MSG_NOT_EQUAL
		#ifdef NDEBUG
			#define MSG_NOT_EQUAL(s1, s2)	\
				"%s: %s != %s\n",			\
				src, #s1, #s2
		#else
			#define MSG_NOT_EQUAL(s1, s2)					\
				"%s[%s()]: %s != %s @ FILE %s, Line %u\n",	\
				src, fn, #s1, #s2, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NOT_VIGILANT
	 ** \brief Message for vigilancy violations.
	 **
	 ** MSG_ERROR_NOT_VIGILANT: Message for vigilancy violations.
	 **/
	#ifndef MSG_ERROR_NOT_VIGILANT
		#ifdef NDEBUG
			#define MSG_ERROR_NOT_VIGILANT(var) \
				"%s: %s = %.3lf is NOT 'vigilant'\n", \
				src, #var, var
		#else
			#define MSG_ERROR_NOT_VIGILANT(var) \
				"%s[%s()]: %s = %.3lf is NOT 'vigilant' @ FILE %s, Line %u \n", \
				src, fn, #var, var, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_EMPTY
	 ** \brief Message for unexpected empty strings.
	 **
	 ** MSG_ERROR_EMPTY: Message for unexpected empty strings.
	 **/
	#ifndef MSG_ERROR_EMPTY
		#ifdef NDEBUG
			#define MSG_ERROR_EMPTY(str) "%s: Unexpected EMPTY String", src
		#else
			#define MSG_ERROR_EMPTY(str) \
				"%s[%s()]: Unexpected EMPTY String '%s' @ FILE %s, Line %u\n", \
				src, fn, #str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NOT_EMPTY
	 ** \brief Message for unexpected non-empty strings.
	 **
	 ** MSG_ERROR_NOT_EMPTY: Message for unexpected non-empty strings.
	 **/
	#ifndef MSG_ERROR_NOT_EMPTY
		#ifdef NDEBUG
			#define MSG_ERROR_NOT_EMPTY(str) "%s: Unexpected non-EMPTY String", src
		#else
			#define MSG_ERROR_NOT_EMPTY(str) \
				"%s[%s()]: Unexpected non-EMPTY String '%s' @ FILE %s, Line %u\n", \
				src, fn, #str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NOT_NULL
	 ** \brief Message for unexpected non-null pointers.
	 **
	 ** MSG_ERROR_NOT_NULL: Message for unexpected non-null pointers.
	 **/
	#ifndef MSG_ERROR_NOT_NULL
		#ifdef NDEBUG
			#define MSG_ERROR_NOT_NULL(ptr) "%s: Unexpected non-NULL Pointer", src
		#else
			#define MSG_ERROR_NOT_NULL(ptr) \
				"%s[%s()]: Unexpected non-NULL Pointer '%s' @ FILE %s, Line %u\n", \
				src, fn, #ptr, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NULL
	 ** \brief Message for unexpected null pointers.
	 **
	 ** MSG_ERROR_NULL: Message for unexpected null pointers.
	 **/
	#ifndef MSG_ERROR_NULL
		#ifdef NDEBUG
			#define MSG_ERROR_NULL(ptr) "%s: Unexpected NULL Pointer", src
		#else
			#define MSG_ERROR_NULL(ptr) \
				"%s[%s()]: Unexpected NULL Pointer '%s' @ FILE %s, Line %u\n", \
				src, fn, #ptr, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_OPERATOR_MISSING
	 ** \brief Message for missing operators.
	 **
	 ** MSG_ERROR_OPERATOR_MISSING: Message for missing operators.
	 **/
	#ifndef MSG_ERROR_OPERATOR_MISSING
		#ifdef NDEBUG
			#define MSG_ERROR_OPERATOR_MISSING(op,str) \
				"%s: Operator '%s' Missing --> '%s'\n", src, op, str
		#else
			#define MSG_ERROR_OPERATOR_MISSING(op,str) \
				"%s[%s()]: Operator '%s' Missing --> '%s' @ FILE %s, Line %u\n", \
				src, fn, op, str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_OUT_OF_BOUNDS
	 ** \brief Message for out-of-bounds errors.
	 **
	 ** MSG_ERROR_OVERFLOW: Message for out-of-bounds errors.
	 **/
	#ifndef MSG_ERROR_OUT_OF_BOUNDS
		#ifdef NDEBUG
			#define MSG_ERROR_OUT_OF_BOUNDS(index,bounds) "%s: Index %u out of bounds [%u]\n", src, index, bounds
		#else
			#define MSG_ERROR_OUT_OF_BOUNDS(index,bounds) \
				"%s[%s()]: Index %u out of bounds [%u] @ FILE %s, Line %u\n", \
				src, fn, index, bounds, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_OVERFLOW
	 ** \brief Message for overflow errors.
	 **
	 ** MSG_ERROR_OVERFLOW: Message for overflow errors.
	 **/
	#ifndef MSG_ERROR_OVERFLOW
		#ifdef NDEBUG
			#define MSG_ERROR_OVERFLOW(ptr,len) "%s: Buffer Overflow\n", src
		#else
			#define MSG_ERROR_OVERFLOW(ptr,len) \
				"%s[%s()]: Buffer Overflow --> '%s', length = %u @ FILE %s, Line %u\n", \
				src, fn, #ptr, len, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_STR_TOO_LONG
	 ** \brief Message for too long strings.
	 **
	 ** MSG_ERROR_STR_TOO_LONG: Message for too long strings.
	 **/
	#ifndef MSG_ERROR_STR_TOO_LONG
		#ifdef NDEBUG
			#define MSG_ERROR_STR_TOO_LONG(str, maxlen) "%s: String is longer than %u\n|%s|\n", src, maxlen, str
		#else
			#define MSG_ERROR_STR_TOO_LONG(str, maxlen) \
				"%s[%s()]: String is longer than %u @ FILE %s, Line %u\n|%s|\n", \
				src, fn, maxlen, __FILE__, __LINE__, str
		#endif
	#endif

	/** \def MSG_ERROR_SYNTAX
	 ** \brief Message for syntax errors.
	 **
	 ** MSG_ERROR_SYNTAX: Message for syntax errors.
	 **/
	#ifndef MSG_ERROR_SYNTAX
		#ifdef NDEBUG
			#define MSG_ERROR_SYNTAX(str) "%s: Syntax Error --> '%s'\n", src, str
		#else
			#define MSG_ERROR_SYNTAX(str) \
				"%s[%s()]: Syntax Error --> '%s' @ FILE %s, Line %u\n", \
				src, fn, str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_TOO_FEW_ARGUMENTS
	 ** \brief Message for too few arguments.
	 **
	 ** MSG_ERROR_TOO_FEW_ARGUMENTS: Message for too few arguments.
	 **/
	#ifndef MSG_ERROR_TOO_FEW_ARGUMENTS
		#ifdef NDEBUG
			#define MSG_ERROR_TOO_FEW_ARGUMENTS "%s: Classified Error\n", src
		#else
			#define MSG_ERROR_TOO_FEW_ARGUMENTS \
				"%s[%s()]: Too Few Arguments @ FILE %s, Line %u\n", \
				src, fn, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_UNKNOWN
	 ** \brief Message for unknown errors.
	 **
	 ** MSG_ERROR_UNKNOWN: Message for unknown errors.
	 **/
	#ifndef MSG_ERROR_UNKNOWN
		#ifdef NDEBUG
			#define MSG_ERROR_UNKNOWN "%s: Unknown Error\n", src
		#else
			#define MSG_ERROR_UNKNOWN \
				"%s[%s()]: Unknown Error @ FILE %s, Line %u\n", \
				src, fn, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_UNRECOGNIZED_CONNECTIVE
	 ** \brief Message for unrecognized connectives.
	 **
	 ** MSG_ERROR_UNRECOGNIZED_CONNECTIVE: Message for unrecognized connectives.
	 **/
	#ifndef MSG_ERROR_UNRECOGNIZED_CONNECTIVE
		#ifdef NDEBUG
			#define MSG_ERROR_UNRECOGNIZED_CONNECTIVE(p) \
				"%s: Unrecognized connective in '%s'\n", src, p
		#else
			#define MSG_ERROR_UNRECOGNIZED_CONNECTIVE(p) \
				"%s[%s()]: Unrecognized connective in '%s' @ FILE %s, Line %u\n", \
				src, fn, p, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_UNSUPPORTED
	 ** \brief Message for unsupported syntaxes.
	 **
	 ** MSG_ERROR_UNSUPPORTED: Message for unsupported syntaxes.
	 **/
	#ifndef MSG_ERROR_UNSUPPORTED
		#ifdef NDEBUG
			#define MSG_ERROR_UNSUPPORTED(stx,str) \
				"%s: %s NOT Supported --> '%s'\n", src, stx, str
		#else
			#define MSG_ERROR_UNSUPPORTED(stx,str) \
				"%s[%s()]: %s NOT Supported --> '%s' @ FILE %s, Line %u\n", \
				src, fn, stx, str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_STRLEN_MISMATCH
	 ** \brief Message for string construction errors.
	 **
	 ** MSG_ERROR_STRLEN_MISMATCH: Message for string construction errors.
	 **/
	#ifndef MSG_ERROR_STRLEN_MISMATCH
		#ifdef NDEBUG
			#define MSG_ERROR_STRLEN_MISMATCH(str,len) \
				"%s: String length %u != %u\n", src, strlen(str), len
		#else
			#define MSG_ERROR_STRLEN_MISMATCH(str,len) \
				"%s[%s()]: String length %u != %u @ FILE %s, Line %u\n%s = \n\t%s\n", \
				src, fn, strlen(str), len, __FILE__, __LINE__, #str, str
		#endif
	#endif

	/** \def MSG_ERROR_UNRECOGNIZED_STR
	 ** \brief Message for unrecognized strings.
	 **
	 ** MSG_ERROR_ACTION_UNRECOGNIZED_STRING: Message for unrecognized strings.
	 **/
	#ifndef MSG_ERROR_UNRECOGNIZED_STR
		#ifdef NDEBUG
			#define MSG_ERROR_UNRECOGNIZED_STR(str) \
				"%s: Unrecognized string --> '%s'\n", src, str
		#else
			#define MSG_ERROR_UNRECOGNIZED_STR(str) \
				"%s[%s()]: Unrecognized %s --> '%s' @ FILE %s, Line %u\n", \
				src, fn, #str, str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_ERROR_ZERO
	 ** \brief Message for unexpected zero values.
	 **
	 ** MSG_ERROR_ZERO: Message for unexpected zero values.
	 **/
	#ifndef MSG_ERROR_ZERO
		#ifdef NDEBUG
			#define MSG_ERROR_ZERO(var) "%s: Unexpected Zero Value", src
		#else
			#define MSG_ERROR_ZERO(var) \
				"%s[%s()]: Unexpected Zero Value '%s' @ FILE %s, Line %u\n", \
				src, fn, #var, __FILE__,__LINE__
		#endif
	#endif

	/** \def MSG_ERROR_NOT_ZERO
	 ** \brief Message for unexpected non-zero values.
	 **
	 ** MSG_ERROR_NOT_ZERO: Message for unexpected non-zero values.
	 **/
	#ifndef MSG_ERROR_NOT_ZERO
		#ifdef NDEBUG
			#define MSG_ERROR_NOT_ZERO(var) "%s: Unexpected Non-Zero Value", src
		#else
			#define MSG_ERROR_NOT_ZERO(var) \
				"%s[%s()]: Unexpected Non-Zero Value '%s' @ FILE %s, Line %u\n", \
				src, fn, #var, __FILE__,__LINE__
		#endif
	#endif

	/** \def MSG_LOGGING_STARTED
	 ** \brief Message for when logging starts.
	 **
	 ** MSG_LOGGING_STARTED: Message for when logging starts.
	 **/
	#ifndef MSG_LOGGING_STARTED
		#ifdef NDEBUG
			#define MSG_LOGGING_STARTED(pth) "%s: STARTED Logging --> %s\n", src, pth
		#else
			#define MSG_LOGGING_STARTED(pth) \
				"%s[%s()]: STARTED Logging --> %s @ FILE %s, Line %u\n", \
				src, fn, pth, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_LOGGING_STOPPED
	 ** \brief Message for when logging stops.
	 **
	 ** MSG_LOGGING_STOPPED: Message for when logging stops.
	 **/
	#ifndef MSG_LOGGING_STOPPED
		#ifdef NDEBUG
			#define MSG_LOGGING_STOPPED(pth) "%s: STOPPED Logging --> %s\n", src, pth
		#else
			#define MSG_LOGGING_STOPPED(pth) \
				"%s[%s()]: STOPPED Logging --> %s @ FILE %s, Line %u\n", \
				src, fn, pth, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_EPISODE_COUNTER
	 ** \brief Message for when the episode counter is increased.
	 **
	 ** MSG_EPISODE_COUNTER: Message for when the episode counter is increased.
	 **/
	#ifndef MSG_EPISODE_COUNTER
		#ifdef NDEBUG
			#define MSG_EPISODE_COUNTER(eid,mid) "%s: Starting Episode %u/%u\n", src, eid, mid
		#else
			#define MSG_EPISODE_COUNTER(eid,mid) \
				"%s[%s()]: Starting Episode %u/%u @ FILE %s, Line %u\n", \
				src, fn, eid, mid, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_REPORT
	 ** \brief Message for just reporting something
	 **
	 ** MSG_REPORT: Message for just reporting something.
	 **/
	#ifndef MSG_REPORT
		#ifdef NDEBUG
			#define MSG_REPORT(txt) "%s: %s\n", src, txt
		#else
			#define MSG_REPORT(txt) "%s[%s()]: %s @ FILE %s, Line %u\n", \
				src, fn, txt, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_REPORT_VAR
	 ** \brief Message for reporting a variable.
	 **
	 ** MSG_REPORT_VAR: Message for reporting a variable.
	 **/
	#ifndef MSG_REPORT_VAR
		#ifdef NDEBUG
			#define MSG_REPORT_VAR(txt,type,str) "%s: %s => " type "\n", src, txt, str
		#else
			#define MSG_REPORT_VAR(txt,type,str) \
				"%s[%s()]: %s => " type " @ FILE %s, Line %u\n", src, fn, txt, str, __FILE__, __LINE__
		#endif
	#endif

	/** \def MSG_WARNING_FILE_NOT_FOUND
	 ** \brief Message for missing optional files.
	 **
	 ** MSG_WARNING_FILE_NOT_FOUND: Message for missing optional files.
	 **/
	#ifndef MSG_WARNING_FILE_NOT_FOUND
		#ifdef NDEBUG
			#define MSG_WARNING_FILE_NOT_FOUND(filename) "%s: %s NOT found, continuing without it...\n", src, filename
		#else
			#define MSG_WARNING_FILE_NOT_FOUND(filename) \
				"%s[%s()]: %s NOT found, continuing without it... @ FILE %s, Line %u\n", \
				src, fn, filename, __FILE__, __LINE__
		#endif
	#endif

	#ifndef XML_MAX_TAG_SIZE
		#define XML_MAX_TAG_SIZE 32
	#endif

	#ifndef XML_MAX_CONTENT_SIZE
		#define XML_MAX_CONTENT_SIZE 256
	#endif

	#ifndef XML_MAX_CHILDREN
		#define XML_MAX_CHILDREN 32
	#endif

	#ifndef XML_MAX_NODES
		#define XML_MAX_NODES 1024
	#endif

	#ifndef XML_MAX_ATTRIBUTES
		#define XML_MAX_ATTRIBUTES 32
	#endif

	#ifndef XML_MAX_ATTRIBUTE_NAME_SIZE
		#define XML_MAX_ATTRIBUTE_NAME_SIZE 32
	#endif

	#ifndef XML_MAX_ATTRIBUTE_VAL_SIZE
		#define XML_MAX_ATTRIBUTE_VAL_SIZE 256
	#endif

	#ifndef XML_META_MAX_SIZE
		#define XML_META_MAX_SIZE 250
	#endif

	#ifndef XML_EQUAL_SYMBOL
		#define XML_EQUAL_SYMBOL '='
	#endif

	#ifndef XML_QUOTE_SYMBOL
		#define XML_QUOTE_SYMBOL '"'
	#endif

	#ifndef XML_QUOTE
		#define XML_QUOTE "&quot;"
	#endif

	#ifndef XML_APOSTROPHE_SYMBOL
		#define XML_APOSTROPHE_SYMBOL '\''
	#endif

	#ifndef XML_APOSTROPHE
		#define XML_APOSTROPHE "&apos;"
	#endif

	#ifndef XML_QUOTE_SYMBOLS
		#define XML_QUOTE_SYMBOLS {XML_QUOTE_SYMBOL,XML_APOSTROPHE_SYMBOL,'\0'}
	#endif

	#ifndef XML_ATTRIBUTE
		#define XML_ATTRIBUTE(name,value)	\
			"%s%c%c%s%c",					\
			name,							\
			XML_EQUAL_SYMBOL,				\
			XML_QUOTE_SYMBOL,				\
			value,							\
			XML_QUOTE_SYMBOL
	#endif

	#ifndef XML_DEFAULT_META
		#define XML_DEFAULT_META "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>"
	#endif

	#ifndef XML_META_SYMBOL
		#define XML_META_SYMBOL '?'
	#endif

	#ifndef XML_NODE_BEGIN_SYMBOL
		#define XML_NODE_BEGIN_SYMBOL '<'
	#endif

	#ifndef XML_GT
		#define XML_GT "&gt;"
	#endif

	#ifndef XML_NODE_STOP_SYMBOL
		#define XML_NODE_STOP_SYMBOL '/'
	#endif

	#ifndef XML_NODE_END_SYMBOL
		#define XML_NODE_END_SYMBOL '>'
	#endif

	#ifndef XML_LT
		#define XML_LT "&lt;"
	#endif

	#ifndef XML_AMP_SYMBOL
		#define XML_AMP_SYMBOL '&'
	#endif

	#ifndef XML_AMP
		#define XML_AMP "&amp;"
	#endif
#endif
