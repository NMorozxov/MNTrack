#include "jam.h"
extern int mid;
int _mdays [13] =  {
/* Jan */   0,
/* Feb */   31,
/* Mar */   31+28,
/* Apr */   31+28+31,
/* May */   31+28+31+30,
/* Jun */   31+28+31+30+31,
/* Jul */   31+28+31+30+31+30,
/* Aug */   31+28+31+30+31+30+31,
/* Sep */   31+28+31+30+31+30+31+31,
/* Oct */   31+28+31+30+31+30+31+31+30,
/* Nov */   31+28+31+30+31+30+31+31+30+31,
/* Dec */   31+28+31+30+31+30+31+31+30+31+30,
/* Jan */   31+28+31+30+31+30+31+31+30+31+30+31
};
UINT_4 JAMsysMkTime(JAMTM *pTm)
{
static UINT_4  Days;
static int     Years;
/*Get number of years since 1970*/
Years = pTm->tm_year - 70;
/*Calculate number of days during these years,*/
/*including extra days for leap years         */
Days = Years * 365 + ((Years + 1) / 4);
/*Add the number of days during this year*/
Days += _mdays [pTm->tm_mon] + pTm->tm_mday - 1;
if((pTm->tm_year & 3) == 0 && pTm->tm_mon > 1) Days++;
/*Convert to seconds, and add the number of seconds this day*/
return(((UINT_4) Days * 86400L) + ((UINT_4) pTm->tm_hour * 3600L) + ((UINT_4) pTm->tm_min * 60L) + (UINT_4) pTm->tm_sec);
}
UINT_4 JAMSysTime(void)
{
static JAMTM  m;
static UINT_4        ti;
struct tm *t;
time_t timer;

timer=time(NULL);
t=localtime(&timer);
m.tm_year = t->tm_year;
m.tm_mon  = t->tm_mon;
m.tm_mday = t->tm_mday;
m.tm_hour = t->tm_hour;
m.tm_min  = t->tm_min;
m.tm_sec  = t->tm_sec;

ti = JAMsysMkTime(&m);
return(ti);
}
FILE *OpenJAMBase(char *Base,JAMHeader *jhr)
{
FILE *f;
static char buf[255];

sprintf(buf,"%s.jhr",Base);
if ((f=fopen(buf,"rb+"))==NULL) {
if ((f=fopen(buf,"wb+"))==NULL) {
write_log('!',"Can't Create JAM Base");
return NULL;
}
ZeroMemory(jhr,sizeof(JAMHeader));
strcpy(jhr->Signature,"JAM");
jhr->DateCreated=JAMSysTime();
jhr->PasswordCrc=0xFFFFFFFFl;
jhr->BaseMsgNum=1;
fwrite(jhr,1,sizeof(JAMHeader),f);
} else {
  fread(jhr,1,sizeof(JAMHeader),f);
  jhr->ModCounter++;
  }
return f;
}
void CloseJAMBase(FILE *f,JAMHeader *jhr)
{
fseek(f,0,SEEK_SET);
fwrite(jhr,1,sizeof(JAMHeader),f);
fclose(f);
}
void PostMessageToJAMBase(char *Base,FILE *fhdr,JAMHeader *jhr,char *text,size_t textlen,char *fad,char *fn,char *tn,char *subj)
{
FILE *f,*fidx;
static UINT_2 i;
static UINT_4 l;
static long hdrpos,hdrpos1;
static JAMMsgHeader jmsghdr;
#ifdef __WIN32__
static char buf[MAX_PATH];
#else
static char buf[255];
#endif

fseek(fhdr,0,SEEK_END);
hdrpos=ftell(fhdr);
jhr->ActiveMsgs++;
ZeroMemory(&jmsghdr,sizeof(JAMMsgHeader));

sprintf(buf,"%s.jdx",Base);
if ((fidx=fopen(buf,"ab+"))==NULL) {
write_log('!',"Can't Open JAM Base");
return;
}
fseek(fidx,0,SEEK_END);


strcpy(jmsghdr.Signature,"JAM");
jmsghdr.Revision=1;
jmsghdr.MsgIdCRC=0xFFFFFFFFl;
jmsghdr.ReplyCRC=0xFFFFFFFFl;
jmsghdr.DateWritten=JAMSysTime();
jmsghdr.DateReceived=jmsghdr.DateWritten;
jmsghdr.Attribute=JAM_MSG_TYPEECHO|JAM_MSG_LOCAL;
jmsghdr.MsgNum=jhr->BaseMsgNum+(ftell(fidx)/8);
jmsghdr.PasswordCRC=0xFFFFFFFFl;

sprintf(buf,"%s.jdt",Base);
if ((f=fopen(buf,"ab+"))==NULL) {
write_log('!',"Can't Open JAM Base");
return;
}
fclose(f);
fopen(buf,"rb+");
fseek(f,0,SEEK_END);

jmsghdr.TxtLen=textlen;
jmsghdr.TxtOffset=ftell(f);
fwrite(text,1,textlen,f);
fclose(f);
fwrite(&jmsghdr,1,sizeof(JAMMsgHeader),fhdr);
hdrpos1=ftell(fhdr);

i=JAMSFLD_OADDRESS;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
l=strlen(fad);
fwrite(&l,1,4,fhdr);
fwrite(fad,1,(size_t)l,fhdr);

/*
i=JAMSFLD_DADDRESS;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
l=strlen(fad);
fwrite(&l,1,4,fhdr);
fwrite(fad,1,l,fhdr);
*/

i=JAMSFLD_SENDERNAME;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
l=strlen(fn);
fwrite(&l,1,4,fhdr);
fwrite(fn,1,(size_t)l,fhdr);

i=JAMSFLD_RECVRNAME;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
l=strlen(tn);
fwrite(&l,1,4,fhdr);
fwrite(tn,1,(size_t)l,fhdr);

i=JAMSFLD_SUBJECT;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
l=strlen(subj);
fwrite(&l,1,4,fhdr);
fwrite(subj,1,(size_t)l,fhdr);

i=JAMSFLD_MSGID;
fwrite(&i,1,2,fhdr);
i=0;
fwrite(&i,1,2,fhdr);
sprintf(buf,"%s %08lx",fad,time(NULL)+mid);
mid++;
l=strlen(buf);
fwrite(&l,1,4,fhdr);
fwrite(buf,1,(size_t)l,fhdr);

jmsghdr.SubfieldLen=ftell(fhdr)-hdrpos1;
//printf("%u\n",jmsghdr.SubfieldLen);
fseek(fhdr,hdrpos,SEEK_SET);
fwrite(&jmsghdr,1,sizeof(JAMMsgHeader),fhdr);


// Update Index
l=0xFFFFFFFFl;
fwrite(&l,1,4,fidx);
l=hdrpos;
fwrite(&l,1,4,fidx);

fclose(fidx);
}

