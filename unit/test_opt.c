#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <getopt.h>

const char* arg_string = "abc:foi";

int main (int argc, char * argv []) {
	int opt = 0;
	while ((opt = getopt (argc, argv, arg_string)) != -1) {
		switch (opt) {
			case 'a':
				printf ("I find you have gotten me the a option\n");
				break;
			case 'b':
				printf ("I find you have gotten me the b option\n");
				break;
			case 'c':
				printf ("I find you have gotten me the c option\n");
				break;
			case 'f':
				printf ("I find you have gotten me the f option\n");
				break;
			case 'o':
				printf ("I find you have gotten me the o option\n");
				break;
			case 'i':
				printf ("I find you have gotten me the i option\n");
				break;
			default:
				break;
		}
	}

	return 0;
}
