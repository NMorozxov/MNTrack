#ifndef FIDO_TYP_H
#define FIDO_TYP_H
#include "port_typ.h"
/* Max Len of Message line */
#define FIDOMsgMaxStringLen 4096
/* .MSG Header */
typedef struct _HeaderType {
               char FromUserName[36];
               char ToUserName[36];
               char Subject[72];
               char DateTime[20];
               UINT_2 TimesRead;
               UINT_2 DestNode;
               UINT_2 OrigNode;
               UINT_2 Cost;
               UINT_2 OrigNet;
               UINT_2 DestNet;
               UINT_2 DestZone;
               UINT_2 OrigZone;
               UINT_2 DestPoint;
               UINT_2 OrigPoint;
               UINT_2 ReplyTo;
               UINT_2 Flags;
               UINT_2 NextReply;
               } HeaderType;
/* PKT Header */
typedef struct _TPKTFileHeader {
               UINT_2 OrigNode;
               UINT_2 DestNode;
               UINT_2 Year;
               UINT_2 Month;
               UINT_2 Day;
               UINT_2 Hour;
               UINT_2 Min;
               UINT_2 Sec;
               UINT_2 Baud;
               UINT_2 PktVer;
               UINT_2 OrigNet;
               UINT_2 DestNet;
               char ProdCodeLo;
               char SerialNoHi;
               char Password[8];
               UINT_2 QOrigZone;
               UINT_2 QDestZone;
               UINT_2 AuxNet;
               UINT_2 CWValCopy;
               char ProdCodeHi;
               char SerialNoLo;
               UINT_2 CapWord;
               UINT_2 OrigZone;
               UINT_2 DestZone;
               UINT_2 OrigPoint;
               UINT_2 DestPoint;
               UINT_4 Product;
               } TPKTFileHeader;
/* Message in PKT Header */               
typedef struct _TPKTFileMSGHeader{
               UINT_2 Version;
               UINT_2 OrigNode;
               UINT_2 DestNode;
               UINT_2 OrigNet;
               UINT_2 DestNet;
               UINT_2 Attr;
               UINT_2 Cost;
               } TPKTFileMSGHeader;
#endif
