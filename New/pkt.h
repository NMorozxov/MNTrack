#ifndef FIDO_PACKET_H
#define FIDO_PACKET_H
#include "msg.h"
#include "log.h"
void MakePKTHeader(Adr4D fad,Adr4D tad,char *pass,FILE *f);
void MakePKTMsgHeader(FILE *f);
void MakePKTMsgHeaderFromTo(char *fn,Adr4D fa,char *tn,Adr4D ta,char *subj,char *area,FILE *f);
#endif
