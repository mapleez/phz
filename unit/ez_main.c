/*
 * author : ez
 * date : 2015/10/1
 * describe : The main entry. All the
 *       initialization and caller
*/

#include "ez_main.h"
// #include "ez_prog_args.h"
#include <getopt.h>

// pfile_entity fentity;
// pprog_args pargs;


static void main_dispose ();


static void main_dispose (/*pfile_entity _f*/) {
	// disponse (_f);
}

int main (int argc, char* argv []) {

	int arg = 0;
	char* filename = NULL;
	// main_init_args ();
	while ((arg = 
		getopt_long (argc, argv, ez_arg_string,
			ez_longopts, NULL)) != -1) {
		switch (arg) {
			case 'a': 
				filename = argv [optind];
				// init (filename);
				// ez_disp_arch (fentity);
				break;

			case 'C':
				filename = argv [optind];
				// init (filename);
				// ez_disp_check (fentity);
				break;

			case 'e':
				filename = argv [optind];
				// init (filename);
				// ez_disp_eat_info (fentity);
				break;

			case 'i':
				filename = argv [optind];
				// init (filename);
				// ez_disp_iat_info (fentity);
				break;

			case 's':
				filename = argv [optind];
				// init (filename);
				// ez_disp_file_simple (fentity);
				break;

			case 'h':
				filename = argv [optind];
				// init (filename);
				// ez_disp_help ();
				break;

			default:
				die ("Invalid options:");
				// filename = argv [optind];
				// init (filename);
				// ez_disp_dos (fentity);
				// ez_disp_nt (fentity);
				break;
		}
	}

	main_dispose (/*fentity*/);
	return 0;
}
