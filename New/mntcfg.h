#ifndef MNTRACK_CONFIGURATION_H
#define MNTRACK_CONFIGURATION_H
#define MNTRACK_CONFIGURATION_VERSION 1
#include "mn_types.h"
#ifndef UNIX
#pragma pack(1)
#endif
typedef struct _ConfigType {
               UINT_4 version;
               char scanfiles[255];
               char logfile[255];
               char bouadr[255];
               char utc[255];
               char out[255];
               BOOL_1 ksanswer;
               BOOL_1 insintl;
               char sysopname[255];
               UINT_2 uuedepth;
               BOOL_1 updatelastread;
               char flags[255];
               UINT_2 stop;
               UINT_2 loglevel;
               char pktout[255];
               UINT_2 clearbefore;
               UINT_2 setafter;
#ifdef UNIX
               } __attribute__ ((packed)) ConfigType;
#else
               } ConfigType;
#endif
#ifndef UNIX
#pragma pack()
#endif
void LoadConfig(void);
#endif
