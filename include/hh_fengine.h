#ifndef _HH_FENGINE_H_
#  define _HH_FENGINE_H_
#include "ez_file_entity.h"
#include "windows.h"
void init(char *filename);
int read_dos_head(pfile_entity dosHeader);
int read_NT_head(pfile_entity ntHeader);
int read_segment_header(pfile_entity segHeader);
int desponse(pfile_entity free);
pfile_export PrintExportTable(pfile_entity nt);
DWORD RVAToRAW(DWORD virtualAddress);
#endif //~ _FENGINE_H_
