#ifndef _FENGINE_H_
#  define _FENGINE_H_
#include ez_file_entity.h
void init(char *filename);
int read_dos_head();
int read_NT_head();
int read_segment_header();
int desponse();
#endif //~ _FENGINE_H_
