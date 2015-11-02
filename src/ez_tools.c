/*
 * author : ez
 * date : 2015/10/8
 * describe : useful tools
*/

#include "ez_tools.h"
#include "hh_fengine.c"
#include <stdlib.h>

// #if defined (_WIN32) && defined (__cplusplus)
int die (const char* _str) {
	println (_str);
	hh_desponse (NULL);
	exit (0);
	return 1;
}
// #endif
