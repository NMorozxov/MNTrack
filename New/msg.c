#include "msg.h"
extern ConfigType config;
extern int mid;
/* Make new .msg file and update lastread */
FILE *NewMsg(char *pat,char *newfile)
{
static char buf[255],buf1[255],buf2[255],buf3[255],buf4[255],buf5[255];
FILE *f;
#ifdef __WIN32__
static UINT oldmode;
WIN32_FIND_DATA fd;
HANDLE          sh;
#else
struct ffblk fbl;
#endif
UINT_2 i=0;
#ifdef DEBUG
write_log('~',"->NewMsg");
#endif
#ifdef UNIX
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%slastread"):("%s/lastread"),pat);
#else
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%slastread"):("%s\\lastread"),pat);
#endif
f=fopen(buf,"rb+");
if (f!=NULL) {
fread(&i,1,2,f);
if (config.updatelastread) fseek(f,0,SEEK_SET);
else fclose(f);
} else if (config.updatelastread) f=fopen(buf,"wb+");
if (config.updatelastread) if (f==NULL) {
sprintf(buf1,"Can't create %s.",buf);
write_log('!',buf1);
*newfile=0;
return NULL;
}
#ifdef UNIX
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%s*.msg"):("%s/*.msg"),pat);
#else
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%s*.msg"):("%s\\*.msg"),pat);
#endif

#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(buf,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh!=INVALID_HANDLE_VALUE) while (TRUE) {
fnsplit(fd.cFileName,buf2,buf3,buf4,buf5);
#else
if (findfirst(buf,&fbl,ATTRIB)!=-1) while (TRUE) {
fnsplit(fbl.ff_name,buf2,buf3,buf4,buf5);
#endif


if (atoi(buf4)>i) i=(UINT_2)atoi(buf4);

#ifdef __WIN32__
if (!FindNextFile(sh,&fd)) break;
#else
if (findnext(&fbl)==-1) break;
#endif
}
i++;
#ifdef UNIX
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%s%u.msg"):("%s/%u.msg"),pat,i);
#else
sprintf(buf,(strlen(pat) && (pat[strlen(pat)-1]=='\\'|| pat[strlen(pat)-1]=='/'))?("%s%u.msg"):("%s\\%u.msg"),pat,i);
#endif
strcpy(newfile,buf);
if (config.updatelastread && f!=NULL) {fwrite(&i,1,2,f);fclose(f);}
f=fopen(buf,"wb+");
#ifdef DEBUG
write_log('~',"<-NewMsg");
#endif
return f;
}
/* Make Msg Header */
void MakeMsgHeader(char *from,Adr4D fad,char *to,Adr4D tad,char *subj,char *dmn,FILE *f)
{
HeaderType hea1;
static char moth[4],buf[255],buf1[255];
struct tm *tmm;
time_t timer;
#ifdef DEBUG
write_log('~',"->MakeMsgHeader");
#endif
ZeroMemory(&hea1,sizeof(HeaderType));
strcpy(hea1.FromUserName,from);
strcpy(hea1.ToUserName,to);
strcpy(hea1.Subject,subj);
hea1.OrigNode=fad.node;
hea1.DestNode=tad.node;
hea1.OrigNet=fad.net;
hea1.DestNet=tad.net;
hea1.TimesRead=0;
hea1.Flags=0x0101;
if (config.ksanswer) hea1.Flags+=(UINT_2)128;
hea1.NextReply=0;
timer=time(NULL);
tmm=localtime(&timer);
GetMonth(tmm->tm_mon+1,moth);
sprintf(hea1.DateTime,"%2.2d %s %2.2d  %2.2d:%2.2d:%2.2d",tmm->tm_mday,moth,year42(tmm->tm_year+1900),tmm->tm_hour,tmm->tm_min,tmm->tm_sec);
fwrite(&hea1.FromUserName,1,36,f);
fwrite(&hea1.ToUserName,1,36,f);
fwrite(&hea1.Subject,1,72,f);
fwrite(&hea1.DateTime,1,20,f);
fwrite(&hea1.TimesRead,1,2,f);
fwrite(&hea1.DestNode,1,2,f);
fwrite(&hea1.OrigNode,1,2,f);
fwrite(&hea1.Cost,1,2,f);
fwrite(&hea1.OrigNet,1,2,f);
fwrite(&hea1.DestNet,1,2,f);
fwrite(&hea1.DestZone,1,2,f);
fwrite(&hea1.OrigZone,1,2,f);
fwrite(&hea1.DestPoint,1,2,f);
fwrite(&hea1.OrigPoint,1,2,f);
fwrite(&hea1.ReplyTo,1,2,f);
fwrite(&hea1.Flags,1,2,f);
fwrite(&hea1.NextReply,1,2,f);
sprintf(buf,"\1INTL %u:%u/%u %u:%u/%u\r",tad.zone,tad.net,tad.node,fad.zone,fad.net,fad.node);
fwrite(buf,1,strlen(buf),f);
if (fad.point) {
sprintf(buf,"\1FMPT %u\r",fad.point);
fwrite(buf,1,strlen(buf),f);
}
if (tad.point) {
sprintf(buf,"\1TOPT %u\r",tad.point);
fwrite(buf,1,strlen(buf),f);
}
adr2txt(fad,buf1);
sprintf(buf,"\1MSGID: %s%s %08lx\r",buf1,dmn,time(NULL)+mid);
mid++;
fwrite(buf,1,strlen(buf),f);
#ifdef DEBUG
write_log('~',"<-MakeMsgHeader");
#endif
}
