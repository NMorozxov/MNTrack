#ifndef ADDR_H
#define ADDR_H
#include "trackmod.h"
#ifdef __MSDOS__
extern NdxRec far *FNdx;
extern NdxRec far *TNdx;
extern NdxRec far *PNdx;
BOOL_1 CheckAddress(const Adr4D adr);
#else
extern NdxRec *FNdx;
extern NdxRec *TNdx;
extern NdxRec *PNdx;
BOOL_1 CheckAddress(const Adr4D adr);
#endif
#endif
