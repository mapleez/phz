/*
 * author : ez
 * date : 2015/10/1
 * describe : The main entry. All the
 *       initialization and caller
*/

#include "ez_main.h"
#include "ez_display.h"
#include "hh_fengine.h"
#include "getopt.h"

pfile_entity fentity;

static void main_dispose (pfile_entity);

static void main_dispose (pfile_entity _f) {
	// from hh_fengine.h
	hh_desponse (_f);
}

int main (int argc, char* argv []) {

	int arg = 0;
	char* filename = NULL;
	while ((arg = 
		getopt_long (argc, argv, ez_arg_string,
			ez_longopts, NULL)) != -1) {
		switch (arg) {
			case 'a': 
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_arch (fentity);
				break;

			case 'C':
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_check (fentity);
				break;

			case 'e':
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_eat_info (fentity);
				break;

			case 'i':
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_iat_info (fentity);
				break;

			case 's':
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_file_simple (fentity);
				break;

			case 'h':
				ez_disp_help ();
				break;

			default:
				filename = argv [optind];
				if (! (fentity = hh_init (filename)))
					die ("Initialize error...");
				ez_disp_dos (fentity);
				ez_disp_nt (fentity);
				break;
		}
	}

	main_dispose (fentity);
	return 0;
}
