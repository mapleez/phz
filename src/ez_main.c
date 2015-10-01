/*
 * author : ez
 * date : 2015/10/1
 * describe : The main entry. All the
 *       initialization and caller
*/

#include "ez_main.h"
// #include "ez_prog_args.h"
#include <getopt.h>

pfile_entity fentity;
// pprog_args pargs;

/*
   Initialize arguments
*/
// static void main_init_args ();
// static void main_init_fengine ();
// static void main_init_fentity ();
// static void main_init_disp ();
static void main_dispose ();

// static void main_init_args () {
// 	pargs = (pprog_args) malloc (prog_args_size);
// 	if (! pargs); // TODO
// 	memset (pargs, 0, prog_args_size);
// }

static void main_dispose () {
}

int main (int argc, char* argv) {

	int arg = 0;
	// main_init_args ();
	while ((arg = 
		getopt_long (argc, argv, ez_arg_string,
			ez_longopts, NULL)) != -1) {
		switch (arg) {
			case 'a': 

				// pprog_args -> _arch = 1;
				// pprog_args -> _smp = 1;
				// println ("option a.");
				break;

			case 'C':
				ez_disp_check (fentity);
				// println ("option C.");
				break;

			case 'e':
				// pprog_args -> _eat = 1;
				// pprog_args -> _smp = 1;
				// println ("option e.");
				break;

			case 'i':
				// pprog_args -> _iat = 1;
				// pprog_args -> _smp = 1;
				// println ("option i.");
				break;

			case 's':
				// pprog_args -> _smp = 1;
				// println ("option s.");
				break;

			case 'h':
				ez_disp_help ();
				break;

			default:
				// pprog_args -> _smp = 1;
				// pprog_args -> _dos = 1;
				// pprog_args -> _sgm = 1;
				// pprog_args -> _nt  = 1;
				// simply display information
				// println ("default options");
				break;
		}
	}
	return 0;
}
