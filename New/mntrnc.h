#ifndef UNIX
#include <dos.h>
#endif /* UNIX */

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef UNIX
#include <dosfind.h>
#endif

#include <mnlib.h>
#include "mn_types.h"
#include "cport.h"
#include "mntrq.h"
/* Command line Arguments */
#define ARG_HELP 1
#define ARG_NUM  2
/* Nodelist Tokens */
#define NDL_ZONE 1
#define NDL_REGION 2
#define NDL_HOST 3
#define NDL_HUB 4
#define NDL_PVT 5
#define NDL_DOWN 6
#define NDL_HOLD 7
/* CTL Tokens */
#define CTL_NODELIST 1
#define CTL_NODELISTMASK 2
#define CTL_NODELISTMASKNUMERIC 3
#define CTL_NODELISTSEGMENT 4
#define CTL_ADDRESS 5

