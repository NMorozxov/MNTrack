#ifndef _DOS_TO_ANSI_FIND_FUNCTIONS
#define _DOS_TO_ANSI_FIND_FUNCTIONS

#include <dos.h>
#include "cport.h"

#define ffblk find_t
#define ff_name name

int findfirst(const char *pathname,struct ffblk *ffblk, int attrib);
int findnext(struct ffblk *ffblk);

#endif

