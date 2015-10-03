#ifndef _HH_FENGINE_H_
#  define _HH_FENGINE_H_
#include "ez_file_entity.h"
#include "windows.h"
void hh_init(char *filename);
int hh_read_dos_head(pfile_entity dosHeader);
int hh_read_NT_head(pfile_entity ntHeader);
int hh_read_segment_header(pfile_entity segHeader);
void hh_desponse(pfile_entity free);
pfile_export hh_PrintExportTable(pfile_entity nt);
DWORD hh_RVAToRAW(DWORD virtualAddress);
#endif //~ _FENGINE_H_
