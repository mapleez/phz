#ifndef _FENGINE_H_
#  define _FENGINE_H_
#include ez_file_entity.h
void init(char *filename);
int read_dos_head(pfile_entity dosHeader);
int read_NT_head(pfile_entity ntHeader);
int read_segment_header(pfile_entity segHeader);
int desponse(pfile_entity free);
#endif //~ _FENGINE_H_
