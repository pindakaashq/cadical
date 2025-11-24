#ifndef _UNISTD_H
#define _UNISTD_H    1

#include <io.h>
#include <intrin.h>
#include <process.h>

#define R_OK    4
#define W_OK    2

#define pclose _pclose
#define popen _popen
#define access _access
#define isatty _isatty

#define __PRETTY_FUNCTION__ __FUNCTION__
#define __builtin_prefetch(A,B,C) _m_prefetch((void*)(A))
#define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#define S_ISFIFO(mode)  (((mode) & _S_IFMT) == _S_IFIFO)

#endif /* unistd.h  */
