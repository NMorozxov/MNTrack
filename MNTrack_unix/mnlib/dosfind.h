#ifndef DOS_FINDFIRST_FINDNEXT_H
#define DOS_FINDFIRST_FINDNEXT_H

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

#ifdef HAVE_DIR_H
#include <dir.h>
#endif

#ifdef HAVE_REGEX_H
#include <regex.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifndef HAVE_SCANDIR
#include "scandir.h"
#endif

struct  ffblk   {
    long            ff_curfile;
    long            ff_maxfile;
    struct dirent   **ff_namelist;
    char            ff_mask[255];
/*    
    long            ff_fsize;
    unsigned long   ff_attrib;
    unsigned short  ff_ftime;
    unsigned short  ff_fdate;
*/    
    char            ff_name[256];
};

int fnsplit(const char *__path, char *__drive, char *__dir, char *__name, char *__ext );
int findfirst( const char *__path,struct ffblk *__ffblk,int __attrib );
int findnext( struct ffblk *__ffblk );
#endif
