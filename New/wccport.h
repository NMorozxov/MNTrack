#if !defined(_MNTRACK_WATCOMC_PORT_H) && defined (__WATCOMC__)
#define _MNTRACK_WATCOMC_PORT_H

#include <direct.h>
#include <malloc.h>
#include <errno.h>
#include <io.h>
#include "d2afind.h"

#define ATTRIB _A_RDONLY|_A_HIDDEN|_A_SYSTEM|_A_ARCH

#define fnsplit _splitpath

#if defined(__MSDOS__)  && !defined (__DOS32__)
#define farcalloc _fcalloc
#define farfree _ffree
#endif

#define _timezone (-timezone)
#define _daylight daylight
#endif
