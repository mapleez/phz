#ifndef _EZ_TOOLS_H_
#	define _EZ_TOOLS_H_

#include <stdio.h>

#	define println(___S) \
		printf ("%s\n", ___S)

//#if !defined (_WIN32) || !defined (__cplusplus)
//#	define die(___S) ({	\
//		println (___S);	\
//		exit (0); \
//		1;	\
//	})
//#else

extern 
int die (const char*);

// #endif

#ifndef  NULL
#	define NULL ((void*)0)
#endif // ~ NULL

#endif // ~ _EZ_TOOLS_H_
