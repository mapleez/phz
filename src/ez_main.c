/*
 * author : ez
 * date : 2015/10/1
 * describe : The main entry. All the
 *       initialization and caller
*/

#include "ez_main.h"
#include "ez_prog_args.h"
#include <getopt.h>

pfile_entity fentity;
pprog_args pargs;

static void main_init_args ();
static void main_init_fengine ();
static void main_init_fentity ();
static void main_init_disp ();
static void main_dispose ();

int main (int argc, char* argv) {
	int arg = 0;
	while ((arg = 
		getopt_long (argc, argv, ez_arg_string,
			ez_longopts, NULL)) != -1) {
		
		switch (arg) {
			case 'a': 
				println ("option a.");
				break;
			case 'C':
				println ("option C.");
				break;

			case 'e':
				println ("option e.");
				break;

			case 'i':
				println ("option i.");
				break;

			case 's':
				println ("option s.");
				break;
			default:
				// simply display information
				println ("default options");
				break;
		}
	}
	return 0;
}
