#ifndef JAM_H
#define JAM_H

#include <time.h>
#include "log.h"
#include "trackmod.h"

#define JAM_MSG_LOCAL       0x00000001L    /* Msg created locally */
#define JAM_MSG_INTRANSIT   0x00000002L    /* Msg is in-transit */
#define JAM_MSG_PRIVATE     0x00000004L    /* Private */
#define JAM_MSG_READ        0x00000008L    /* Read by addressee */
#define JAM_MSG_SENT        0x00000010L    /* Sent to remote */
#define JAM_MSG_KILLSENT    0x00000020L    /* Kill when sent */
#define JAM_MSG_ARCHIVESENT 0x00000040L    /* Archive when sent */
#define JAM_MSG_HOLD        0x00000080L    /* Hold for pick-up */
#define JAM_MSG_CRASH       0x00000100L    /* Crash */
#define JAM_MSG_IMMEDIATE   0x00000200L    /* Send Msg now, ignore restrictions */
#define JAM_MSG_DIRECT      0x00000400L    /* Send directly to destination */
#define JAM_MSG_GATE        0x00000800L    /* Send via gateway */
#define JAM_MSG_FILEREQUEST 0x00001000L    /* File request */
#define JAM_MSG_FILEATTACH  0x00002000L    /* File(s) attached to Msg */
#define JAM_MSG_TRUNCFILE   0x00004000L    /* Truncate file(s) when sent */
#define JAM_MSG_KILLFILE    0x00008000L    /* Delete file(s) when sent */
#define JAM_MSG_RECEIPTREQ  0x00010000L    /* Return receipt requested */
#define JAM_MSG_CONFIRMREQ  0x00020000L    /* Confirmation receipt requested */
#define JAM_MSG_ORPHAN      0x00040000L    /* Unknown destination */
#define JAM_MSG_ENCRYPT     0x00080000L    /* Msg text is encrypted */
#define JAM_MSG_COMPRESS    0x00100000L    /* Msg text is compressed */
#define JAM_MSG_ESCAPED     0x00200000L    /* Msg text is seven bit ASCII */
#define JAM_MSG_FPU         0x00400000L    /* Force pickup */
#define JAM_MSG_TYPELOCAL   0x00800000L    /* Msg is for local use only (not for export) */
#define JAM_MSG_TYPEECHO    0x01000000L    /* Msg is for conference distribution */
#define JAM_MSG_TYPENET     0x02000000L    /* Msg is direct network mail */
#define JAM_MSG_NODISP      0x20000000L    /* Msg may not be displayed to user */
#define JAM_MSG_LOCKED      0x40000000L    /* Msg is locked, no editing possible */
#define JAM_MSG_DELETED     0x80000000L    /* Msg is deleted */

#define JAMSFLD_OADDRESS    0
#define JAMSFLD_DADDRESS    1
#define JAMSFLD_SENDERNAME  2
#define JAMSFLD_RECVRNAME   3
#define JAMSFLD_MSGID       4
#define JAMSFLD_REPLYID     5
#define JAMSFLD_SUBJECT     6
#define JAMSFLD_PID         7
#define JAMSFLD_TRACE       8
#define JAMSFLD_ENCLFILE    9
#define JAMSFLD_ENCLFWALIAS 10
#define JAMSFLD_ENCLFREQ    11
#define JAMSFLD_ENCLFILEWC  12
#define JAMSFLD_ENCLINDFILE 13
#define JAMSFLD_EMBINDAT    1000
#define JAMSFLD_FTSKLUDGE   2000
#define JAMSFLD_SEENBY2D    2001
#define JAMSFLD_PATH2D      2002
#define JAMSFLD_FLAGS       2003
#define JAMSFLD_TZUTCINFO   2004
#define JAMSFLD_UNKNOWN     0xffff

typedef struct _JAMHeader {
               char Signature[4];
               UINT_4 DateCreated;
               UINT_4 ModCounter;
               UINT_4 ActiveMsgs;
               UINT_4 PasswordCrc;
               UINT_4 BaseMsgNum;
               unsigned char Reserved[1000];
               } JAMHeader;
typedef struct _JAMMsgHeader {
               char   Signature[4];               /* <J><A><M> followed by <NUL> */
               UINT_2  Revision;                  /* CURRENTREVLEV */
               UINT_2  ReservedWord;              /* Reserved */
               UINT_4  SubfieldLen;               /* Length of subfields */
               UINT_4  TimesRead;                 /* Number of times message read */
               UINT_4  MsgIdCRC;                  /* CRC-32 of MSGID line */
               UINT_4  ReplyCRC;                  /* CRC-32 of REPLY line */
               UINT_4  ReplyTo;                   /* This msg is a reply to.. */
               UINT_4  Reply1st;                  /* First reply to this msg */
               UINT_4  ReplyNext;                 /* Next msg in reply chain */
               UINT_4  DateWritten;               /* When msg was written */
               UINT_4  DateReceived;              /* When msg was received/read */
               UINT_4  DateProcessed;             /* When msg was processed by packer */
               UINT_4  MsgNum;                    /* Message number (1-based) */
               UINT_4  Attribute;                 /* Msg attribute, see "Status bits" */
               UINT_4  Attribute2;                /* Reserved for future use */
               UINT_4  TxtOffset;                 /* Offset of text in text file */
               UINT_4  TxtLen;                    /* Length of message text */
               UINT_4  PasswordCRC;               /* CRC-32 of password to access msg */
               UINT_4  Cost;                      /* Cost of message */
               } JAMMsgHeader;
typedef struct _JAMTM     {
               int     tm_sec,                    /* Seconds 0..59                     */
                       tm_min,                    /* Minutes 0..59                     */
                       tm_hour,                   /* Hour of day 0..23                 */
                       tm_mday,                   /* Day of month 1..31                */
                       tm_mon,                    /* Month 0..11                       */
                       tm_year,                   /* Years since 1900                  */
                       tm_wday,                   /* Day of week 0..6 (Sun..Sat)       */
                       tm_yday,                   /* Day of year 0..365                */
                       tm_isdst;                  /* Daylight savings time (not used)  */
               } JAMTM;
/* Prototypes */
FILE *OpenJAMBase(char *Base,JAMHeader *jhr);
/*
Input:
 Base - JAM Base
Output:
 jhr  - JAM Header
Return:
 FILE with JAM Header
*/
void CloseJAMBase(FILE *f,JAMHeader *jhr);
void PostMessageToJAMBase(char *Base,FILE *fhdr,JAMHeader *jhr,char *text,size_t textlen,char *fad,char *fn,char *tn,char *subj);
#endif
