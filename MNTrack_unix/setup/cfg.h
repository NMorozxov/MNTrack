#ifndef _MNTRACK_TV_SETUP_CFG_H
#define _MNTRACK_TV_SETUP_CFG_H

#define Uses_MsgBox
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tv.h>

#ifdef UNIX

#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_ALLOC_H
#include <alloc.h>
#endif

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#else /* UNIX */

#include <ctype.h>
#include <conio.h>
#ifdef  __WATCOMC__
#include <malloc.h>
#include <io.h>
#else
#include <alloc.h>
#endif

#endif /* UNIX */

#include <mn_types.h>
#include <mntcfg.h>
#include <trackmod.h>
void LoadConfig(void);
void SaveConfig(void);
#endif
