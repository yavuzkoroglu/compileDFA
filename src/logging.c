/** \file logging.c
 ** \brief Implements the functions declared in logging.h
 **/
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "debug.h"
#include "stdioplus.h"

DECLARE_SOURCE("LOG");

/** \brief The file descriptor for the log file.
 **/
FILE* _logFile;

int vsnprintf_rpl(char* s, size_t n, const char* pattern, va_list args)
{
	DECLARE_FUNCTION(vsnprintf);

	/* Variable declarations. */
	#ifdef LENGTH_SHORT
		#undef LENGTH_SHORT
	#endif
	#ifdef LENGTH_MODERATE
		#undef LENGTH_MODERATE
	#endif
	#ifdef LENGTH_LONG
		#undef LENGTH_LONG
	#endif
	#define LENGTH_SHORT 0
	#define LENGTH_MODERATE 1
	#define LENGTH_LONG 2
	#define LENGTH_LONG_LONG 3
	int force_sign, left_justify, width, precision, length;
	unsigned int len;
	char formatStr[BUFFER_SIZE], *formatPtr = formatStr;
	char* str;
	const char* ptr;

	/* Check. */
	ASSERT_NOT_NULL(s);

	str = s;
	len = 0;
	for (ptr = pattern; (*ptr); ptr++) {
		force_sign = 0;
		left_justify = 0;
		width = -1;
		precision = -1;
		length = LENGTH_MODERATE;
		if (*ptr == '%') {
			/* Skip the % character. */
			ptr++;

			/* Check flags. */
			/* TODO: Implement (space), #, and 0 flags. */
			if (*ptr == '-') {
				ptr++;
				left_justify = 1;
			}
			if (*ptr == '+') {
				ptr++;
				force_sign = 1;
			}

			/* Check width. */
			if (isdigit(*ptr)) {
				for (width = 0; (*ptr) && isdigit(*ptr); width = 10*width + (*(ptr++) - '0'));
			} else if (*ptr == '*') {
				ptr++;
				width = va_arg(args, int);
			}

			/* Check precision. */
			if (*ptr == '.') {
				/* Skip punctuation. */
				ptr++;

				/* Get precision. */
				if (isdigit(*ptr)) {
					for (precision = 0; (*ptr) && isdigit(*ptr); precision = 10*precision + (*(ptr++) - '0'));
				} else if (*ptr == '*') {
					ptr++;
					precision = va_arg(args, int);
				} else {
					/* Format error. */
					exit(1);
				}
			}

			/* Check length. */
			if (*ptr == 'h') {
				ptr++;
				length = LENGTH_SHORT;
			} else if ((*ptr == 'l' && *(ptr+1) == 'l') || (*ptr == 'L')) {
				ptr++;
				if (*ptr == 'l')
					ptr++;
				length = LENGTH_LONG_LONG;
			} else if (*ptr == 'l') {
				ptr++;
				length = LENGTH_LONG;
			}

			/* Get specifier. */
			formatPtr = formatStr;
			sprintf(formatPtr, "%%");
			formatPtr += strlen(formatPtr);
			if (left_justify) {
				sprintf(formatPtr, "-");
				formatPtr += strlen(formatPtr);
			}
			if (force_sign) {
				sprintf(formatPtr, "+");
				formatPtr += strlen(formatPtr);
			}
			if (width >= 0) {
				sprintf(formatPtr, "%d", width);
				formatPtr += strlen(formatPtr);
			}
			if (precision >= 0) {
				sprintf(formatPtr, ".%d", precision);
				formatPtr += strlen(formatPtr);
			}
			if (length == LENGTH_SHORT) {
				sprintf(formatPtr, "h");
				formatPtr += strlen(formatPtr);
			} else if (length == LENGTH_LONG_LONG) {
				if (*ptr == 'f') {
					sprintf(formatPtr, "L");
					formatPtr += strlen(formatPtr);
				} else {
					sprintf(formatPtr, "ll");
					formatPtr += strlen(formatPtr);
				}
			} else if (length == LENGTH_LONG) {
				sprintf(formatPtr, "l");
				formatPtr += strlen(formatPtr);
			}

			/* Get specifier. */
			if (*ptr == '%') {
				if (formatPtr - formatStr > 1) {
					/* Format error. */
					exit(1);
				}

				sprintf(str, "%%");
			} else if (*ptr == 'c') {
				sprintf(formatPtr, "c");
				sprintf(str, formatStr, va_arg(args, int));
			} else if (*ptr == 'd') {
				sprintf(formatPtr, "d");
				if (length <= LENGTH_MODERATE)
					sprintf(str, formatStr, va_arg(args, int));
				else
					sprintf(str, formatStr, va_arg(args, long));
			} else if (*ptr == 'u') {
				sprintf(formatPtr, "u");
				if (length <= LENGTH_SHORT)
					sprintf(str, formatStr, va_arg(args, unsigned));
				else
					sprintf(str, formatStr, va_arg(args, unsigned long));
			} else if (*ptr == 'f') {
				sprintf(formatPtr, "f");
				sprintf(str, formatStr, va_arg(args, double));
			} else if (*ptr == 's') {
				if (formatPtr - formatStr > 1) {
					/* Format error. */
					exit(1);
				}

				sprintf(str, "%s", va_arg(args, char*));
			} else {
				/* TODO: Implement more specifiers. */
				exit(1);
			}
		} else {
			sprintf(str, "%c", *ptr);
		}
		str += strlen(str);
		len = str - s;
		ASSERT_FITS_IN_BOUND(len, BUFFER_LARGE_SIZE);
	}

	if (len > n)
		s[n] = '\0';
	else
		s[len] = '\0';

	return len;
}

/** \brief Writes the given string only to logs.
 ** \param format A format string
 ** \param va_list A variadic list of parameters
 **
 ** NOTE: Must observe [!vWriteLog U start_logging]
 **/
void vWriteLog(const char* format, va_list args)
{
	vfprintf(_logFile, format, args);
	va_end(args);
	fflush(_logFile);
}

/** \brief Writes the given string only to logs.
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!writeLog U start_logging]
 **/
void writeLog(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vWriteLog(format, args);
}

/** \brief Writes the given string both to logs and to standard output.
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Should NOT 'vSay' strings longer than LOG_SAY_MAX.
 ** NOTE: Must observe [!vSay U start_logging]
 **/
void vSay(const char* format, va_list args)
{
	char buffer[LOG_SAY_MAX];

	/* vsnprintf() is a non-standard C library function. */
	#ifdef VSNPRINTF_SUPPORTED
		vsnprintf(buffer, LOG_SAY_MAX, format, args);
	#else
		vsnprintf_rpl(buffer, LOG_SAY_MAX, format, args);
	#endif
	va_end(args);

	printf("%s", buffer);
	fprintf(_logFile, "%s", buffer);
	fflush(stdout);
	fflush(_logFile);
}

/** \brief Writes the given string both to logs and to standard output.
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Should NOT 'say' strings longer than LOG_SAY_MAX.
 ** NOTE: Must observe [!say U start_logging]
 **/
void say(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vSay(format, args);
}

/** \brief Warning only if a given warning condition holds.
 ** \param warningCondition The warning condition
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Must observe [!vWarningIf U start_logging]
 **/
void vWarningIf(const int warningCondition, const char* format, va_list args)
{
	if (warningCondition) {
		vWarning(format, args);
	} else {
		va_end(args);
	}
}

/** \brief Warning only if a given error condition holds.
 ** \param warningCondition The warning condition
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!warningIf U start_logging]
 **/
void warningIf(const int warningCondition, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vWarningIf(warningCondition, format, args);
}

/** \brief Warning if a given no-warning condition fails.
 ** \param noWarningCondition The no-warning condition
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Must observe [!vWarningUnless U start_logging]
 **/
void vWarningUnless(const int noWarningCondition, const char* format, va_list args)
{
	if (noWarningCondition) {
		va_end(args);
	} else {
		vWarning(format, args);
	}
}

/** \brief Warning if a given no-warning condition fails.
 ** \param noWarningCondition The no-warning condition
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!warningUnless U start_logging]
 **/
void warningUnless(const int noWarningCondition, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vWarningUnless(noWarningCondition, format, args);
}

/** \brief Gives a warning of an error and terminates the program.
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Must observe [!vError U start_logging]
 **/
void vError(const char* format, va_list args)
{
	vWarning(format, args);
	exit(1);
}

/** \brief Gives a warning of an error and terminates the program.
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!error U start_logging]
 **/
void error(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vError(format, args);
}

/** \brief Error only if a given error condition holds.
 ** \param errorCondition The error condition
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Must observe [!vErrorIf U start_logging]
 **/
void vErrorIf(const int errorCondition, const char* format, va_list args)
{
	if (errorCondition) {
		vError(format, args);
	} else {
		va_end(args);
	}
}

/** \brief Error only if a given error condition holds.
 ** \param errorCondition The error condition
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!errorIf U start_logging]
 **/
void errorIf(const int errorCondition, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vErrorIf(errorCondition, format, args);
}

/** \brief Error if a given no-error condition fails.
 ** \param noErrorCondition The no-error condition
 ** \param format A format string
 ** \param args A variadic list of parameters
 **
 ** NOTE: Must observe [!vErrorUnless U start_logging]
 **/
void vErrorUnless(const int noErrorCondition, const char* format, va_list args)
{
	if (noErrorCondition) {
		va_end(args);
	} else {
		vError(format, args);
	}
}

/** \brief Error if a given no-error condition fails.
 ** \param noErrorCondition The no-error condition
 ** \param format A format string
 ** \param ... Additional parameters
 **
 ** NOTE: Must observe [!errorUnless U start_logging]
 **/
void errorUnless(const int noErrorCondition, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vErrorUnless(noErrorCondition, format, args);
}

/** \brief Deletes previously saved logs and starts logging to _logFile.
 **
 ** NOTE: Must observe G[start_logging -> GX(!start_logging U stop_logging)]
 **/
void start_logging()
{
	DECLARE_FUNCTION(start_logging);
	SAFE_FOPEN(_logFile, LOG_PATH, "w");
	say(MSG_LOGGING_STARTED(LOG_PATH));
}

/** \brief Closes _logFile.
 **/
void stop_logging()
{
	DECLARE_FUNCTION(stop_logging);
	say(MSG_LOGGING_STOPPED(LOG_PATH));
	fclose(_logFile);
}
