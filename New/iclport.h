#if !defined(_MNTRACK_MSVC_PORT_H) && defined (_MSC_VER)
#define _MNTRACK_MSVC_PORT_H

#include <io.h>

#define ATTRIB _A_RDONLY|_A_HIDDEN|_A_SYSTEM|_A_ARCH

#define fnsplit _splitpath
#define ffblk _finddata_t
#define findfirst(a,b,c) _findfirst(a,b)
#define findnext(a) _findnext(findresult,a);
#define ff_name name

#endif
