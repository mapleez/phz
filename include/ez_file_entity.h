#ifndef _EZ_FILE_ENTITY_H_
#	define _EZ_FILE_ENTITY_H_

/*
 * author : ez
 * date : 2015/9/30
 * describe : this structure stored all
 *			the data readed from input
 *			PE file, stored into PE file
 *			structures.
*/

#include <winnt.h>
#include <stdint.h>

typedef struct _file_entity {

	PIMAGE_DOS_HEADER _dos_header;
	uint8_t* _dos_stub;
	PIMAGE_NT_HEADERS _nt_headers;
#	define _file_header _nt_headers -> FileHeader
#	define _opt_header _nt_headers -> OptionalHeader
	PIMAGE_SECTION_HEADER _sec_header;

} file_entity, 
	*pfile_entity;


#endif // ~ _EZ_FILE_ENTITY_H_
