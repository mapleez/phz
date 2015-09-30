#ifdef _EZ_PROG_ARGS_H_
#	define _EZ_PROG_ARGS_H_

/*
 * author : ez
 * date : 2015/9/30
 * describe : this file define the display 
 *        functions for each input option
*/

// define the 
// displayed position
typedef
struct _prog_args {

	uint32_t _eat	:1;
	uint32_t _iat	:1;
	uint32_t _sgm	:1;
	uint32_t _dos	:1;
	uint32_t _nt	:1;
	uint32_t _arch	:1;
	uint32_t _smp	:1;
	uint32_t _flds	:1;

	uint32_t _padd	:24;

} prog_args, 
	*pprog_args;

#endif // ~ _EZ_PROG_ARGS_H_
