/* DOS */
#ifdef __MSDOS__
#ifndef __DOS32__
char version[]="3.10/DOS";
#endif
#endif
/* DOS Protected */
#ifdef __DOS32__
char version[]="3.10/386";
#endif
/* OS/2 */
#ifdef __OS2__
char version[]="3.10/OS2";
#endif
#ifdef __WIN32__
char version[]="3.10/Win32";
#endif
#ifdef UNIX
#include "unix_version.h"
#endif
