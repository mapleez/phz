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

// for import table structure
typedef struct _thunk {
	union {
		uint32_t _hint;
		uint32_t _origin;
	} _number;
	char* _func_name;
	uint32_t _func_addr;
} thunk,
	*pthunk;

typedef struct _import {
	int _total_funcs;
	char* _name;
	pthunk _funcs;
} file_import,
	*pfile_import;


// for export table structure
typedef struct _export {
	int _total_funcs;
	int _named_funcs;
	char* _name;
	pthunk _funcs;
} file_export,
	*pfile_export;

#endif // ~ _EZ_FILE_ENTITY_H_

