/** \file stringplus.h
 ** \brief Declares some extremely useful but non-standard string manipulation functions.
 **/
#include <stdarg.h>

char* vFromPattern(char*,unsigned int,const char*,va_list);
char* fromPattern(char*,unsigned int,const char*,...);
