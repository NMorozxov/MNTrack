#ifndef TRACK_MOD_H
#define TRACK_MOD_H
#ifdef __WIN32__
#include <windows.h>
#else
#include <dos.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "cport.h"
#include "stringop.h"
#include "mn_types.h"
BOOL_1 FileExist(char *name);
void adr2txt(Adr4D addr,char *txt);
void txt2adr(char *txt,Adr4D *addr);
void getdomain(char *adr,char *domain);
#endif