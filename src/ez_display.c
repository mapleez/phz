#include "ez_display.h"
#include "ez_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <windows.h>

int offset = 0;

void
ez_disp_file_simple (pfile_entity _f) {
}

void
ez_disp_eat_info (pfile_entity _f) {

}

void
ez_disp_dos (pfile_entity _f) {
#	define IMAGE_DOS_HEADER DHD
	! _f && read_dos_head (_f);
	printf ("%08x  e_magic          wd: %04x (\"MZ\")\r\n", offsetof (DHD, e_magic), dos.e_magic);
	printf ("%08x  e_cblp           wd: %04x\r\n", offsetof (DHD, e_cblp), dos.e_cblp);
	printf ("%08x  e_cp             wd: %04x\r\n", offsetof (DHD, e_cp), dos.e_cp);
	printf ("%08x  e_crlc           wd: %04x\r\n", offsetof (DHD, e_crlc), dos.e_crlc);
	printf ("%08x  e_cparhdr        wd: %04x\r\n", offsetof (DHD, e_cparhdr), dos.e_cparhdr);
	printf ("%08x  e_minalloc       wd: %04x\r\n", offsetof (DHD, e_minalloc), dos.e_minalloc);
	printf ("%08x  e_maxalloc       wd: %04x\r\n", offsetof (DHD, e_maxalloc), dos.e_maxalloc);
	printf ("%08x  e_ss             wd: %04x\r\n", offsetof (DHD, e_ss), dos.e_ss);
	printf ("%08x  e_sp             wd: %04x\r\n", offsetof (DHD, e_sp), dos.e_sp);
	printf ("%08x  e_csum           wd: %04x\r\n", offsetof (DHD, e_csum), dos.e_csum);
	printf ("%08x  e_ip             wd: %04x\r\n", offsetof (DHD, e_ip), dos.e_ip);
	printf ("%08x  e_cs             wd: %04x\r\n", offsetof (DHD, e_cs), dos.e_cs);
	printf ("%08x  e_lfarlc         wd: %04x\r\n", offsetof (DHD, e_lfarlc), dos.e_lfarlc);
	printf ("%08x  e_ovno           wd: %04x\r\n", offsetof (DHD, e_ovno), dos.e_ovno);
	printf ("%08x  e_res[0]         wd: %04x\r\n", offsetof (DHD, e_res [0]), dos.e_res [0]);
	printf ("%08x  e_res[1]         wd: %04x\r\n", offsetof (DHD, e_res [1]), dos.e_res [1]);
	printf ("%08x  e_res[2]         wd: %04x\r\n", offsetof (DHD, e_res [2]), dos.e_res[2]);
	printf ("%08x  e_res[3]         wd: %04x\r\n", offsetof (DHD, e_res [3]), dos.e_res[3]);
	printf ("%08x  e_oemid          wd: %04x\r\n", offsetof (DHD, e_oemid), dos.e_oemid);
	printf ("%08x  e_oeminfo        wd: %04x\r\n", offsetof (DHD, e_oeminfo), dos.e_oeminfo);
	printf ("%08x  e_res2[0]        wd: %04x\r\n", offsetof (DHD, e_res2 [0]), dos.e_res2[0]);
	printf ("%08x  e_res2[1]        wd: %04x\r\n", offsetof (DHD, e_res2 [1]), dos.e_res2[1]);
	printf ("%08x  e_res2[2]        wd: %04x\r\n", offsetof (DHD, e_res2 [2]), dos.e_res2[2]);
	printf ("%08x  e_res2[3]        wd: %04x\r\n", offsetof (DHD, e_res2 [3]), dos.e_res2[3]);
	printf ("%08x  e_res2[4]        wd: %04x\r\n", offsetof (DHD, e_res2 [4]), dos.e_res2[4]);
	printf ("%08x  e_res2[5]        wd: %04x\r\n", offsetof (DHD, e_res2 [5]), dos.e_res2[5]);
	printf ("%08x  e_res2[6]        wd: %04x\r\n", offsetof (DHD, e_res2 [6]), dos.e_res2[6]);
	printf ("%08x  e_res2[7]        wd: %04x\r\n", offsetof (DHD, e_res2 [7]), dos.e_res2[7]);
	printf ("%08x  e_res2[8]        wd: %04x\r\n", offsetof (DHD, e_res2 [8]), dos.e_res2[8]);
	printf ("%08x  e_res2[9]        wd: %04x\r\n", offsetof (DHD, e_res2 [9]), dos.e_res2[9]);
	printf ("%08x  e_lfanew         dw: %08x\r\n", offsetof (DHD, e_lfanew), dos.e_lfanew);
}

void
ez_disp_check (pfile_entity _f) {
	bool flag = false;
	if (! _f) {
		if (read_dos_head (_f) && 
				read_nt_head (_f)) {
			flag = 
				_f -> _dos_header -> e_magic == magic && 
				_f -> _nt_header -> Signature -> signature;
		}

	}

	printf ("We checked the file:%s\n", 
			flag ? "true" : "false");

}


void
ez_disp_iat_info (pfile_entity _f) {
}

void
ez_disp_arch (pfile_entity _f) {
	// int tmp = 0; 
	uint32_t nt_offset = 0,
			 opt_size = 0,
			 seg_head_offset = 0;
	int i = 0;
	if (read_dos_head (_f) &&
		read_nt_head (_f) &&
		read_segment_header (_f)) 
	{
		// dos header
		println ("DOS: 0x00 ~ 0x40 (offset)\n");

		nt_offset = (uint32_t) _f -> _dos_header ->
			e_lfanew;
		opt_size = (uint32_t) _f -> nt_headers -> 
			FileHeader.SizeofOptionalHeader;
		seg_head_offset = opt_size + 4 + 
			sizeof (IMAGE_FILE_HEADER);

		// nt header
		printf ("NT: 0x%04x ~ 0x%04x (offset)\n", 
				nt_offset,
				seg_head_offset - 1);
		printf ("Sections\n"
			"------------------------------\n");
		// section headers 
		// for (; i < _f -> nt_headers -> 
		// 	FileHeader.NumberOfSections; ++ i)
		// {
		// 	printf ("%s: 0x%08x ~ 0x%08x "
		// 			"(offset)\n",
		// 			_f -> _sec_header [i].name);
		// }

	}
}

// void
// ez_disp_fields (pfile_entity _f) {
// }

void
ez_disp_help () {
	printf ("PE file parser %s\n"
			"%s\n"
			"author : \n",
			version,
			help_str
		   );
	printf ("  %s %s\n", author [0], email [0]);
	printf ("  %s %s\n", author [1], email [1]);
}


