/*
 *
 * stdbool.h
 */
 
#ifndef _STDBOOL_H
#define _STDBOOL_H
 
#ifndef __cplusplus
 
#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
# if !defined(__GNUC__) ||(__GNUC__ < 3)
  typedef char _Bool;/* For C compilers without _Bool */
# endif // __GNUC__
#endif // ~ __STDC_VERSION__
 
#define bool  _Bool
#define true  1
#define false 0
 
#else // __cplusplus
 
/* C++ */
#define bool  bool
#define true  true
#define false false
 
#endif // __cplusplus
 
#define __bool_true_false_are_defined 1
 
#endif /* _STDBOOL_H */
