#ifndef _SCANDIR_H
#define _SCANDIR_H

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

#ifdef HAVE_DIR_H
#include <dir.h>
#endif
/*
extern int scandir (__const char *__dir,
		    struct dirent ***__namelist,
		    __dir_select_fn_t __dir_select_fn,
		    __dir_compar_fn_t __dir_compar_fn);

extern int alphasort (
		__const struct dirent * __const *,
		__const struct dirent * __const *
		);
*/
#endif