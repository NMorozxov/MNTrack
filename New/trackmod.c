#include "trackmod.h"
BOOL_1 FileExist(char *name)
{
#ifdef __WIN32__
WIN32_FIND_DATA fd;
HANDLE          sh;
static UINT     oldmode;
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(name,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh==INVALID_HANDLE_VALUE) {FindClose(sh);return FALSE;}
else {FindClose(sh);return TRUE;}
#else
struct ffblk fbl;
if (findfirst(name,&fbl,ATTRIB)!=-1) return TRUE;
return FALSE;
#endif
}
void adr2txt(Adr4D addr,char *txt)
{
sprintf(txt,(addr.point)?("%d:%d/%d.%d"):("%d:%d/%d"),addr.zone,addr.net,addr.node,addr.point);
return;
}
void txt2adr(char *txt,Adr4D *addr)
{
static char buf[255];
int index=0,i;
addr->zone=0;
addr->node=0;
addr->net=0;
addr->point=0;
if (*txt!='/') {
index=substr(txt,buf,index,':');
if (*buf==0) return;
addr->zone=(UINT_2)atoi(buf);
index=substr(txt,buf,index,'/');
if (*buf==0) return;
addr->net=(UINT_2)atoi(buf);
} else index=1;
for(i=index;(size_t)i<strlen(txt) && txt[i]!=0 && txt[i]!='.' && txt[i]!='@';i++)
 buf[i-index]=txt[i];
buf[i-index]=0;
if (*buf==0) return;
addr->node=(UINT_2)atoi(buf);
if (txt[i]=='@') return;
if (txt[i]==0) return;
index=++i;
for(i=index;(size_t)i<strlen(txt) && txt[i]!='@';i++)
 buf[i-index]=txt[i];
buf[i-index]=0;
addr->point=(UINT_2)atoi(buf);
return;
}
void getdomain(char *adr,char *domain)
{
char *c=adr;
while (*c!='@') if (*c==0) {strcpy(domain,"");return;} else c++;
strcpy(domain,c);
return;
}
#ifndef __WIN32__
void ZeroMemory(void *Destination,int Length)
{
char *d;
int i;
for(i=0,d=(char *)Destination;i<Length;i++,d++) *d=0;
}
#endif

