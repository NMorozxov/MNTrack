#ifndef PORT_TYP_H
#define PORT_TYP_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* DOS */
#ifdef __MSDOS__
#define BOOL_1 char
#ifndef __DOS32__
#define UINT_2 unsigned int
#define UINT_4 unsigned long
#else 
/* DOS 32 bit */
#define UINT_2 unsigned short
#define UINT_4 unsigned long
#define farcalloc calloc
#define farfree free
#define far
#endif
#endif
/* OS/2 */
#ifdef __OS2__
#define BOOL_1 char
#define UINT_2 unsigned short
#define UINT_4 unsigned long
#define farcalloc calloc
#define farfree free
#define far
#endif
/* Windows NT */
#ifdef __WIN32__
#define BOOL_1 unsigned char
#define UINT_2 unsigned short
#define UINT_4 unsigned long
#define farcalloc(a,b) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,a*b)
#define farfree(a) HeapFree(GetProcessHeap(),0,a)
#define far
#endif
/* UNIX */
#ifdef UNIX
#define BOOL_1 unsigned char
#define UINT_2 unsigned short
#define UINT_4 unsigned long
#define farcalloc calloc
#define farfree free
#define far
#define _timezone (-tmm->tm_gmtoff)
#define _daylight tmm->tm_isdst
#ifndef HAVE_STRICMP
#ifdef HAVE_STRCASECMP
#define stricmp strcasecmp
#endif
#endif
#endif
#endif
