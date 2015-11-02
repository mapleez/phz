/*
 * author : ez
 * date : 2015/10/2
 * describe : this file implement the 
 * 	display function.
*/

#include "ez_display.h"
#include "hh_fengine.h"
#include "ez_tools.h"
#include "version.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef __cplusplus
#include "stdbool.h"
#endif

#include <stddef.h>
#include <windows.h>


/*
   Display file information simply, about 
   only common attributes, e.g. file size.
*/
void
ez_disp_file_simple (pfile_entity _f) {
}

/*
   display PE Export Function Table 
   structure. one line for one function.
*/
void
ez_disp_eat_info (pfile_entity _f) {
	pfile_export exp = NULL;
	int i = 0;
	_f && hh_read_dos_head (_f) &&
		hh_read_NT_head (_f) &&
		hh_read_segment_header (_f) ||
		die ("Cannot read file data."
			 "Unknown error.");
	// pfile_export  printexporttable (pfile_entity _f);
	if (! (exp = 
			hh_PrintExportTable (_f)))
		die ("Cannot read import tables."
			 "Unknown error.");
	printf ("Export tables %s:\n",
			exp -> _name);
// 	for (; i <= imp_num; ++ i) {
// 		pfile_import lib = &(imp [i]);
// 		println ("%d. %s\n",
// 				i + 1, 
// 				lib -> _name);
	// int f_idx = 0;
	for (; i < exp -> _total_funcs; 
			++ i)
	{
		pthunk func = exp -> _funcs + i;
		printf ("  %d. 0x%08x 0x%04x  %s\n",
				i + 1, // NO
				func -> _func_addr, // function address
				func -> _number._origin,// hint
				func -> _func_name);
	}
}

/*
   display PE NT header (or COFF header).
   each fields offset and value.
*/
void
ez_disp_nt (pfile_entity _f) {
	int nt_offset = 0,
		opt_size = 0,
		opt_offset = 0;
	uint16_t opt_magic = 0;
	_f && hh_read_dos_head (_f) && 
		hh_read_NT_head (_f) || 
		die ("Cannot read NT header."
			 "Unknown error :-("); // im so sorry for this @.o||
	nt_offset = (int) _f -> _dos_header -> e_lfanew;
	opt_size = (int) _f -> _file_header.SizeOfOptionalHeader;
	opt_offset = (int) (nt_offset + 4 + sizeof (IMAGE_FILE_HEADER));
	opt_magic = (uint16_t) _f -> _opt_header.Magic;

	// nt header
	println ("NT header:");
	printf ("%08x  Signature           dw: %04x\n", 
				offsetof (IMAGE_NT_HEADERS, Signature) + nt_offset, 
				_f -> _nt_headers -> Signature);
	// file header
#	define IFH IMAGE_FILE_HEADER 
#	define IOH IMAGE_OPTIONAL_HEADER
// #	define IOH64 IMAGE_OPTIONAL64_HEADER
	println ("--> FileHeader:");
	printf ("    %08x  Machine                      wd: %04x\n", opt_offset + offsetof (IFH, Machine), _f -> _file_header.Machine);
	printf ("    %08x  NumberOfSections             wd: %04x\n", opt_offset + offsetof (IFH, NumberOfSections), _f -> _file_header.NumberOfSections);
	printf ("    %08x  TimeDateStamp                dw: %08x\n", opt_offset + offsetof (IFH, TimeDateStamp), _f -> _file_header.TimeDateStamp);
	printf ("    %08x  PointerToSymbolTable         dw: %08x\n", opt_offset + offsetof (IFH, PointerToSymbolTable), _f -> _file_header.PointerToSymbolTable);
	printf ("    %08x  NumberOfSymbols              dw: %08x\n", opt_offset + offsetof (IFH, NumberOfSymbols), _f -> _file_header.NumberOfSymbols);
	printf ("    %08x  SizeOfOptionalHeader         wd: %04x\n", opt_offset + offsetof (IFH, SizeOfOptionalHeader), _f -> _file_header.SizeOfOptionalHeader);

	/* optional header
	 * In this version we just 
	 * provide optional 32 bits analysis
	*/
	println ("--> OptionalHeader:");
	printf ("    %08x  Magic                        wd: %04x\n", opt_offset + offsetof (IOH, Magic), _f -> _opt_header.Magic);
	printf ("    %08x  MajorLinkerVersion           b : %02x\n", opt_offset + offsetof (IOH, MajorLinkerVersion), _f -> _opt_header.MajorLinkerVersion);
	printf ("    %08x  MinorLinkerVersion           b : %02x\n", opt_offset + offsetof (IOH, MinorLinkerVersion), _f -> _opt_header.MinorLinkerVersion);
	printf ("    %08x  SizeOfCode                   dw: %08x\n", opt_offset + offsetof (IOH, SizeOfCode), _f -> _opt_header.SizeOfCode);
	printf ("    %08x  SizeOfInitializedData        dw: %08x\n", opt_offset + offsetof (IOH, SizeOfInitializedData), _f -> _opt_header.SizeOfInitializedData);
	printf ("    %08x  SizeOfUninitializedData      dw: %08x\n", opt_offset + offsetof (IOH, SizeOfUninitializedData), _f -> _opt_header.SizeOfUninitializedData);
	printf ("    %08x  AddressOfEntryPoint          dw: %08x\n", opt_offset + offsetof (IOH, AddressOfEntryPoint), _f -> _opt_header.AddressOfEntryPoint);
	printf ("    %08x  BaseOfCode                   dw: %08x\n", opt_offset + offsetof (IOH, BaseOfCode), _f -> _opt_header.BaseOfCode);
	printf ("    %08x  BaseOfData                   dw: %08x\n", opt_offset + offsetof (IOH, BaseOfData), _f -> _opt_header.BaseOfData);
	printf ("    %08x  ImageBase                    dw: %08x\n", opt_offset + offsetof (IOH, ImageBase), _f -> _opt_header.ImageBase);
	printf ("    %08x  SectionAlignment             dw: %08x\n", opt_offset + offsetof (IOH, SectionAlignment), _f -> _opt_header.SectionAlignment);
	printf ("    %08x  FileAlignment                dw: %08x\n", opt_offset + offsetof (IOH, FileAlignment), _f -> _opt_header.FileAlignment);
	printf ("    %08x  MajorOperatingSystemVersion  wd: %04x\n", opt_offset + offsetof (IOH, MajorOperatingSystemVersion), _f -> _opt_header.MajorOperatingSystemVersion);
	printf ("    %08x  MinorOperatingSystemVersion  wd: %04x\n", opt_offset + offsetof (IOH, MinorOperatingSystemVersion), _f -> _opt_header.MinorOperatingSystemVersion);
	printf ("    %08x  MajorImageVersion            wd: %04x\n", opt_offset + offsetof (IOH, MajorImageVersion), _f -> _opt_header.MajorImageVersion);
	printf ("    %08x  MinorImageVersion            wd: %04x\n", opt_offset + offsetof (IOH, MinorImageVersion), _f -> _opt_header.MinorImageVersion);
	printf ("    %08x  MajorSubsystemVersion        wd: %04x\n", opt_offset + offsetof (IOH, MajorSubsystemVersion), _f -> _opt_header.MajorSubsystemVersion);
	printf ("    %08x  MinorSubsystemVersion        wd: %04x\n", opt_offset + offsetof (IOH, MinorSubsystemVersion), _f -> _opt_header.MinorSubsystemVersion);
	printf ("    %08x  Win32VersionValue            dw: %08x\n", opt_offset + offsetof (IOH, Win32VersionValue), _f -> _opt_header.Win32VersionValue);
	printf ("    %08x  SizeOfImage                  dw: %08x\n", opt_offset + offsetof (IOH, SizeOfImage), _f -> _opt_header.SizeOfImage);
	printf ("    %08x  SizeOfHeaders                dw: %08x\n", opt_offset + offsetof (IOH, SizeOfHeaders), _f -> _opt_header.SizeOfHeaders);
	printf ("    %08x  CheckSum                     dw: %08x\n", opt_offset + offsetof (IOH, CheckSum), _f -> _opt_header.CheckSum);
	printf ("    %08x  Subsystem                    wd: %04x\n", opt_offset + offsetof (IOH, Subsystem), _f -> _opt_header.Subsystem);
	printf ("    %08x  DllCharacteristics           wd: %04x\n", opt_offset + offsetof (IOH, DllCharacteristics), _f -> _opt_header.DllCharacteristics);
	printf ("    %08x  SizeOfStackReserve           dw: %08x\n", opt_offset + offsetof (IOH, SizeOfStackReserve), _f -> _opt_header.SizeOfStackReserve);
	printf ("    %08x  SizeOfStackCommit            dw: %08x\n", opt_offset + offsetof (IOH, SizeOfStackCommit), _f -> _opt_header.SizeOfStackCommit);
	printf ("    %08x  SizeOfHeapReserve            dw: %08x\n", opt_offset + offsetof (IOH, SizeOfHeapReserve), _f -> _opt_header.SizeOfHeapReserve);
	printf ("    %08x  SizeOfHeapCommit             dw: %08x\n", opt_offset + offsetof (IOH, SizeOfHeapCommit), _f -> _opt_header.SizeOfHeapCommit);
	printf ("    %08x  LoaderFlags                  dw: %08x\n", opt_offset + offsetof (IOH, LoaderFlags), _f -> _opt_header.LoaderFlags);
	printf ("    %08x  NumberOfRvaAndSizes          dw: %08x\n", opt_offset + offsetof (IOH, NumberOfRvaAndSizes), _f -> _opt_header.NumberOfRvaAndSizes);

#	undef IFH   
#	undef IOH
}

/*
   Display PE DOS header,
   each fields offset and value.
*/
void
ez_disp_dos (pfile_entity _f) {
#	define DHD IMAGE_DOS_HEADER
	_f && hh_read_dos_head (_f) || 
		die ("Cannot read dos header."
			 "Unknown error :-("); // the same above.
	println ("DOS header:");

	printf ("%08x  e_magic          wd: %04x (\"MZ\")\r\n", offsetof (DHD, e_magic), _f -> _dos_header -> e_magic);
	printf ("%08x  e_cblp           wd: %04x\n", offsetof (DHD, e_cblp), _f -> _dos_header -> e_cblp);
	printf ("%08x  e_cp             wd: %04x\n", offsetof (DHD, e_cp), _f -> _dos_header -> e_cp);
	printf ("%08x  e_crlc           wd: %04x\n", offsetof (DHD, e_crlc), _f -> _dos_header -> e_crlc);
	printf ("%08x  e_cparhdr        wd: %04x\n", offsetof (DHD, e_cparhdr), _f -> _dos_header -> e_cparhdr);
	printf ("%08x  e_minalloc       wd: %04x\n", offsetof (DHD, e_minalloc), _f -> _dos_header -> e_minalloc);
	printf ("%08x  e_maxalloc       wd: %04x\n", offsetof (DHD, e_maxalloc), _f -> _dos_header -> e_maxalloc);
	printf ("%08x  e_ss             wd: %04x\n", offsetof (DHD, e_ss), _f -> _dos_header -> e_ss);
	printf ("%08x  e_sp             wd: %04x\n", offsetof (DHD, e_sp), _f -> _dos_header -> e_sp);
	printf ("%08x  e_csum           wd: %04x\n", offsetof (DHD, e_csum), _f -> _dos_header -> e_csum);
	printf ("%08x  e_ip             wd: %04x\n", offsetof (DHD, e_ip), _f -> _dos_header -> e_ip);
	printf ("%08x  e_cs             wd: %04x\n", offsetof (DHD, e_cs), _f -> _dos_header -> e_cs);
	printf ("%08x  e_lfarlc         wd: %04x\n", offsetof (DHD, e_lfarlc), _f -> _dos_header -> e_lfarlc);
	printf ("%08x  e_ovno           wd: %04x\n", offsetof (DHD, e_ovno), _f -> _dos_header -> e_ovno);
	printf ("%08x  e_res[0]         wd: %04x\n", offsetof (DHD, e_res [0]), _f -> _dos_header -> e_res [0]);
	printf ("%08x  e_res[1]         wd: %04x\n", offsetof (DHD, e_res [1]), _f -> _dos_header -> e_res [1]);
	printf ("%08x  e_res[2]         wd: %04x\n", offsetof (DHD, e_res [2]), _f -> _dos_header -> e_res[2]);
	printf ("%08x  e_res[3]         wd: %04x\n", offsetof (DHD, e_res [3]), _f -> _dos_header -> e_res[3]);
	printf ("%08x  e_oemid          wd: %04x\n", offsetof (DHD, e_oemid), _f -> _dos_header -> e_oemid);
	printf ("%08x  e_oeminfo        wd: %04x\n", offsetof (DHD, e_oeminfo), _f -> _dos_header -> e_oeminfo);
	printf ("%08x  e_res2[0]        wd: %04x\n", offsetof (DHD, e_res2 [0]), _f -> _dos_header -> e_res2[0]);
	printf ("%08x  e_res2[1]        wd: %04x\n", offsetof (DHD, e_res2 [1]), _f -> _dos_header -> e_res2[1]);
	printf ("%08x  e_res2[2]        wd: %04x\n", offsetof (DHD, e_res2 [2]), _f -> _dos_header -> e_res2[2]);
	printf ("%08x  e_res2[3]        wd: %04x\n", offsetof (DHD, e_res2 [3]), _f -> _dos_header -> e_res2[3]);
	printf ("%08x  e_res2[4]        wd: %04x\n", offsetof (DHD, e_res2 [4]), _f -> _dos_header -> e_res2[4]);
	printf ("%08x  e_res2[5]        wd: %04x\n", offsetof (DHD, e_res2 [5]), _f -> _dos_header -> e_res2[5]);
	printf ("%08x  e_res2[6]        wd: %04x\n", offsetof (DHD, e_res2 [6]), _f -> _dos_header -> e_res2[6]);
	printf ("%08x  e_res2[7]        wd: %04x\n", offsetof (DHD, e_res2 [7]), _f -> _dos_header -> e_res2[7]);
	printf ("%08x  e_res2[8]        wd: %04x\n", offsetof (DHD, e_res2 [8]), _f -> _dos_header -> e_res2[8]);
	printf ("%08x  e_res2[9]        wd: %04x\n", offsetof (DHD, e_res2 [9]), _f -> _dos_header -> e_res2[9]);
	printf ("%08x  e_lfanew         dw: %08x\n", offsetof (DHD, e_lfanew), _f -> _dos_header -> e_lfanew);
#	undef DHD
}

/*
   Only check whether it's a 
   valid PE format file. we just
   check the DOS e_magic and 
   NT Signature. @,o
*/
void
ez_disp_check (pfile_entity _f) {
	int flag = 0;
	if (_f) {
		if (hh_read_dos_head (_f) && 
				hh_read_NT_head (_f)) {
			flag = 
				_f -> _dos_header -> e_magic == IMAGE_DOS_SIGNATURE && 
				_f -> _nt_headers -> Signature == IMAGE_NT_SIGNATURE;
		}
	}

	printf ("We've checked the file is%s PE format.\n", 
			flag ? "" : " not");
}


/*
   Display PE import function table.
*/
void
ez_disp_iat_info (pfile_entity _f) {
	pfile_import imp = NULL;
	int imp_num = 0,
		i = 0;
	_f && hh_read_dos_head (_f) &&
		hh_read_NT_head (_f) &&
		hh_read_segment_header (_f) ||
		die ("Cannot read file data."
			 "Unknown error.");
	// pfile_import read_import_tables (pfile_entity _f);
	if (! (imp = 
			ez_read_import_tables (_f, &imp_num)))
		die ("Cannot read import tables."
			 "Unknown error.");
	printf ("Import tables, total %d libs:\n",
			imp_num);
	for (; i <= imp_num; ++ i) {
		int f_idx = 0;
		pfile_import lib = &(imp [i]);
		printf ("%d. %s\n",
				i + 1, 
				lib -> _name);
		for (; f_idx < lib -> _total_funcs; 
				++ f_idx)
		{
			pthunk func = lib -> _funcs + f_idx;
			printf ("  %d. 0x%08x 0x%04x  %s\n",
					f_idx + 1, // NO
					func -> _func_addr, // function address
					func -> _number._hint, // hint
					func -> _func_name);
		}
	}
}

/*
   Display PE architecture.
   Offset and RVA range for 
   each header ,each segment.
*/
void
ez_disp_arch (pfile_entity _f) {
	// int tmp = 0; 
	uint32_t nt_offset = 0,
			 opt_size = 0,
			 seg_head_offset = 0;
	int i = 0;
	if (hh_read_dos_head (_f) &&
		hh_read_NT_head (_f) &&
		hh_read_segment_header (_f)) 
	{
		// dos header
		println ("DOS: 0x00 ~ 0x40 (offset)\n");

		nt_offset = (uint32_t) _f -> _dos_header ->
			e_lfanew;
		opt_size = (uint32_t) _f -> _nt_headers -> 
			FileHeader.SizeOfOptionalHeader;
		seg_head_offset = opt_size + 4 + 
			sizeof (IMAGE_FILE_HEADER);

		// nt header
		printf ("NT: 0x%04x ~ 0x%04x (offset)\n", 
				nt_offset,
				seg_head_offset - 1);

		// section headers
		printf ("Section header: 0x%04x ~ 0x%04x (offset)\n",
				seg_head_offset,

				seg_head_offset + 
				sizeof (IMAGE_SECTION_HEADER) * 
				(_f -> _file_header.NumberOfSections)
		);

		// printf ("Sections\n"
		// 	"------------------------------\n");
		// sections 
		for (; i < _f -> _nt_headers -> 
			FileHeader.NumberOfSections; ++ i)
		{
			printf ("%s: 0x%08x ~ 0x%08x (offset)," 
					"0x%08x ~ 0x%08x (RVA)\n",
					_f -> _sec_header [i].Name, // name

					_f -> _sec_header [i].PointerToRawData, // file offset start

					_f -> _sec_header [i].PointerToRawData + 
					_f -> _sec_header [i].SizeOfRawData - 1, // file offset end

					_f -> _sec_header [i].VirtualAddress, // RVA start

					_f -> _sec_header [i].Misc.VirtualSize +
					_f -> _sec_header [i].VirtualAddress - 1 // RVA end
			);
		}

	}
}


/*
   You know ! ;)
*/
void
ez_disp_help () {
	printf ("PE file parser %s\n"
			"%s\n"
			"author : \n",
			version,
			help_str
		   );
	printf ("  %s %s\n", author1, email1);
	printf ("  %s %s\n", author2, email2 );
}


