#ifndef TRACK_MOD_H
#define TRACK_MOD_H
#include <stdio.h>
#include <stdlib.h>
#ifdef UNIX
#include <dosfind.h>
#else /* UNIX */
#ifdef __WIN32__
#include <windows.h>
#else
#include <dos.h>
#endif /* __WIN32__ */
#endif /* UNIX */
#include "cport.h"
#include <mnlib.h>
#include "mn_types.h"

#ifdef __cplusplus
extern "C" {
#endif
BOOL_1 FileExist(char *name);
void adr2txt(Adr4D addr,char *txt);
void txt2adr(char *txt,Adr4D *addr);
void getdomain(char *adr,char *domain);
#ifndef __WIN32__
void ZeroMemory(void *Destination,int Length);
#endif
#ifdef __cplusplus
};
#endif
#endif
