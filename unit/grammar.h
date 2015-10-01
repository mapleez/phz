#ifndef _GRAMMAR_H_
#	define _GRAMMER_H_

struct opt {
	char* arc;
	int x;
	int y;
	int z;
};


const
struct opt myopt [] = {
	{"c lang", 0, 1, 2},
	{"cpp lang", 0, 1, 3},
	{"java lang", 0, 3, 2},
	{"perl lang", 3, 2, 9},
};

#endif // ~ _GRAMMER_H_
