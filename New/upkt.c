#include "upkt.h"
void fgetsz(FILE *f,char *ptr)
{
static char buf[255];
static char c;
int i=0;
while(TRUE) if (!fread(&c,1,1,f) || !c || i == 254) break; else buf[i++]=c;
buf[i]=0;
strcpy(ptr,buf);
}
void UnPackPKT(char *fromdir,char *todir)
{
static char buf[255],buf3[255],buf4[255],date[255],to[255],from[255],subj[255],msgname[255];
static char buf5[255],buf6[255],buf7[255],buf8[255];
static TPKTFileHeader phea;
static TPKTFileMSGHeader pkt;
static HeaderType hea1;
static char c;
FILE *f,*msg;
int i;
#ifdef __WIN32__
static UINT oldmode;
WIN32_FIND_DATA fd;
HANDLE          sh;
#else
struct ffblk fblock;
#endif
BOOL_1 ECHO;

#ifdef UNIX
sprintf(buf3,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s*.pkt"):("%s/*.pkt"),fromdir);
#else
sprintf(buf3,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s*.pkt"):("%s\\*.pkt"),fromdir);
#endif
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(buf3,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh==INVALID_HANDLE_VALUE) write_log('^',"No PKT files found");
else while (TRUE){
sprintf(buf4,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s%s"):("%s\\%s"),fromdir,fd.cFileName);
#else
if (findfirst(buf3,&fblock,ATTRIB)!=-1) while (TRUE) {
#ifdef UNIX
sprintf(buf4,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s%s"):("%s/%s"),fromdir,fblock.ff_name);
#else
sprintf(buf4,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s%s"):("%s\\%s"),fromdir,fblock.ff_name);
#endif
#endif
sprintf(buf,"Unpacking %s",buf4);
write_log('#',buf);
if ((f=fopen(buf4,"rb"))==NULL) {
sprintf(buf,"Can't open %s",buf4);
write_log('!',buf);
} else {
//  fread(&phea,sizeof(TPKTFileHeader),1,f);
  fread(&phea.OrigNode,1,2,f);
  fread(&phea.DestNode,1,2,f);
  fread(&phea.Year,1,2,f);
  fread(&phea.Month,1,2,f);
  fread(&phea.Day,1,2,f);
  fread(&phea.Hour,1,2,f);
  fread(&phea.Min,1,2,f);
  fread(&phea.Sec,1,2,f);
  fread(&phea.Baud,1,2,f);
  fread(&phea.PktVer,1,2,f);
  fread(&phea.OrigNet,1,2,f);
  fread(&phea.DestNet,1,2,f);
  fread(&phea.ProdCodeLo,1,1,f);
  fread(&phea.SerialNoHi,1,1,f);
  fread(&phea.Password,1,8,f);
  fread(&phea.QOrigZone,1,2,f);
  fread(&phea.QDestZone,1,2,f);
  fread(&phea.AuxNet,1,2,f);
  fread(&phea.CWValCopy,1,2,f);
  fread(&phea.ProdCodeHi,1,1,f);
  fread(&phea.SerialNoLo,1,1,f);
  fread(&phea.CapWord,1,2,f);
  fread(&phea.OrigZone,1,2,f);
  fread(&phea.DestZone,1,2,f);
  fread(&phea.OrigPoint,1,2,f);
  fread(&phea.DestPoint,1,2,f);
  fread(&phea.Product,1,4,f);

  ECHO=FALSE;
  if (phea.PktVer!=2) {
  write_log('^',"Not a Type-2 packet");
  ECHO=TRUE;
  } else while(fread(&pkt,1,sizeof(TPKTFileMSGHeader),f)==sizeof(TPKTFileMSGHeader)) {
    fgetsz(f,date);
    fgetsz(f,to);
    fgetsz(f,from);
    fgetsz(f,subj);

    strcpy(hea1.FromUserName,from);
    strcpy(hea1.ToUserName,to);
    strcpy(hea1.Subject,subj);
    strcpy(hea1.DateTime,date);
    hea1.OrigNode=pkt.OrigNode;
    hea1.DestNode=pkt.DestNode;
    hea1.OrigNet=pkt.OrigNet;
    hea1.DestNet=pkt.DestNet;
    hea1.TimesRead=0;
    hea1.Cost=pkt.Cost;
    hea1.Flags=(UINT_2)pkt.Attr&((UINT_2)0x7413);     // !!!!!!!

    if (hea1.Flags&16) {
    i=substr(subj,buf,0,' ');
    *hea1.Subject=0;
    while (*buf) {
    fnsplit(buf,buf5,buf6,buf7,buf8);
#ifdef UNIX
    sprintf(buf5,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s%s%s"):("%s/%s%s"),fromdir,buf7,buf8);
#else
    sprintf(buf5,(!strlen(fromdir) || fromdir[strlen(fromdir)-1]=='\\' || fromdir[strlen(fromdir)-1]=='/')?("%s%s%s"):("%s\\%s%s"),fromdir,buf7,buf8);
#endif
    if (*hea1.Subject) strcat(hea1.Subject," ");
    strcat(hea1.Subject,buf5);
    i=substr(subj,buf,i,' ');
    }
    }

    i=(int)ftell(f);
    buf[fread(&buf,1,4,f)]=0;
    fseek(f,i,SEEK_SET);
    if (stricmp(buf,"AREA")) {
    msg=NewMsg(todir,msgname);
    fwrite(&hea1,1,sizeof(HeaderType),msg);
    while(fread(&c,1,1,f) && c) fwrite(&c,1,1,msg);
    c=0;
    fwrite(&c,1,1,msg);
    fclose(msg);
    } else {write_log('^',"PKT contains echomail");ECHO=TRUE;break;}
    } /* while */
  fclose(f);
  if (!ECHO) unlink(buf4);
  } /* else */
#ifdef __WIN32__
if (!FindNextFile(sh,&fd)) break;
}
FindClose(sh);
#else
if (findnext(&fblock)==-1) break;
} else write_log('^',"No PKT files found");
#endif
}
