#ifndef MN_TYP_H
#define MN_TYP_H
#include "port_typ.h"
#ifndef UNIX
#pragma pack(1)
#endif
typedef struct _Adr4D {
               UINT_2 zone;
               UINT_2 net;
               UINT_2 node;
               UINT_2 point;
#ifdef UNIX
               } __attribute__ ((packed)) Adr4D;
#else
               } Adr4D;
#endif
typedef struct _NdxRec {
#ifdef __MSDOS__
               struct _NdxRec far *next;
#else
               struct _NdxRec *next;
#endif
               Adr4D address;
#ifdef UNIX
               } __attribute__ ((packed)) NdxRec;
#else
               } NdxRec;
#endif
typedef struct _DomenType {
               char name[255];
               char out[255];
               BOOL_1 Default;
               BOOL_1 HaveMainZone;
               UINT_2 MainZone;
               char zones[255];
#ifdef UNIX
               } __attribute__ ((packed)) DomenType;
#else
               } DomenType;
#endif
typedef struct _DmnRec {
#ifdef __MSDOS__
               struct _DmnRec far *next;
#else
               struct _DmnRec *next;
#endif
               DomenType dmn;
#ifdef UNIX
               } __attribute__ ((packed)) DmnRec;
#else
               } DmnRec;
#endif
typedef struct _ScriptType {
               char name[255];
#ifdef UNIX
               } __attribute__ ((packed)) ScriptType;
#else
               } ScriptType;
#endif
typedef struct _ScriptRec {
#ifdef __MSDOS__
               void far *next;
#else
               void *next;
#endif
               ScriptType scr;
#ifdef UNIX
               } __attribute__ ((packed)) ScriptRec;
#else
               } ScriptRec;
#endif

typedef struct _AKAType {
               char zone[255];
               char net[255];
               char addr[255];
               void *next;
#ifdef UNIX
               } __attribute__ ((packed)) AKAType;
#else
               } AKAType;
#endif
#ifndef UNIX
#pragma pack()
#endif
#endif
