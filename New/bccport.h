#if !defined(_MNTRACK_BORLAND_PORT_H) && defined (__BORLANDC__)
#define _MNTRACK_BORLAND_PORT_H

#include <dir.h>

#ifndef __WIN32__
#include <alloc.h>
#endif

#ifdef __MSDOS__
#define _timezone timezone
#define _daylight daylight
#endif

#define ATTRIB FA_ARCH|FA_RDONLY|FA_HIDDEN|FA_SYSTEM

#endif

