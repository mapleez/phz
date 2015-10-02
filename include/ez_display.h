#ifndef _EZ_DISPLAY_H_
#	define _EZ_DISPLAY_H_

/*
 * author : ez
 * date : 2015/9/30
 * describe : this file define the display 
 *        functions for each input option
*/

#include "ez_file_entity.h"
#include "ez_prog_args.h"


extern void
ez_disp_file_simple (pfile_entity);

extern void
ez_disp_eat_info (pfile_entity);

extern void
ez_disp_iat_info (pfile_entity);

extern void
ez_disp_check (pfile_entity);

extern void
ez_disp_nt (pfile_entity);

extern void
ez_disp_dos (pfile_entity);

extern void
ez_disp_arch (pfile_entity);

extern void
ez_disp_help ();

#endif // ~ _EZ_DISPLAY_H_


