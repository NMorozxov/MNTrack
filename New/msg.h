#ifndef NETMAIL_MSG_H
#define NETMAIL_MSG_H
#include <time.h>
#include "mntcfg.h"
#include "addr.h"
#include "fido_typ.h"
#include "log.h"
FILE *NewMsg(char *pat,char *newfile);
/*
 Input:
  pat  - PATH to FIDO *msg message base
 Output:
  newfile - Buffer to store new file name
 Returns:
  message file
*/
void MakeMsgHeader(char *from,Adr4D fad,char *to,Adr4D tad,char *subj,char *dmn,FILE *f);
#endif
