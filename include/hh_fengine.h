#ifndef _HH_FENGINE_H_
#  define _HH_FENGINE_H_

#include "ez_file_entity.h"
#ifdef _MSC_VER
#include "windows.h"
#else
#error "This program cannot compile under this platform :("
#endif // ~ _MSC_VER_

/*
   Initialization for the file engine;
   @1 = file name string

   We will return the file entity printer
   for the function calling below;

   Note: It's important to call it before
   all the read_*_header subroutine;
*/
extern
pfile_entity hh_init (char *);

/*
   Read PE DOS header into ptr @1.
   the @1 argument must be the return 
   value of hh_init (); function will
   malloc the _dos_header field and fill
   PE DOS header data to it.
   
   Return read length.
*/
extern
int hh_read_dos_head (pfile_entity);

/*
   Read PE NT header into ptr @1.
   the @1 argument must be the return 
   value of hh_init (); function will
   malloc the _nt_headers fields and 
   fill PE NT header data to it.
   
   Return read length.
*/
extern
int hh_read_NT_head (pfile_entity);

/*
   Read PE Segment headers into ptr @1.
   the @1 argument must be the return 
   value of hh_init (); function will
   malloc the _sec_header field and 
   fill PE Section header array to it.
   
   Return read length.
*/
extern
int hh_read_segment_header (pfile_entity);

/*
   Despite the argument, the file engine;
   If @1 ptr is NULL, nothing will be done 
   for it, Else its members will be disposed.
*/
extern
void hh_desponse (pfile_entity);

/*
   Dump export table content and return it;
   if successful, return the ptr of file_export,
   else return NULL;

   The @1 argument must be the return value of
   function hh_init ();
   
   relevant read_*_header functions to fill it.
*/
extern
pfile_export hh_PrintExportTable (pfile_entity);

/*
   exchange from RVA to RAW;
   return the RAW address of file offset space if successful,
   else return false;
*/
extern
DWORD hh_RVAToRAW (DWORD);

// ez
extern
pfile_import ez_read_import_tables (pfile_entity, int*);

#endif //~ _FENGINE_H_

