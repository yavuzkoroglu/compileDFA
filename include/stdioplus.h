/** \file stdioplus.h
 ** \brief Declares some extremely useful but non-standard input/output manipulation macros.
 **/
#include "debug.h"

#ifdef SAFE_FOPEN
	#undef SAFE_FOPEN
#endif
#define SAFE_FOPEN(fp,filepath,mode) fp = fopen(filepath, mode); ASSERT_NOT_NULL(fp)

#ifdef SAFE_POPEN
	#undef SAFE_POPEN
#endif
#define SAFE_POPEN(fp,filepath,mode) fp = popen(filepath, mode); ASSERT_NOT_NULL(fp)
