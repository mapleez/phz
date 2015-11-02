/*
 * author : ez
 * date : 2015/10/8
 * describe : useful tools
*/

#include "ez_tools.h"
#include <stdlib.h>

// #if defined (_WIN32) && defined (__cplusplus)
int die (const char* _str) {
	println (_str);
	exit (0);
	return 1;
}
// #endif
