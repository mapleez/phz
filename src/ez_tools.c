#include "ez_tools.h"
#include <stdlib.h>

int die (const char* _str) {
	println (_str);
	exit (0);
	return 1;
}
