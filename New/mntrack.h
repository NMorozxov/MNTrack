#ifndef MNTRACK_H
#define MNTRACK_H
#include <stdlib.h>
#ifndef UNIX
#include <process.h>
#endif
#include <ctype.h>
#include "addr.h"
#include "mnlib.h"
#include "cport.h"
#include "log.h"
#include "bink.h"
#include "pkt.h"
#include "upkt.h"
#include "mntcfg.h"
#include "jam.h"
/* Command Line Arguments */
#define ARG_HELP 1
#define ARG_QUIET 2
#define ARG_SCAN 3
#define ARG_SCR 4
#define ARG_UNPKT 5
/* Script Tokens */
#define SCR_OUTLOG 1
#define SCR_LOGSTART 2
#define SCR_LOGEND 3
#define SCR_LOGDROP 4
#define SCR_BREAK 5
#define SCR_NOBREAK 6
#define SCR_NOCASE 7
#define SCR_REALCASE 8
#define SCR_QUIT 9
#define SCR_GOTO 10
#define SCR_JE 11
#define SCR_JNE 12
#define SCR_SUBJ 13
#define SCR_INSUBJ 14
#define SCR_TONAME 15
#define SCR_FROMNAME 16
#define SCR_FROMADR 17
#define SCR_FROMADR3D 18
#define SCR_TOADR 19
#define SCR_TOADR3D 20
#define SCR_TOZONE 21
#define SCR_TONET 22
#define SCR_TONODE 23
#define SCR_TOPOINT 24
#define SCR_FROMZONE 25
#define SCR_FROMNET 26
#define SCR_FROMNODE 27
#define SCR_FROMPOINT 28
#define SCR_LOOP 29
#define SCR_DUPE 30
#define SCR_INTL 31
#define SCR_MSGID 32
#define SCR_TOLISTED 33
#define SCR_FROMLISTED 34
#define SCR_EMPTY 35
#define SCR_INBODY 36
#define SCR_MSGSIZE 37
#define SCR_UUE 38
#define SCN_PVT 39
#define SCN_CRA 40
#define SCN_RCV 41
#define SCN_SNT 42
#define SCN_ATT 43
#define SCN_TRS 44
#define SCN_ORP 45
#define SCN_KS 46
#define SCN_LOC 47
#define SCN_HLD 48
#define SCN_FRQ 49
#define SCN_RRQ 50
#define SCN_RRC 51
#define SCN_ARQ 52
#define SCN_URQ 53
#define SCN_ZON 54
#define SCN_DIR 55
#define SCN_LOK 56
#define SCN_KFS 57
#define SCN_CFM 58
#define SCN_XMA 59
#define SCN_IMM 60
#define SCN_TFS 61
#define SCN_AS 62
#define SCN_HUB 63
#define SCN_MOVE 64
#define SCN_COPY 65
#define SCN_SEMAPHORE 66
#define SCN_DELETE 67
#define SCN_DELETEATTACH 68
#define SCN_WRITETOJAMECHO 69
#define SCN_APPENDTOFILE 70
#define SCN_BOUNCE 71
#define SCN_FORWARD 72
#define SCN_MAKEMSG 73
#define SCN_SETPVT 74
#define SCN_CLEARPVT 75
#define SCN_SETCRA 76
#define SCN_CLEARCRA 77
#define SCN_SETRCV 78
#define SCN_CLEARRCV 79
#define SCN_SETSNT 80
#define SCN_CLEARSNT 81
#define SCN_SETATT 82
#define SCN_CLEARATT 83
#define SCN_SETTRS 84
#define SCN_CLEARTRS 85
#define SCN_SETORP 86
#define SCN_CLEARORP 87
#define SCN_SETKS 88
#define SCN_CLEARKS 89
#define SCN_SETLOC 90
#define SCN_CLEARLOC 91
#define SCN_SETHLD 92
#define SCN_CLEARHLD 93
#define SCN_SETFRQ 94
#define SCN_CLEARFRQ 95
#define SCN_SETRRQ 96
#define SCN_CLEARRRQ 97
#define SCN_SETRCC 98
#define SCN_CLEARRRC 99
#define SCN_SETARQ 100
#define SCN_CLEARARQ 101
#define SCN_SETURQ 102
#define SCN_CLEARURQ 103
#define SCN_BUSYCHECK 104
#define SCN_BUSYSET 105
#define SCN_BUSYUNSET 106
#define SCN_BUSYSYSTEMFLAGS 107
#define SCN_NOBUSYSYSTEMFLAGS 108
#define SCN_PACK 109
#define SCN_PACKPKT 110
#define SCN_ATTACH 111
#define SCN_FREQ 112
#define SCN_SETSUBJ 113
#define SCN_SETFROMNAME 114
#define SCN_SETTONAME 115
#define SCN_MAKEPKT 116
#define SCN_VIA 117
#define SCN_INFROMNAME 118
#define SCN_INTONAME 119
#define SCN_EXEC 120
#define SCN_WRITETOFILE 121
#define SCN_EXISTATTACH 122
#define SCN_SECOND 123
#define SCN_MINUTE 124
#define SCN_HOUR 125
#define SCN_STRIPPATH 126
#define SCN_SETFROMZONE 127
#define SCN_SETTOZONE 128
#define SCN_EXISTFILE 129
/* Kludges */
#define K_INTL 1
#define K_TOPT 2
#define K_FMPT 3
#define K_FLAGS 4
#define K_MSGID 5
#define K_Via 6
/* Flags */
#define FL_ZON 1
#define FL_DIR 2
#define FL_LOK 3
#define FL_KFS 4
#define FL_CFM 5
#define FL_XMA 6
#define FL_IMM 7
#define FL_TFS 8
#define FL_AS 9
#define FL_HUB 10
/* Data types */
typedef struct _DupeBase {
#ifdef __MSDOS__
               struct _DupeBase far *next;
#else
               struct _DupeBase *next;
#endif
               char *duperec;
               } DupeBase;
typedef struct _LoopBase {
#ifdef __MSDOS__
               struct _LoopBase far *next;
#else
               struct _LoopBase *next;
#endif
               char *looprec;
               } LoopBase;
#endif

