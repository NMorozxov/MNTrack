#ifndef MNTRACK_LOG_H
#define MNTRACK_LOG_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef UNIX
//#include "brtime.h"
#else /* UNIX */
#include <dos.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif
#include "mntcfg.h"
#include "cport.h"
#include "mnlib.h"
#include "mntrq.h"
void write_log(char type,char *message);
#endif
