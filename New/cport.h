#ifndef C_PORT_H
#define C_PORT_H

#include "wccport.h"
#include "bccport.h"
#include "iclport.h"

#ifdef UNIX
#define ATTRIB 0
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

#ifdef HAVE_DIR_H
#include <dir.h>
#endif

#ifdef HAVE_ALLOC_H
#include <alloc.h>
#endif

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#endif

