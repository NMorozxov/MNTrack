#ifndef BINK_H
#define BINK_H
#include "log.h"
#include "trackmod.h"
void GetOutbound(const Adr4D adr,char * domain,char * name);
void GetBinkName(Adr4D adr,char * domain,char * binkname);
BOOL_1 BusySystemCheck(Adr4D adr,char * domain);
void BusySystemSet(Adr4D adr,char * domain);
void BusySystemUnSet(Adr4D adr,char * domain);
#endif

