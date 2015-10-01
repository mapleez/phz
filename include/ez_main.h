#ifndef _EZ_MAIN_H_
#	define _EZ_MAIN_H_

/*
 * author : ez
 * date : 2015/9/30
 * describe : defined all the global 
 *     varibles, handle arguments.
*/

#include "ez_file_engine.h"
#include "ez_file_entity.h"
#include "ez_prog_args.h"
#include <getopt.h>
#include "version.h"

#	define printlnf(___F, ___S) \
		printf (___F, ___S)

#	define println(___S) \
		printf ("%s\n", ___S)

/*
   getopt string
*/
const* char* ez_arg_string = "aCeis";

/*
   File Handle Engine to access input
   PE file data.
*/
// extern pfile_engine fhandle;

/*
   Stored the hole data read from 
   file stream. Formatted data.
*/
extern pfile_entity fentity;

/*
   Stored the analysis result of input
   options.
*/
extern pprog_args pargs;

/*
   All the function options this version
   provided.
*/
const 
struct option ez_longopts [] = {
	/* 
	   Print EAT structure, each fields and
	   all export functions.
	*/
	{"export", no_argument, NULL, 'e'},

	/*
	   Print IAT structure, each fields and
	   all import funcitons from each modules
	*/
	{"import", no_argument, NULL, 'i'},

	/*
	   If this options is provided, only check
	   if the input PE file is valid. simple :-)
	*/
	{"check", no_argument, NULL, 'C'},

	/*
	   Print the file architecture of each
	   segment, each header.
	*/
	{"architecture", no_argument, NULL, 'a'},

	/*
	   This flag only do like option 'check',
	   and print other basic file information.
	   e.g. file name @_x
	*/
	{"simple_info", no_argument, NULL, 's'}
};

#endif // ~ _EZ_MAIN_H_
