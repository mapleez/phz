// #include "unit.h"

#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>
#include <memory.h>
#include "grammar.h"

struct in {
	int mc;
	int mb;
};

#	define in_size sizeof (struct in)

struct xp {
	int x;
	struct in* y;
#	define in_mc y -> mc;
#	define in_mb y -> mb;
	int mxh;
};

#	define xp_size sizeof (struct xp)

void* create_xp () {
	// xp c;

	// sizeof (c);
	// xp* m;
	// m = malloc ()
	// m -> x;

	struct xp* res = (struct xp*) 
		malloc (xp_size);
	memset (res, 0, xp_size);
	if (res) {
		res -> y = (struct in*) malloc (in_size);
		memset ((void*) res -> y, 0, in_size);
	}
	return (void*) res;
}


int main (int argc, char* argv []) {

	int i = 0;
	for (; i < 4; i ++) {
		printf ("%s, %d, %d, %d\n", 
				myopt [i].arc,
				myopt [i].x,
				myopt [i].y,
				myopt [i].z
			   );
	}

	// struct xp* test_xp = create_xp ();
	// int mc = test_xp -> in_mc;
	// int mb = test_xp -> in_mb;
	// int tag = 102;

	// tag = mc + mb;

	return 0;
}
