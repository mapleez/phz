#ifndef _EZ_DISPLAY_H_
#	define _EZ_DISPLAY_H_

/*
 * author : ez
 * date : 2015/9/30
 * describe : this file define the display 
 *        functions for each input option
*/

#include <stdio.h>
#include <stdlib.h>
#include "ez_file_entity.h"
#include "ez_prog_args.h"
#include <stdint.h>

// // define the 
// // displayed position
// struct _disp_pos {
// 
// 	uint32_t _eat	:1;
// 	uint32_t _iat	:1;
// 	uint32_t _sgm	:1;
// 	uint32_t _dos	:1;
// 	uint32_t _nt	:1;
// 	uint32_t _arch	:1;
// 	uint32_t _smp	:1;
// 	uint32_t _flds	:1;
// 
// 	uint32_t _padd	:24;
// 
// };

extern void
ez_disp_file_simple (pfile_entity);

extern void
ez_disp_eat_info (pfile_entity);

extern void
ez_disp_iat_info (pfile_entity);

extern void
ez_disp_check (pfile_entity);

extern void
ez_disp_arch (pfile_entity);

extern void
ez_disp_fields (pfile_entity, pprog_args);


#endif // ~ _EZ_DISPLAY_H_
