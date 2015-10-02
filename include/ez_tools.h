#ifndef _EZ_TOOLS_H_
#	define _EZ_TOOLS_H_

// #	define printlnf(___F, ___S) \
//		printf (___F, ___S)

#	define println(___S) \
		printf ("%s\n", ___S)

#	define die(___S) ({	\
		println (___S);	\
		exit (0); \
	})

#endif // ~ _EZ_TOOLS_H_
