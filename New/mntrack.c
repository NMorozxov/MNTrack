#include "mntrack.h"
#include "version.h"
extern ConfigType config;
char FileName[255];
extern char MesPrev[255];
extern char MesPost[255];
unsigned long tact,maxact,tdmn,maxdmn,taka,maxaka;
#ifdef __MSDOS__
NdxRec    far *FNdx=NULL,far *TNdx=NULL,far *PNdx=NULL;
ScriptRec far *FScr=NULL,far *TScr=NULL,far *PScr=NULL;
DmnRec    far *FDmn=NULL,far *TDmn=NULL,far *PDmn=NULL;
DupeBase  far *FBas=NULL,far *TBas=NULL,far *PBas=NULL;
AKAType   far *FAKA=NULL,far *TAKA=NULL,far *PAKA=NULL;
#else
NdxRec    *FNdx=NULL,*TNdx=NULL,*PNdx=NULL;
ScriptRec *FScr=NULL,*TScr=NULL,*PScr=NULL;
DmnRec    *FDmn=NULL,*TDmn=NULL,*PDmn=NULL;
DupeBase  *FBas=NULL,*TBas=NULL,*PBas=NULL;
AKAType   *FAKA=NULL,*TAKA=NULL,*PAKA=NULL;
#endif
BOOL_1 F_Quiet=FALSE,F_CR=FALSE,F_CLOSED=FALSE;
BOOL_1 F_EMPTY=TRUE,F_VIA=FALSE;
BOOL_1 F_Dupe=FALSE,F_Loop=FALSE;
BOOL_1 ZON_F=FALSE,DIR_F=FALSE,LOK_F=FALSE,KFS_F=FALSE,CFM_F=FALSE;
BOOL_1 XMA_F=FALSE,IMM_F=FALSE,TFS_F=FALSE,AS_F=FALSE,HUB_F=FALSE;
static UINT_2 uued;
static char Drive[3],Dir[255],Name[255],Ext[255];
HeaderType hea;
int mid=0;
/* Kludges */
static char topt[255],msgid[255],fmpt[255],intl_to[255],intl_from[255];
/* Address Variables */
static char FromAddr[255],ToAddr[255];
static Adr4D FmAd,ToAd;
/* Token tables */
static TokenTable KludgTokens[]={
           {"INTL",K_INTL},
           {"TOPT",K_TOPT},
           {"FMPT",K_FMPT},
           {"FLAGS",K_FLAGS},
           {"MSGID:",K_MSGID},
           {"Via",K_Via},
           {"",0}};
static TokenTable ArgTokens[]={
           {"/H",ARG_HELP},
           {"/Q",ARG_QUIET},
           {"/F",ARG_SCAN},
           {"/S",ARG_SCR},
           {"/U",ARG_UNPKT},
           {"",0}};
static TokenTable FlagsTokens[]={
           {"ZON",FL_ZON},
           {"DIR",FL_DIR},
           {"LOK",FL_LOK},
           {"KFS",FL_KFS},
           {"CFM",FL_CFM},
           {"XMA",FL_XMA},
           {"IMM",FL_IMM},
           {"TFS",FL_TFS},
           {"A/S",FL_AS},
           {"HUB",FL_HUB},
           {"",0}};
static TokenTable ScriptTokens[]={
           {"OUTLOG",SCR_OUTLOG},
           {"LOGSTART",SCR_LOGSTART},
           {"LOGEND",SCR_LOGEND},
           {"LOGDROP",SCR_LOGDROP},
           {"BREAK",SCR_BREAK},
           {"NOBREAK",SCR_NOBREAK},
           {"NOCASE",SCR_NOCASE},
           {"REALCASE",SCR_REALCASE},
           {"QUIT",SCR_QUIT},
           {"GOTO",SCR_GOTO},
           {"JMP",SCR_GOTO},
           {"JE",SCR_JE},
           {"JNE",SCR_JNE},
           {"SUBJ",SCR_SUBJ},
           {"INSUBJ",SCR_INSUBJ},
           {"TONAME",SCR_TONAME},
           {"FROMNAME",SCR_FROMNAME},
           {"FROMADR",SCR_FROMADR},
           {"FROMADR3D",SCR_FROMADR3D},
           {"TOADR",SCR_TOADR},
           {"TOADR3D",SCR_TOADR3D},
           {"TOZONE",SCR_TOZONE},
           {"TONET",SCR_TONET},
           {"TONODE",SCR_TONODE},
           {"TOPOINT",SCR_TOPOINT},
           {"FROMZONE",SCR_FROMZONE},
           {"FROMNET",SCR_FROMNET},
           {"FROMNODE",SCR_FROMNODE},
           {"FROMPOINT",SCR_FROMPOINT},
           {"LOOP",SCR_LOOP},
           {"DUPE",SCR_DUPE},
           {"INTL",SCR_INTL},
           {"MSGID",SCR_MSGID},
           {"TOLISTED",SCR_TOLISTED},
           {"FROMLISTED",SCR_FROMLISTED},
           {"EMPTY",SCR_EMPTY},
           {"INBODY",SCR_INBODY},
           {"MSGSIZE",SCR_MSGSIZE},
           {"UUE",SCR_UUE},
           {"PVT",SCN_PVT},
           {"CRA",SCN_CRA},
           {"RCV",SCN_RCV},
           {"SNT",SCN_SNT},
           {"ATT",SCN_ATT},
           {"TRS",SCN_TRS},
           {"ORP",SCN_ORP},
           {"K/S",SCN_KS},
           {"LOC",SCN_LOC},
           {"HLD",SCN_HLD},
           {"FRQ",SCN_FRQ},
           {"RRQ",SCN_RRQ},
           {"RRC",SCN_RRC},
           {"ARQ",SCN_ARQ},
           {"URQ",SCN_URQ},
           {"ZON",SCN_ZON},
           {"DIR",SCN_DIR},
           {"LOK",SCN_LOK},
           {"KFS",SCN_KFS},
           {"CFM",SCN_CFM},
           {"XMA",SCN_XMA},
           {"IMM",SCN_IMM},
           {"TFS",SCN_TFS},
           {"A/S",SCN_AS},
           {"HUB",SCN_HUB},
           {"MOVE",SCN_MOVE},
           {"COPY",SCN_COPY},
           {"SEMAPHORE",SCN_SEMAPHORE},
           {"DELETE",SCN_DELETE},
           {"DELETEATTACH",SCN_DELETEATTACH},
           {"WRITETOJAMECHO",SCN_WRITETOJAMECHO},
           {"BOUNCE",SCN_BOUNCE},
           {"FORWARD",SCN_FORWARD},
           {"MAKEMSG",SCN_MAKEMSG},
           {"SETPVT",SCN_SETPVT},
           {"CLEARPVT",SCN_CLEARPVT},
           {"SETCRA",SCN_SETCRA},
           {"CLEARCRA",SCN_CLEARCRA},
           {"SETRCV",SCN_SETRCV},
           {"CLEARRCV",SCN_CLEARRCV},
           {"SETSNT",SCN_SETSNT},
           {"CLEARSNT",SCN_CLEARSNT},
           {"SETATT",SCN_SETATT},
           {"CLEARATT",SCN_CLEARATT},
           {"SETTRS",SCN_SETTRS},
           {"CLEARTRS",SCN_CLEARTRS},
           {"SETORP",SCN_SETORP},
           {"CLEARORP",SCN_CLEARORP},
           {"SETK/S",SCN_SETKS},
           {"CLEARK/S",SCN_CLEARKS},
           {"SETLOC",SCN_SETLOC},
           {"CLEARLOC",SCN_CLEARLOC},
           {"SETHLD",SCN_SETHLD},
           {"CLEARHLD",SCN_CLEARHLD},
           {"SETFRQ",SCN_SETFRQ},
           {"CLEARFRQ",SCN_CLEARFRQ},
           {"SETRRQ",SCN_SETRRQ},
           {"CLEARRRQ",SCN_CLEARRRQ},
           {"SETRRC",SCN_SETRCC},
           {"CLEARRRC",SCN_CLEARRRC},
           {"SETARQ",SCN_SETARQ},
           {"CLEARARQ",SCN_CLEARARQ},
           {"SETURQ",SCN_SETURQ},
           {"CLEARURQ",SCN_CLEARURQ},
           {"BUSYSYSTEMCHECK",SCN_BUSYCHECK},
           {"BUSYSYSTEMSET",SCN_BUSYSET},
           {"BUSYSYSTEMUNSET",SCN_BUSYUNSET},
           {"BUSYSYSTEMFLAGS",SCN_BUSYSYSTEMFLAGS},
           {"NOBUSYSYSTEMFLAGS",SCN_NOBUSYSYSTEMFLAGS},
           {"PACK",SCN_PACK},
           {"PACKPKT",SCN_PACKPKT},
           {"ATTACH",SCN_ATTACH},
           {"FREQ",SCN_FREQ},
           {"SETSUBJ",SCN_SETSUBJ},
           {"SETFROMNAME",SCN_SETFROMNAME},
           {"SETTONAME",SCN_SETTONAME},
           {"INFROMNAME",SCN_INFROMNAME},
           {"INTONAME",SCN_INTONAME},
           {"MAKEPKT",SCN_MAKEPKT},
           {"VIA",SCN_VIA},
           {"EXEC",SCN_EXEC},
           {"WRITETOFILE",SCN_WRITETOFILE},
           {"EXISTATTACH",SCN_EXISTATTACH},
           {"APPENDTOFILE",SCN_APPENDTOFILE},
           {"SECOND",SCN_SECOND},
           {"MINUTE",SCN_MINUTE},
           {"HOUR",SCN_HOUR},
           {"STRIPPATH",SCN_STRIPPATH},
           {"SETTOZONE",SCN_SETTOZONE},
           {"SETFROMZONE",SCN_SETFROMZONE},
           {"EXISTFILE",SCN_EXISTFILE},
           {"",0}};
/* Mach Address */
char *MachAddress(Adr4D adr)
{
TAKA=FAKA;
while (TAKA!=NULL) {
if (atoi(TAKA->zone)==adr.zone && atoi(TAKA->net)==adr.net) return TAKA->addr;
TAKA=(AKAType *)TAKA->next;
}
return config.bouadr;
}
/* Writes Tearline */
void WriteTearline(FILE *f)
{
static char buf[80];
#ifdef DEBUG
write_log('~',"->Writetearline");
#endif
fwrite(&buf,1,sprintf(buf,"\r--- MNTrack %s (C) Nicol Morozov 2:5020/991",version),f);
#ifdef DEBUG
write_log('~',"<-Writetearline");
#endif
}
/* Writes Origin */
void WriteOrigin(char *from,FILE *f)
{
static char buf[80];
#ifdef DEBUG
write_log('~',"->WriteteOrigin");
#endif
fwrite(&buf,1,sprintf(buf,"\r * Origin: MNTrack %s (C) Nicol Morozov 2:5020/991 (%s)",version,from),f);
#ifdef DEBUG
write_log('~',"<-WriteOrigin");
#endif
}
/* Writes body */
void WriteBody(FILE *f,FILE *fmsg,int w_body,int w_klu)
{
static char c;
#ifdef DEBUG
write_log('~',"->WriteBody");
#endif
if (F_CLOSED)
 {
 write_log('!',"Error processing ~B macros : Message file does not exist");
 return;
 }
fseek(fmsg,sizeof(HeaderType),SEEK_SET);
while (fread(&c,1,1,fmsg))
 {
 wb_l_s:if (c==0) break;
 if (c==1) if (w_klu)
            {
            c='@';
            fwrite(&c,1,1,f);
            do if (!fread(&c,1,1,fmsg) || !c)
                {
                write_log('~',"<-WriteBody EOF or Zero in kludge line");
                return;
                }
               else fwrite(&c,1,1,f);
            while (c!=0xa && c!=0xd);
            do if (!fread(&c,1,1,fmsg) || !c)
               {
#ifdef DEBUG
               write_log('~',"<-WriteBody EOF or Zero after kludge line");
#endif
               return;
               }
               else if (c==0xa || c==0xd) fwrite(&c,1,1,f);
            while (c==0xa || c==0xd);
            goto wb_l_s;
            }
           else
            {
            do if (!fread(&c,1,1,fmsg) || !c)
                {
                write_log('~',"<-WriteBody EOF or Zero in kludge line");
                return;
                }
            while (c!=0xA && c!=0xD);
            do if (!fread(&c,1,1,fmsg) || !c)
                {
#ifdef DEBUG
                write_log('~',"<-WriteBody EOF or Zero after kludge line");
#endif
                return;
                }
            while (c==0xa || c==0xd);
            goto wb_l_s;
            }
 if (!w_body) continue;
 if (c=='-')
  {
  fwrite(&c,1,1,f);
  fread(&c,1,1,fmsg);
  if (c=='-') c='+';
  }
 if (c==' ')
  {
  fwrite(&c,1,1,f);
  fread(&c,1,1,fmsg);
  if (c=='*') c='+';
  }
 fwrite(&c,1,1,f);
 }
#ifdef DEBUG
write_log('~',"<-WriteBody Normaly");
#endif
}
/* Writes template to a file */
BOOL_1 WriteTpl(FILE *f,char *tpl,FILE *fmsg)
{
FILE *tplf;
char c;
static char buf[255];
struct tm *tmm;
BOOL_1 leadingzero;
time_t timer;
#ifdef DEBUG
write_log('~',"->WriteTpl");
#endif
tplf=fopen(tpl,"rb");

if (tplf==NULL) {sprintf(buf,"Can't open %s",tpl);write_log('^',buf);return FALSE;}
while(fread(&c,1,1,tplf))
{
if (c=='~')
{
fread(&c,1,1,tplf);
switch((char)toupper(c))
 {
 case 'H':
  fread(&c,1,1,tplf);
  switch(((char)toupper(c)))
   {
   case 'D':
    fwrite(&hea.DateTime,1,strlen(hea.DateTime),f);
   break;
   case 'S':
    fwrite(&hea.Subject,1,strlen(hea.Subject),f);
   break;
   }
 break;
 case 'F':
  fread(&c,1,1,tplf);
  switch(((char)toupper(c)))
   {
   case 'N':
    fwrite(&hea.FromUserName,1,strlen(hea.FromUserName),f);
   break;
   case 'A':
    fwrite(&FromAddr,1,strlen(FromAddr),f);
   break;
   case '3':
    sprintf(buf,"%u:%u/%u",FmAd.zone,FmAd.net,FmAd.node);
    fwrite(&buf,1,strlen(buf),f);
   break;
   }
 break;
 case 'D':
  fread(&c,1,1,tplf);
  switch(((char)toupper(c)))
   {
   case 'N':
    fwrite(&hea.ToUserName,1,strlen(hea.ToUserName),f);
   break;
   case 'A':
    fwrite(&ToAddr,1,strlen(ToAddr),f);
   break;
   case '3':
    sprintf(buf,"%u:%u/%u",ToAd.zone,ToAd.net,ToAd.node);
    fwrite(&buf,1,strlen(buf),f);
   break;
   }
 break;
 case 'V':
  fwrite(&version,1,strlen(version),f);
 break;
 case 'N':
  fwrite(&config.sysopname,1,strlen(config.sysopname),f);
 break;
 case 'L':
  timer=time(NULL);
  tmm=localtime(&timer);
  fread(&c,1,1,tplf);
  if (c=='0')
   {
   leadingzero=TRUE;
   fread(&c,1,1,tplf);
   }
  else leadingzero=FALSE;
  switch(((char)toupper(c)))
   {
   case 'S':
    sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_sec);
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'M':
    sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_min);
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'H':
    sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_hour);
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'A':
    sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_mday);
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'O':
    fread(&c,1,1,tplf);
    switch(((char)toupper(c)))
     {
     case 'I':
      sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_mon);
     break;
     //case 'T':
     default:
      GetMonth(tmm->tm_mon,buf);
     break;
     }
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'W':
    fread(&c,1,1,tplf);
    switch(((char)toupper(c)))
     {
     case 'I':
      sprintf(buf,"%d",tmm->tm_wday);
     break;
     //case 'T':
     default:
      GetDayOfWeek(tmm->tm_wday,buf);
     break;
     }
    fwrite(&buf,1,strlen(buf),f);
   break;
   case 'Y':
    fread(&c,1,1,tplf);
    switch(((char)toupper(c)))
     {
     case '2':
      sprintf(buf,(leadingzero)?("%02d"):("%d"),year42(tmm->tm_year+1900));
     break;
     //case '4':
     default:
      sprintf(buf,"%d",tmm->tm_year+1900);
     break;
     }
    fwrite(&buf,1,strlen(buf),f);
   break;
   }
 break;
 case 'B':
  fread(&c,1,1,tplf);
  switch(((char)toupper(c)))
   {
   case 'C':
    WriteBody(f,fmsg,TRUE,TRUE);
   break;
   case 'T':
    WriteBody(f,fmsg,TRUE,FALSE);
   break;
   case 'K':
    WriteBody(f,fmsg,FALSE,TRUE);
   break;
   }
 break;
 //case '~':
 default:
  fwrite(&c,1,1,f);
 } /* switch */
} else fwrite(&c,1,1,f);
} /* while */
fclose(tplf);
#ifdef DEBUG
write_log('~',"<-WriteTpl");
#endif
return TRUE;
}
/* Write Via */
void WriteVia(char *from,FILE *f)
{
static char buf[255];
struct tm *tmm;
time_t timer;
#ifdef DEBUG
write_log('~',"->WriteVia");
#endif
timer=time(NULL);
tmm=localtime(&timer);
fwrite(&buf,1,sprintf(buf,"\1Via %s @%4.4d%2.2d%2.2d.%2.2d%2.2d%2.2d.UTC%+ld MNTrack %s\r",from,tmm->tm_year+1900,tmm->tm_mon+1,tmm->tm_mday,tmm->tm_hour,tmm->tm_min,tmm->tm_sec,-_timezone/3600+_daylight,version),f);
#ifdef DEBUG
write_log('~',"<-WriteVia");
#endif
}
/* Clear Flags */
void ClearFlags(FILE *fmsg)
{
UINT_2 flg=(UINT_2)((config.clearbefore&0xFC00)*2);
flg+=(UINT_2)(config.clearbefore&0x3FF);
hea.Flags&=(UINT_2)(65535l-flg);
fseek(fmsg,0,SEEK_SET);
fwrite(&hea,1,sizeof(HeaderType),fmsg);
}
void SetFlags(FILE *fmsg)
{
UINT_2 flg=(UINT_2)((config.setafter&0xFC00)*2);
flg+=(UINT_2)(config.setafter&0x3FF);
hea.Flags|=flg;
fseek(fmsg,0,SEEK_SET);
fwrite(&hea,1,sizeof(HeaderType),fmsg);
}
void ClearFlag(FILE *fmsg,UINT_2 flg,char *name)
{
static char buf[255];
if (F_CLOSED) {
write_log('!',"Message file does not exist");
return;
}
hea.Flags&=(UINT_2)(65535l-flg);
fseek(fmsg,0,SEEK_SET);
fwrite(&hea,1,sizeof(HeaderType),fmsg);
sprintf(buf,"Cleaning %s Flag",name);
write_log('#',buf);
}
void SetFlag(FILE *fmsg,UINT_2 flg,char *name)
{
static char buf[255];
if (F_CLOSED) {
write_log('!',"Message file does not exist");
return;
}
hea.Flags|=flg;
fseek(fmsg,0,SEEK_SET);
fwrite(&hea,1,sizeof(HeaderType),fmsg);
sprintf(buf,"Seting %s Flag",name);
write_log('#',buf);
}
/* Parse single script */
void ParseSingleScript(FILE *fmsg)
{
long KomRet=TRUE,KomRetOld=TRUE;
BOOL_1 KomInv=FALSE,KomAND=FALSE,KomOR=FALSE,KomXOR=FALSE;
BOOL_1 CaseS=TRUE,BreakF=TRUE,BF_FLAG=FALSE,leadingzero;
FILE *fscr,*f,*f1;
struct tm *tmm;
time_t timer;
static Adr4D adr,adr1;
static char sstr[255],scrc[255],buf[255],buf1[255],buf2[255],buf3[255],buf4[255];
static char buf5[255],buf6[255],buf7[255],c[3],b;
static int index,i;
static size_t ui;
static JAMHeader jhr;
#ifdef __MSDOS__
void far *p;
#else
void *p;
#endif

#ifdef DEBUG
write_log('~',"->ParseSingleScript");
#endif

timer=time(NULL);
tmm=localtime(&timer);

fscr=fopen(TScr->scr.name,"r");

if (fscr==NULL) {
sprintf(sstr,"Can't open script %s",TScr->scr.name);
write_log('!',sstr);
exit_mntrack(5);
}
/* Parse Cicle */
while (fgets(sstr,255,fscr)!=NULL) {
char *c1,*c2,*c3;
#ifdef DEBUG
sprintf(buf,"Step 1 :KomRet=%d KomRetOld=%d",KomRet,KomRetOld);
write_log('~',buf);
#endif
if (config.stop && F_CLOSED) {
fclose(fscr);
return;
}
if (KomInv) {KomRet=!KomRet;KomInv=FALSE;}
if (KomAND) {KomRet=KomRetOld&&KomRet;KomAND=FALSE;}
if (KomOR) {KomRet=KomRetOld||KomRet;KomOR=FALSE;}
if (KomXOR) {if (KomRet && KomRetOld) KomRet=FALSE;else KomRet=KomRetOld||KomRet;KomXOR=FALSE;}
#ifdef DEBUG
sprintf(buf,"Step 2 : KomRet=%d KomRetOld=%d",KomRet,KomRetOld);
write_log('~',buf);
#endif
if (!KomRet && BreakF) break;
while (strlen(sstr) && (sstr[strlen(sstr)-1]==0xD || sstr[strlen(sstr)-1]==0xA || sstr[strlen(sstr)-1]==' ')) sstr[strlen(sstr)-1]=0;
if (!sstr[0] || sstr[0]==':' || sstr[0]==';') continue;
#ifdef DEBUG
sprintf(buf1,"Command line before parsing : %s",sstr);
write_log('~',buf1);
#endif
strcpy(buf,sstr);
*sstr=0;c1=buf;c2=sstr;
while(*c1)
{
if (*c1=='~')
{
c1++; if (!*c1) break;
switch (toupper(*c1))
 {
 case '~':
  *c2='~';
  c2++;
 break;
 case 'F':
  c1++;
  switch(((char)toupper(*c1)))
   {
   case 'N':
    c3=hea.FromUserName;
   break;
   case 'A':
    c3=FromAddr;
   break;
   case '3':
    sprintf(buf1,"%u:%u/%u",FmAd.zone,FmAd.net,FmAd.node);
    c3=buf1;
   break;
   }
  while (*c3) {*c2=*c3;c2++;c3++;}
 break;
 case 'D':
  c1++;
  switch(((char)toupper(*c1)))
   {
   case 'N':
    c3=hea.ToUserName;
   break;
   case 'A':
    c3=ToAddr;
   break;
   case '3':
    sprintf(buf1,"%u:%u/%u",ToAd.zone,ToAd.net,ToAd.node);
    c3=buf1;
   break;
   }
  while (*c3) {*c2=*c3;c2++;c3++;}
 break;
 case 'H':
  c1++;
  switch(((char)toupper(*c1)))
   {
   case 'D':
    c3=hea.DateTime;
   break;
   case 'S':
    c3=hea.Subject;
   break;
   }
  while (*c3) {*c2=*c3;c2++;c3++;}
 break;
 case 'V' :
  c3=version;
  while (*c3) {*c2=*c3;c2++;c3++;}
 break;
 case 'N' :
  c3=config.sysopname;
  while (*c3) {*c2=*c3;c2++;c3++;}
 break;
 case 'L':
 c1++;
 if (*c1=='0')
  {
  leadingzero=TRUE;
  c1++;
  }
 else leadingzero=FALSE;
 switch(((char)toupper(*c1)))
  {
  case 'S':
   sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_sec);
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'M':
   sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_min);
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'H':
   sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_hour);
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'A':
   sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_mday);
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'O':
   c1++;
   switch(((char)toupper(*c1)))
    {
    case 'I':
     sprintf(buf,(leadingzero)?("%02d"):("%d"),tmm->tm_mon);
    break;
    //case 'T':
    default:
     GetMonth(tmm->tm_mon,buf);
    break;
    }
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'W':
   c1++;
   switch(((char)toupper(*c1)))
    {
    case 'I':
     sprintf(buf,"%d",tmm->tm_wday);
    break;
    //case 'T':
    default:
     GetDayOfWeek(tmm->tm_wday,buf);
    break;
    }
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  case 'Y':
   c1++;
   switch(((char)toupper(*c1)))
    {
    case '2':
     sprintf(buf,(leadingzero)?("%02d"):("%d"),year42(tmm->tm_year+1900));
    break;
    //case '4':
    default:
     sprintf(buf,"%d",tmm->tm_year+1900);
    break;
    }
   c3=buf;
   while (*c3) {*c2=*c3;c2++;c3++;}
  break;
  }
 break;
 }
} else {*c2=*c1;c2++;}
c1++;
}
*c2=0;
#ifdef DEBUG
sprintf(buf1,"Command line after parsing : %s",sstr);
write_log('~',buf1);
#endif
while (TRUE) switch (sstr[0]) {
             case '-':
              KomInv=TRUE;
              strcpy(scrc,sstr+1);
              strcpy(sstr,scrc);
              break;
             case '&':
              KomAND=TRUE;
              strcpy(scrc,sstr+1);
              strcpy(sstr,scrc);
              break;
             case '|':
              KomOR=TRUE;
              strcpy(scrc,sstr+1);
              strcpy(sstr,scrc);
              break;
             case '^':
              KomXOR=TRUE;
              strcpy(scrc,sstr+1);
              strcpy(sstr,scrc);
              break;
             default: goto Parse;
             }
Parse:
index=substr(sstr,scrc,0,' ');
sprintf(buf,"Parsing script command : '%s'",scrc);
write_log('~',buf);
switch (GetToken(ScriptTokens,scrc,0,FALSE)) {
case SCN_EXISTFILE:
 KomRetOld=KomRet;
 KomRet=FileExist(sstr+index);
 break;
case SCN_SETFROMZONE:
 FmAd.zone=(UINT_2)atoi(sstr+index);
 adr2txt(FmAd,FromAddr);
 break;
case SCN_SETTOZONE:
 ToAd.zone=(UINT_2)atoi(sstr+index);
 adr2txt(ToAd,ToAddr);
 break;
case SCN_STRIPPATH:
 strcpy(buf,hea.Subject);
 *hea.Subject=0;
 i=substr(buf,buf3,0,' ');
 while (*buf3) {
 fnsplit(buf3,buf4,buf5,buf6,buf7);
 if (*hea.Subject) strcat(hea.Subject," ");
 strcat(hea.Subject,buf6);
 strcat(hea.Subject,buf7);
 i=substr(buf,buf3,i,' ');
 }
 fseek(fmsg,0,SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),fmsg);
 break;
case SCN_SECOND:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (tmm->tm_sec>atoi(sstr+index)) KomRet=TRUE;
 break;
case SCN_MINUTE:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (tmm->tm_min>atoi(sstr+index)) KomRet=TRUE;
 break;
case SCN_HOUR:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (tmm->tm_hour>atoi(sstr+index)) KomRet=TRUE;
 break;
case SCN_WRITETOJAMECHO:
 index=substr(sstr,buf1,index,' '); //base
 index=substr(sstr,buf3,index,'"'); //fn
 index=substr(sstr,buf4,index,' '); //fa
 index=substr(sstr,buf5,index,'"'); //tn
 index=substr(sstr,buf2,index,' '); //tpl
 index=substr(sstr,buf6,index,'"'); //s
 if (!FileExist(buf2)) {
 sprintf(buf,"File not exist %s",buf2);
 write_log('!',buf);
 break;
 }
 f=OpenJAMBase(buf1,&jhr);
 if (f==NULL) break;
 if ((f1=fopen("mntrack.tmp","wb+"))==NULL) {
 write_log('!',"Can't create mntrack.tmp");
 break;
 }
 WriteTpl(f1,buf2,fmsg);
 WriteTearline(f1);
 WriteOrigin(buf4,f1);
 ui=(size_t)ftell(f1);
 if ((p=farcalloc(1,ui+1))==NULL) {
 exit_mntrack(2);
 }
 fseek(f1,0,SEEK_SET);
 fread(p,1,ui,f1);
 fclose(f1);
 unlink("mntrack.tmp");
 PostMessageToJAMBase(buf1,f,&jhr,p,ui,buf4,buf3,buf5,buf6);
 farfree(p);
 CloseJAMBase(f,&jhr);
 write_log('%',"Posted message to JAM");
 break;
case SCN_EXISTATTACH:
 KomRetOld=KomRet;
 KomRet=TRUE;
 i=substr(hea.Subject,buf3,0,' ');
 while (*buf3) {
 fnsplit(buf3,buf4,buf5,buf6,buf7);
#ifdef UNIX
 if (!*buf4 && !*buf5 && strlen(config.out)) sprintf(buf,(config.out[strlen(config.out)]!='\\' && config.out[strlen(config.out)]!='/')?("%s/%s"):("%s%s"),config.out,buf3);
#else
 if (!*buf4 && !*buf5 && strlen(config.out)) sprintf(buf,(config.out[strlen(config.out)]!='\\' && config.out[strlen(config.out)]!='/')?("%s\\%s"):("%s%s"),config.out,buf3);
#endif
 else strcpy(buf,buf3);
 if (!FileExist(buf)) KomRet=FALSE;
 i=substr(hea.Subject,buf3,i,' ');
 }
 break;
case SCN_APPENDTOFILE:
 index=substr(sstr,buf1,index,' ');
 index=substr(sstr,buf2,index,' ');
 if (!FileExist(buf1)) {
 sprintf(buf,"File not exist %s",buf1);
 write_log('!',buf);
 break;
 }
 sprintf(buf3,"Appending template %s to file %s",buf1,buf2);
 write_log('%',buf3);
 f=fopen(buf2,"ab+");
 if (f==NULL) {write_log('!',"Can't open/create file");break;};
 WriteTpl(f,buf1,fmsg);
 fclose(f);
 break;
case SCN_WRITETOFILE:
 index=substr(sstr,buf1,index,' ');
 index=substr(sstr,buf2,index,' ');
 if (!FileExist(buf1)) {
 sprintf(buf,"File not exist %s",buf1);
 write_log('!',buf);
 break;
 }
 sprintf(buf3,"Writing template %s to file %s",buf1,buf2);
 write_log('%',buf3);
 f=fopen(buf2,"wb");
 if (f==NULL) {write_log('!',"Can't create file");break;};
 WriteTpl(f,buf1,fmsg);
 fclose(f);
 break;
case SCN_EXEC:
#ifdef UNIX
 system(sstr+index);
 sprintf(buf2,"Executed '%s'",sstr+index);
 write_log('@',buf2);
#else
 index=substr(sstr,buf1,index,' ');
 if (spawnl(P_WAIT,buf1,buf1,sstr+index,NULL)==-1) {
 sprintf(buf2,"Error Executing '%s %s' error %d",buf1,sstr+index,errno);
 write_log('!',buf2);
 } else {
   sprintf(buf2,"Executed '%s %s'",buf1,sstr+index);
   write_log('@',buf2);
   }
#endif
 break;
case SCN_INFROMNAME:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (strstr(hea.FromUserName,sstr+index)!=NULL) KomRet=TRUE;}
 else {
 for(i=0;hea.FromUserName[i]!=0;i++) scrc[i]=(char)toupper(hea.FromUserName[i]);
 scrc[i]=0;
 for(i=0;sstr[i]!=0;i++) sstr[i]=(char)toupper(sstr[i]);
 sstr[i]=0;
 if (strstr(scrc,sstr+index)!=NULL) KomRet=TRUE;
 }
 break;
case SCN_INTONAME:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (strstr(hea.ToUserName,sstr+index)!=NULL) KomRet=TRUE;}
 else {
 for(i=0;hea.ToUserName[i]!=0;i++) scrc[i]=(char)toupper(hea.ToUserName[i]);
 scrc[i]=0;
 for(i=0;sstr[i]!=0;i++) sstr[i]=(char)toupper(sstr[i]);
 sstr[i]=0;
 if (strstr(scrc,sstr+index)!=NULL) KomRet=TRUE;
 }
 break;
case SCN_VIA:
 KomRetOld=KomRet;
 KomRet=F_VIA;
 break;
case SCN_MAKEPKT:
 while (TRUE) {
 i=(int)time(NULL)+mid;mid++;
#ifdef UNIX
 sprintf(buf,(strlen(config.pktout) && (config.pktout[strlen(config.pktout)-1]=='\\' || config.pktout[strlen(config.pktout)-1]=='/'))?("%s%8.8x.pkt"):("%s/%8.8x.pkt"),config.pktout,i);
#else
 sprintf(buf,(strlen(config.pktout) && (config.pktout[strlen(config.pktout)-1]=='\\' || config.pktout[strlen(config.pktout)-1]=='/'))?("%s%8.8x.pkt"):("%s\\%8.8x.pkt"),config.pktout,i);
#endif
 if (!FileExist(buf)) break;
 }
 index=substr(sstr,buf1,index,'"'); //fn
 index=substr(sstr,buf2,index,' '); //fa
 index=substr(sstr,buf3,index,'"'); //tn
 index=substr(sstr,buf4,index,' '); //ta
 index=substr(sstr,buf5,index,'"'); //s
 index=substr(sstr,buf6,index,' '); //e
 index=substr(sstr,buf7,index,' '); //tpl
 index=substr(sstr,scrc,index,' '); //pf
 if (!FileExist(buf7)) {
 sprintf(buf,"File not exist %s",buf7);
 write_log('!',buf);
 break;
 }
 f=fopen(buf,"wb");
 txt2adr(scrc,&adr);
 index=substr(sstr,scrc,index,' '); //pp
 if (!*scrc) strcpy(scrc,MachAddress(adr));
 txt2adr(scrc,&adr1);
 substr(sstr,scrc,index,' ');
 MakePKTHeader(adr1,adr,scrc,f);
 txt2adr(buf2,&adr);
 txt2adr(buf4,&adr1);
 MakePKTMsgHeaderFromTo(buf1,adr,buf3,adr1,buf5,buf6,f);
 WriteTpl(f,buf7,fmsg);
 WriteTearline(f);
 WriteOrigin(buf2,f);
 fputc(0xD,f);
 fputc(0,f);
 fputc(0,f);
 fputc(0,f);
 fclose(f);
 write_log('%',"Created PKT");
 break;
case SCN_SETSUBJ:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 strcpy(hea.Subject,sstr+index);
 fseek(fmsg,0,SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),fmsg);
 sprintf(buf,"Seting Subject : %s",sstr+index);
 write_log('#',buf);
 break;
case SCN_SETFROMNAME:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 strcpy(hea.FromUserName,sstr+index);
 fseek(fmsg,0,SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),fmsg);
 sprintf(buf,"Seting From Name : %s",sstr+index);
 write_log('#',buf);
 break;
case SCN_SETTONAME:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 strcpy(hea.ToUserName,sstr+index);
 fseek(fmsg,0,SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),fmsg);
 sprintf(buf,"Seting TO Name : %s",sstr+index);
 write_log('#',buf);
 break;
case SCN_BUSYSYSTEMFLAGS:
 BF_FLAG=TRUE;
 break;
case SCN_NOBUSYSYSTEMFLAGS:
 BF_FLAG=FALSE;
 break;
case SCN_PACK:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 /* Flavor */
 index=substr(sstr,buf,index,' ');
 if (!*buf)  { strcpy(buf,"o");
             if (IMM_F) strcpy(buf,"i");
             if (DIR_F) strcpy(buf,"d");
             if (hea.Flags&2) strcpy(buf,"c");
             if (hea.Flags&512) strcpy(buf,"h");
             } else switch (toupper(*buf)) {
                    case 'D':
                     strcpy(buf,"d");
                     break;
                    case 'C':
                     strcpy(buf,"c");
                     break;
                    case 'I':
                     strcpy(buf,"i");
                     break;
                    case 'H':
                     strcpy(buf,"h");
                     break;
                    default:
                     strcpy(buf,"o");
                    }
 /* To */
 index=substr(sstr,buf1,index,' ');
 if (!*buf1) strcpy(buf1,ToAddr);
 txt2adr(buf1,&adr);
 getdomain(buf1,scrc);
 /* From */
 index=substr(sstr,buf2,index,' ');
 if (!*buf2) strcpy(buf2,MachAddress(adr));
 txt2adr(buf2,&adr1);
 /* Pass */
 substr(sstr,buf4,index,' ');
 /***/
#ifdef __WIN32__
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) Sleep(1);
#else
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) sleep(1);
#endif
 if (BF_FLAG) BusySystemSet(adr,scrc);
 GetBinkName(adr,scrc,buf3);
 strcat(buf3,".");
 strcat(buf3,buf);
 strcat(buf3,"ut");
 f=fopen(buf3,"rb+");
 if (f==NULL) {
 f=fopen(buf3,"wb+");
 if (f==NULL) {sprintf(buf,"Can't create %s",buf3);write_log('!',buf);break;}
 MakePKTHeader(adr1,adr,buf4,f);
 } else {
   fseek(f,0,SEEK_END);
   fseek(f,ftell(f)-2,SEEK_SET);
   }
 ClearFlags(fmsg);
 MakePKTMsgHeader(f);
 SetFlags(fmsg);
 if (config.insintl && !*intl_to) fwrite(&buf4,1,sprintf(buf4,"\1INTL %u:%u/%u %u:%u/%u\r",ToAd.zone,ToAd.net,ToAd.node,FmAd.zone,FmAd.net,FmAd.node),f);
 fseek(fmsg,sizeof(HeaderType),SEEK_SET);
 while(fread(&c,1,1,fmsg)) if (*c) {fwrite(&c,1,1,f);b=*c;}else break;
 if (*c) { if (*c!=0x0A && *c!=0x0D) fputc(0x0D,f);}
 else if (b!=0x0A && b!=0x0D) fputc(0x0D,f);
 WriteVia(buf2,f);
 fputc(0,f);
 fputc(0,f);
 fputc(0,f);
 fclose(f);
 if (BF_FLAG) BusySystemUnSet(adr,scrc);
 sprintf(buf2,"Message From %s to %s Packed to %s",FromAddr,ToAddr,buf1);
 write_log('+',buf2);
 break;
case SCN_PACKPKT:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 /* Flavor */
 index=substr(sstr,buf,index,' ');
 if (!*buf)  { strcpy(buf,"f");
             if (IMM_F) strcpy(buf,"i");
             if (DIR_F) strcpy(buf,"d");
             if (hea.Flags&2) strcpy(buf,"c");
             if (hea.Flags&512) strcpy(buf,"h");
             } else switch (toupper(*buf)) {
                    case 'D':
                     strcpy(buf,"d");
                     break;
                    case 'C':
                     strcpy(buf,"c");
                     break;
                    case 'I':
                     strcpy(buf,"i");
                     break;
                    case 'H':
                     strcpy(buf,"h");
                     break;
                    default:
                     strcpy(buf,"f");
                    }
 /* To */
 index=substr(sstr,buf1,index,' ');
 if (!*buf1) strcpy(buf1,ToAddr);
 txt2adr(buf1,&adr);
 getdomain(buf1,scrc);
 /* From */
 index=substr(sstr,buf2,index,' ');
 if (!*buf2) strcpy(buf2,MachAddress(adr));
 txt2adr(buf2,&adr1);
 /* Pass */
 substr(sstr,buf4,index,' ');
 /***/
#ifdef __WIN32__
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) Sleep(1);
#else
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) sleep(1);
#endif
 if (BF_FLAG) BusySystemSet(adr,scrc);
 GetBinkName(adr,scrc,buf3);
 strcpy(buf5,buf3);
 strcat(buf3,".pkt");
 f=fopen(buf3,"rb+");
 if (f==NULL) {
 f=fopen(buf3,"wb+");
 if (f==NULL) {sprintf(buf,"Can't create %s",buf3);write_log('!',buf);break;}
 MakePKTHeader(adr1,adr,buf4,f);
 strcat(buf5,".");
 strcat(buf5,buf);
 strcat(buf5,"lo");
 f1=fopen(buf5,"a+");
 if (f1==NULL) {fclose(f);sprintf(buf,"Can't create %s",buf5);write_log('!',buf);break;}
 fputs("^",f1);
 fputs(buf3,f1);
 fputs("\n",f1);
 fclose(f1);
 } else {
   fseek(f,0,SEEK_END);
   fseek(f,ftell(f)-2,SEEK_SET);
   }
 ClearFlags(fmsg);
 MakePKTMsgHeader(f);
 SetFlags(fmsg);
 if (config.insintl && !*intl_to) fwrite(&buf4,1,sprintf(buf4,"\1INTL %u:%u/%u %u:%u/%u\r",ToAd.zone,ToAd.net,ToAd.node,FmAd.zone,FmAd.net,FmAd.node),f);
 fseek(fmsg,sizeof(HeaderType),SEEK_SET);
 while(fread(&c,1,1,fmsg)) if (*c) {fwrite(&c,1,1,f);b=*c;}else break;
 if (*c) {if (*c!=0x0A && *c!=0x0D) fputc(0x0D,f);}
 else if (b!=0x0A && b!=0x0D) fputc(0x0D,f);
 WriteVia(buf2,f);
 fputc(0,f);
 fputc(0,f);
 fputc(0,f);
 fclose(f);
 if (BF_FLAG) BusySystemUnSet(adr,scrc);
 sprintf(buf2,"Message From %s to %s Packed to %s",FromAddr,ToAddr,buf1);
 write_log('+',buf2);
 break;
case SCN_ATTACH:
 /* Flavor */
 index=substr(sstr,buf,index,' ');
 if (!*buf)  { strcpy(buf,"f");
             if (IMM_F) strcpy(buf,"i");
             if (DIR_F) strcpy(buf,"d");
             if (hea.Flags&2) strcpy(buf,"c");
             if (hea.Flags&512) strcpy(buf,"h");
             } else switch (toupper(*buf)) {
                    case 'D':
                     strcpy(buf,"d");
                     break;
                    case 'C':
                     strcpy(buf,"c");
                     break;
                    case 'I':
                     strcpy(buf,"i");
                     break;
                    case 'H':
                     strcpy(buf,"h");
                     break;
                    default:
                     strcpy(buf,"f");
                    }
 /* Address */
 index=substr(sstr,buf1,index,' ');
 if (!*buf1) strcpy(buf1,ToAddr);
 txt2adr(buf1,&adr);
 getdomain(buf1,scrc);
 /* Attribut */
 substr(sstr,buf2,index,' ');
 if (!*buf2) {if (KFS_F) strcpy(buf2,"^");
             else if (TFS_F) strcpy(buf2,"#");}
 else switch (*buf2) {
 case 'k':
 case 'K': strcpy(buf2,"^");break;
 case 't':
 case 'T': strcpy(buf2,"#");break;
 default:*buf2=0;
 }
#ifdef __WIN32__
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) Sleep(1);
#else
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) sleep(1);
#endif
 if (BF_FLAG) BusySystemSet(adr,scrc);
 GetBinkName(adr,scrc,buf3);
 strcat(buf3,".");
 strcat(buf3,buf);
 strcat(buf3,"lo");
 f=fopen(buf3,"a+");
 if (f==NULL) {sprintf(buf,"Can't create %s",buf3);write_log('!',buf);break;}
 i=substr(hea.Subject,buf3,0,' ');
 while (*buf3) {
 if (*buf2) fputc(*buf2,f);
 fnsplit(buf3,buf4,buf5,buf6,buf7);
 if (!*buf4 && !*buf5 && strlen(config.out)) {
 fwrite(config.out,1,strlen(config.out),f);
#ifdef UNIX
 if (config.out[strlen(config.out)]!='\\' && config.out[strlen(config.out)]!='/') fputc ('/',f);
#else
 if (config.out[strlen(config.out)]!='\\' && config.out[strlen(config.out)]!='/') fputc ('\\',f);
#endif
 }
 fputs(buf3,f);
 sprintf(buf,"Attached %s To %s",buf3,buf1);
 write_log('+',buf);
 fputs("\n",f);
 i=substr(hea.Subject,buf3,i,' ');
 }
 fclose(f);
 if (BF_FLAG) BusySystemUnSet(adr,scrc);
 break;
case SCN_FREQ:
 substr(sstr,buf1,index,' ');
 if (!*buf1) strcpy(buf1,ToAddr);
 txt2adr(buf1,&adr);
 getdomain(buf1,scrc);
#ifdef __WIN32__
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) Sleep(1);
#else
 if (BF_FLAG) while (BusySystemCheck(adr,scrc)) sleep(1);
#endif
 if (BF_FLAG) BusySystemSet(adr,scrc);
 GetBinkName(adr,scrc,buf3);
 strcat(buf3,".req");
 f=fopen(buf3,"a+");
 if (f==NULL) {sprintf(buf,"Can't create %s",buf3);write_log('!',buf);break;}
 i=substr(hea.Subject,buf3,0,' ');
 while (*buf3) {
 fputs(buf3,f);
 sprintf(buf,"Requested %s From %s",buf3,buf1);
 write_log('+',buf);
 fputs("\n",f);
 i=substr(hea.Subject,buf3,i,' ');
 }
 fclose(f);
 if (BF_FLAG) BusySystemUnSet(adr,scrc);
 break;
case SCN_BUSYCHECK:
 KomRetOld=KomRet;
 substr(sstr,buf1,index,' ');
 getdomain(buf1,buf2);
 txt2adr(buf1,&adr);
 KomRet=BusySystemCheck(adr,buf2);
 break;
case SCN_BUSYSET:
 substr(sstr,buf1,index,' ');
 getdomain(buf1,buf2);
 txt2adr(buf1,&adr);
 BusySystemSet(adr,buf2);
 sprintf(buf2,"Created Busy Flag for %s",buf1);
 write_log('+',buf2);
 break;
case SCN_BUSYUNSET:
 substr(sstr,buf1,index,' ');
 getdomain(buf1,buf2);
 txt2adr(buf1,&adr);
 BusySystemUnSet(adr,buf2);
 sprintf(buf2,"Killed Busy Flags for %s",buf1);
 write_log('+',buf2);
 break;
case SCN_SETPVT:
 SetFlag(fmsg,1,"PVT");
 break;
case SCN_CLEARPVT:
 ClearFlag(fmsg,1,"PVT");
 break;
case SCN_SETCRA:
 SetFlag(fmsg,2,"CRA");
 break;
case SCN_CLEARCRA:
 ClearFlag(fmsg,2,"CRA");
 break;
case SCN_SETRCV:
 SetFlag(fmsg,4,"RCV");
 break;
case SCN_CLEARRCV:
 ClearFlag(fmsg,4,"RCV");
 break;
case SCN_SETSNT:
 SetFlag(fmsg,8,"SNT");
 break;
case SCN_CLEARSNT:
 ClearFlag(fmsg,8,"SNT");
 break;
case SCN_SETATT:
 SetFlag(fmsg,16,"ATT");
 break;
case SCN_CLEARATT:
 ClearFlag(fmsg,16,"ATT");
 break;
case SCN_SETTRS:
 SetFlag(fmsg,32,"TRS");
 break;
case SCN_CLEARTRS:
 ClearFlag(fmsg,32,"TRS");
 break;
case SCN_SETORP:
 SetFlag(fmsg,64,"ORP");
 break;
case SCN_CLEARORP:
 ClearFlag(fmsg,64,"ORP");
 break;
case SCN_SETKS:
 SetFlag(fmsg,128,"K/S");
 break;
case SCN_CLEARKS:
 ClearFlag(fmsg,128,"K/S");
 break;
case SCN_SETLOC:
 SetFlag(fmsg,256,"LOC");
 break;
case SCN_CLEARLOC:
 ClearFlag(fmsg,256,"LOC");
 break;
case SCN_SETHLD:
 SetFlag(fmsg,512,"HLD");
 break;
case SCN_CLEARHLD:
 ClearFlag(fmsg,512,"HLD");
 break;
case SCN_SETFRQ:
 SetFlag(fmsg,2048,"FRQ");
 break;
case SCN_CLEARFRQ:
 ClearFlag(fmsg,2048,"FRQ");
 break;
case SCN_SETRRQ:
 SetFlag(fmsg,4096,"RRQ");
 break;
case SCN_CLEARRRQ:
 ClearFlag(fmsg,4096,"RRQ");
 break;
case SCN_SETRCC:
 SetFlag(fmsg,8192,"RRC");
 break;
case SCN_CLEARRRC:
 ClearFlag(fmsg,8192,"RRC");
 break;
case SCN_SETARQ:
 SetFlag(fmsg,16384,"ARQ");
 break;
case SCN_CLEARARQ:
 ClearFlag(fmsg,16384,"ARQ");
 break;
case SCN_SETURQ:
 SetFlag(fmsg,(unsigned)32768l,"URQ");
 break;
case SCN_CLEARURQ:
 ClearFlag(fmsg,(unsigned)32768l,"URQ");
 break;
case SCN_BOUNCE:
 sprintf(scrc,"%s%s",Drive,Dir);
 if (!*scrc) strcpy(scrc,".");
 f=NewMsg(scrc,buf);
 if (f==NULL) {
 write_log('!',"Can't Create New Message");
 break;
 }
 substr(sstr,buf1,index,' ');
 getdomain(FromAddr,scrc);
 txt2adr(MachAddress(FmAd),&adr);
 MakeMsgHeader("MNTrack",adr,hea.FromUserName,FmAd,"Bounced message",scrc,f);
 WriteTpl(f,buf1,fmsg);
 WriteTearline(f);
 fclose(f);
 sprintf(scrc,"Bounced to %s",FromAddr);
 write_log('#',scrc);
 break;
case SCN_FORWARD:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 index=substr(sstr,buf1,index,' ');
 index=substr(sstr,buf2,index,' ');
 //substr(sstr,buf3,index,' ');
 if (*(sstr+index)) strcpy(buf3,sstr+index);
 else *buf3=0;
 if (!*buf3) strcpy(buf3,"SysOp");
 sprintf(scrc,"%s%s",Drive,Dir);
 if (!*scrc) strcpy(scrc,".");
 f=NewMsg(scrc,buf);
 if (f==NULL) {
 write_log('!',"Can't Create New Message");
 break;
 }
 txt2adr(buf1,&adr1);
 txt2adr(MachAddress(adr1),&adr);
 getdomain(MachAddress(adr1),scrc);
 MakeMsgHeader("MNTrack",adr,buf3,adr1,hea.Subject,scrc,f);
 if (!WriteTpl(f,buf2,fmsg)) WriteTpl(f,"fwd.tpl",fmsg);
 WriteBody(f,fmsg,TRUE,TRUE);
 WriteTearline(f);
 fclose(f);
 sprintf(scrc,"Forwarded to %s",buf1);
 write_log('#',scrc);
 break;
case SCN_MAKEMSG:
 index=substr(sstr,buf5,index,'"');  //fn
 index=substr(sstr,buf1,index,' ');  //fa
 txt2adr(buf1,&adr);
 getdomain(buf1,buf3);
 index=substr(sstr,buf6,index,'"'); //tn
 index=substr(sstr,buf2,index,' '); //ta
 txt2adr(buf2,&adr1);
 index=substr(sstr,buf7,index,'"'); //subj
 substr(sstr,buf4,index,' ');       //tpl
 if (!FileExist(buf4)) {
 sprintf(buf,"File not exist %s",buf4);
 write_log('!',buf);
 break;
 }
 sprintf(scrc,"%s%s",Drive,Dir);
 if (!*scrc) strcpy(scrc,".");
 f=NewMsg(scrc,buf);
 if (f==NULL) {
 write_log('!',"Can't Create New Message");
 break;
 }
 MakeMsgHeader(buf5,adr,buf6,adr1,buf7,buf3,f);
 WriteTpl(f,buf4,fmsg);
 WriteTearline(f);
 fclose(f);
 write_log('#',"Created Message");
 break;
case SCN_MOVE:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 if ((f=NewMsg(sstr+index,scrc))==NULL) {
 write_log('!',"Can't move message");
 break;
 }
 fseek(fmsg,sizeof(HeaderType),SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),f);
 while(fread(&i,1,1,fmsg)) fwrite(&i,1,1,f);
 fclose(f);
 fclose(fmsg);
 sprintf(sstr,"Moved to %s",scrc);
 write_log('#',sstr);
 if (unlink(FileName)==-1) write_log('!',"Permision denied to delete message file");
 F_CLOSED=TRUE;
 break;
case SCN_COPY:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 if ((f=NewMsg(sstr+index,scrc))==NULL) {
 write_log('!',"Can't copy message");
 break;
 }
 fseek(fmsg,sizeof(HeaderType),SEEK_SET);
 fwrite(&hea,1,sizeof(HeaderType),f);
 while(fread(&i,1,1,fmsg)) fwrite(&i,1,1,f);
 fclose(f);
 sprintf(sstr,"Copied to %s",scrc);
 write_log('#',sstr);
 break;
case SCN_SEMAPHORE:
 f=fopen(sstr+index,"wb+");
 if (f!=NULL) {
 fclose(f);
 sprintf(scrc,"Creating Semaphore %s",sstr+index);
 write_log('&',scrc);
 }
 else {
 sprintf(scrc,"Can't Create %s",sstr+index);
 write_log('!',scrc);
 }
 break;
case SCN_DELETE:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 fclose(fmsg);
 if (unlink(FileName)==-1) write_log('!',"Can't erase message file");
 else write_log('#',"Erased");
 F_CLOSED=TRUE;
 break;
case SCN_DELETEATTACH:
 index=substr(hea.Subject,scrc,0,' ');
 while (*scrc) {
 if (unlink(scrc)==-1) {
 sprintf(sstr,"Can't erase %s",scrc);
 write_log('!',sstr);
 } else {
   sprintf(sstr,"Erased %s",scrc);
   write_log('#',sstr);
   }
 index=substr(hea.Subject,scrc,index,' ');
 }
 break;
case SCN_PVT:
 KomRetOld=KomRet;
 KomRet=hea.Flags&1;
 break;
case SCN_CRA:
 KomRetOld=KomRet;
 KomRet=hea.Flags&2;
 break;
case SCN_RCV:
 KomRetOld=KomRet;
 KomRet=hea.Flags&4;
 break;
case SCN_SNT:
 KomRetOld=KomRet;
 KomRet=hea.Flags&8;
 break;
case SCN_ATT:
 KomRetOld=KomRet;
 KomRet=hea.Flags&16;
 break;
case SCN_TRS:
 KomRetOld=KomRet;
 KomRet=hea.Flags&32;
 break;
case SCN_ORP:
 KomRetOld=KomRet;
 KomRet=hea.Flags&64;
 break;
case SCN_KS:
 KomRetOld=KomRet;
 KomRet=hea.Flags&128;
 break;
case SCN_LOC:
 KomRetOld=KomRet;
 KomRet=hea.Flags&256;
 break;
case SCN_HLD:
 KomRetOld=KomRet;
 KomRet=hea.Flags&512;
 break;
case SCN_FRQ:
 KomRetOld=KomRet;
 KomRet=hea.Flags&2048;
 break;
case SCN_RRQ:
 KomRetOld=KomRet;
 KomRet=hea.Flags&4096;
 break;
case SCN_RRC:
 KomRetOld=KomRet;
 KomRet=hea.Flags&8192;
 break;
case SCN_ARQ:
 KomRetOld=KomRet;
 KomRet=hea.Flags&16384;
 break;
case SCN_URQ:
 KomRetOld=KomRet;
 KomRet=hea.Flags&32768l;
 break;
case SCN_ZON:
 KomRetOld=KomRet;
 KomRet=ZON_F;
 break;
case SCN_DIR:
 KomRetOld=KomRet;
 KomRet=DIR_F;
 break;
case SCN_LOK:
 KomRetOld=KomRet;
 KomRet=LOK_F;
 break;
case SCN_KFS:
 KomRetOld=KomRet;
 KomRet=KFS_F;
 break;
case SCN_CFM:
 KomRetOld=KomRet;
 KomRet=CFM_F;
 break;
case SCN_XMA:
 KomRetOld=KomRet;
 KomRet=XMA_F;
 break;
case SCN_IMM:
 KomRetOld=KomRet;
 KomRet=IMM_F;
 break;
case SCN_TFS:
 KomRetOld=KomRet;
 KomRet=TFS_F;
 break;
case SCN_AS:
 KomRetOld=KomRet;
 KomRet=AS_F;
 break;
case SCN_HUB:
 KomRetOld=KomRet;
 KomRet=HUB_F;
 break;
case SCR_UUE:
 KomRetOld=KomRet;
 if (uued>config.uuedepth) KomRet=TRUE; else KomRet=FALSE;
 break;
case SCR_EMPTY:
 KomRetOld=KomRet;
 KomRet=F_EMPTY;
 break;
case SCR_INBODY:
 if (F_CLOSED) {
 write_log('!',"Message file does not exist");
 break;
 }
 KomRetOld=KomRet;
 KomRet=FALSE;
 fseek(fmsg,sizeof(HeaderType),SEEK_SET);
 if (!CaseS) for(i=0;sstr[i]!=0;i++) sstr[i]=(char)toupper(sstr[i]);
 while (fgets(scrc,255,fmsg)!=NULL) {
 if (!CaseS) for(i=0;scrc[i]!=0;i++) scrc[i]=(char)toupper(scrc[i]);
 if (strstr(scrc,sstr+index)!=NULL) {KomRet=TRUE;break;}
 }
 break;
case SCR_MSGSIZE:
 KomRetOld=KomRet;
 fseek(fmsg,0,SEEK_END);
 substr(sstr,scrc,index,'\0');
 if (atol(scrc)>ftell(fmsg)) KomRet=TRUE; else KomRet=FALSE;
 break;
case SCR_LOOP:
 KomRetOld=KomRet;
 KomRet=F_Loop;
 break;
case SCR_DUPE:
 KomRetOld=KomRet;
 KomRet=F_Dupe;
 break;
case SCR_INTL:
 KomRetOld=KomRet;
 if (*intl_to) KomRet=TRUE; else  KomRet=FALSE;
 break;
case SCR_MSGID:
 KomRetOld=KomRet;
 if (*msgid) KomRet=TRUE; else  KomRet=FALSE;
 break;
case SCR_TOLISTED:
 KomRetOld=KomRet;
 KomRet=CheckAddress(ToAd);
 break;
case SCR_FROMLISTED:
 KomRetOld=KomRet;
 KomRet=CheckAddress(FmAd);
 break;
case SCR_FROMADR:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 txt2adr(scrc,&adr);
 if (FmAd.zone==adr.zone && FmAd.net==adr.net && FmAd.node==adr.node && FmAd.point==adr.point) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_FROMADR3D:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 txt2adr(scrc,&adr);
 if (FmAd.zone==adr.zone && FmAd.net==adr.net && FmAd.node==adr.node) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TOADR:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 txt2adr(scrc,&adr);
 if (ToAd.zone==adr.zone && ToAd.net==adr.net && ToAd.node==adr.node && ToAd.point==adr.point) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TOADR3D:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 txt2adr(scrc,&adr);
 if (ToAd.zone==adr.zone && ToAd.net==adr.net && ToAd.node==adr.node) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TOZONE:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (ToAd.zone==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TONET:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (ToAd.net==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TONODE:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (ToAd.node==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_TOPOINT:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (ToAd.point==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_FROMZONE:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (FmAd.zone==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_FROMNET:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (FmAd.net==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_FROMNODE:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (FmAd.node==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_FROMPOINT:
 KomRetOld=KomRet;
 KomRet=FALSE;
 index=substr(sstr,scrc,index,' ');
 while (*scrc) {
 if (FmAd.point==atoi(scrc)) {KomRet=TRUE;break;}
 index=substr(sstr,scrc,index,' ');
 }
 break;
case SCR_SUBJ:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (!strcmp(sstr+index,hea.Subject)) KomRet=TRUE;}
 else if (!stricmp(sstr+index,hea.Subject)) KomRet=TRUE;
 break;
case SCR_INSUBJ:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (strstr(hea.Subject,sstr+index)!=NULL) KomRet=TRUE;}
 else {
 for(i=0;hea.Subject[i]!=0;i++) scrc[i]=(char)toupper(hea.Subject[i]);
 scrc[i]=0;
 for(i=0;sstr[i]!=0;i++) sstr[i]=(char)toupper(sstr[i]);
 sstr[i]=0;
 if (strstr(scrc,sstr+index)!=NULL) KomRet=TRUE;
 }
 break;
case SCR_TONAME:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (!strcmp(sstr+index,hea.ToUserName)) KomRet=TRUE;}
 else if (!stricmp(sstr+index,hea.ToUserName)) KomRet=TRUE;
 break;
case SCR_FROMNAME:
 KomRetOld=KomRet;
 KomRet=FALSE;
 if (CaseS) {if (!strcmp(sstr+index,hea.FromUserName)) KomRet=TRUE;}
 else if (!stricmp(sstr+index,hea.FromUserName)) KomRet=TRUE;
 break;
case SCR_BREAK:
 BreakF=TRUE;
 break;
case SCR_NOBREAK:
 BreakF=FALSE;
 break;
case SCR_NOCASE:
 CaseS=FALSE;
 break;
case SCR_REALCASE:
 CaseS=TRUE;
 break;
case SCR_QUIT:
 fclose(fscr);
 return;
case SCR_GOTO:
 fseek(fscr,0,SEEK_SET);
 while(TRUE) {
 if (fgets(scrc,255,fscr)==NULL) {
 sprintf(scrc,"Label %s no found",sstr+index);
 write_log('!',scrc);
 fclose(fscr);
 return;
 }
 if (scrc[0]!=':') continue;
 while (strlen(scrc)>0 && (scrc[strlen(scrc)-1]==0xD || scrc[strlen(scrc)-1]==0xA || scrc[strlen(scrc)-1]==' ')) scrc[strlen(scrc)-1]=0;
 if (CaseS) {if (!strcmp(scrc+1,sstr+index)) break;}
 else if (!stricmp(scrc+1,sstr+index)) break;
 }
 break;
case SCR_JE:
 if (!KomRet) break;
 fseek(fscr,0,SEEK_SET);
 while(TRUE) {
 if (fgets(scrc,255,fscr)==NULL) {
 sprintf(scrc,"Label %s no found",sstr+index);
 write_log('!',scrc);
 fclose(fscr);
 return;
 }
 if (scrc[0]!=':') continue;
 while (strlen(scrc)>1 && (scrc[strlen(scrc)-1]==0xD || scrc[strlen(scrc)-1]==0xA || scrc[strlen(scrc)-1]==' ')) scrc[strlen(scrc)-1]=0;
 if (CaseS) {if (!strcmp(scrc+1,sstr+index)) break;}
 else if (!stricmp(scrc+1,sstr+index)) break;
 }
 break;
case SCR_JNE:
 if (KomRet) break;
 fseek(fscr,0,SEEK_SET);
 while(TRUE) {
 if (fgets(scrc,255,fscr)==NULL) {
 sprintf(scrc,"Label %s no found",sstr+index);
 write_log('!',scrc);
 fclose(fscr);
 return;
 }
 if (scrc[0]!=':') continue;
 while (strlen(scrc)>1 && (scrc[strlen(scrc)-1]==0xD || scrc[strlen(scrc)-1]==0xA || scrc[strlen(scrc)-1]==' ')) scrc[strlen(scrc)-1]=0;
 if (CaseS) {if (!strcmp(scrc+1,sstr+index)) break;}
 else if (!stricmp(scrc+1,sstr+index)) break;
 }
 break;
case SCR_OUTLOG:
 substr(sstr,scrc,index,'\0');
 write_log('-',scrc);
 break;
case SCR_LOGSTART:
 substr(sstr,MesPrev,index,'\0');
 break;
case SCR_LOGEND:
 substr(sstr,MesPost,index,'\0');
 break;
case SCR_LOGDROP:
 *MesPrev=0;
 *MesPost=0;
 break;
/* Unknown */
default:
 sprintf(sstr,"Unknown command '%s' in script %s",scrc,TScr->scr.name);
 write_log('!',sstr);
 fclose(fscr);
 return;
} /* switch */
} /* while */
fclose(fscr);
#ifdef DEBUG
write_log('~',"<-ParseSingleScript");
#endif
}
/* Parse scripts on message */
void ParseScripts(FILE *fmsg)
{
TScr=FScr;
#ifdef DEBUG
write_log('~',"->ParseScripts");
#endif
while(TScr!=NULL) {
ParseSingleScript(fmsg);
if (config.stop==2 && F_CLOSED) break;
TScr=TScr->next;
}
#ifdef DEBUG
write_log('~',"<-ParseScripts");
#endif
}
/* Scan single file */
void scanfile(void)
{
FILE *msgf;
static char b[3],msgbuf[FIDOMsgMaxStringLen+1],klubuf[255],lbuf[255],lbuf1[255];
char *c;
int index,ind;
static Adr4D adr;
BOOL_1 F_UUE;
#ifdef DEBUG
write_log('~',"->scanfile");
#endif
msgf=fopen(FileName,"rb+");
if (msgf==NULL) {
write_log('!',"Can't open this message");
return;
}
fread(&hea,1,sizeof(HeaderType),msgf);
*msgbuf=0;*klubuf=0;*fmpt=0;*topt=0;*msgid=0;
*intl_to=0;*intl_from=0;*b=0;
F_CLOSED=FALSE;
F_EMPTY=TRUE;
F_VIA=FALSE;
F_Dupe=FALSE;
F_Loop=FALSE;
uued=0;
 ZON_F=FALSE;DIR_F=FALSE;
 LOK_F=FALSE;KFS_F=FALSE;
 CFM_F=FALSE;XMA_F=FALSE;
 IMM_F=FALSE;TFS_F=FALSE;
 AS_F=FALSE;HUB_F=FALSE;
while (TRUE) {
if (strlen(msgbuf)<FIDOMsgMaxStringLen) {
if (fread(&b,1,1,msgf)==0) break;
if (*b==0xA) continue;
if (*b==0) break;
if (*b!=0xD) {strcat(msgbuf,b);continue;}
if (!*msgbuf) continue;
}
if (*msgbuf==1) {
/* Kludjes */
index=substr(msgbuf,klubuf,1,' ');
#ifdef DEBUG
sprintf(lbuf,"Kludge : '%s'",klubuf);
write_log('~',lbuf);
#endif
switch(GetToken(KludgTokens,klubuf,0,TRUE)){
case K_INTL:
 index=substr(msgbuf,intl_to,index,' ');
 substr(msgbuf,intl_from,index,' ');
 break;
case K_TOPT:
 substr(msgbuf,topt,index,' ');
 break;
case K_FMPT:
 substr(msgbuf,fmpt,index,' ');
 break;
case K_FLAGS:
 while (TRUE) {
 index=substr(msgbuf,lbuf,index,' ');
 if (!*lbuf) break;
 switch(GetToken(FlagsTokens,lbuf,0,TRUE)) {
 case FL_ZON:
  ZON_F=TRUE;
  break;
 case FL_DIR:
  DIR_F=TRUE;
  break;
 case FL_LOK:
  LOK_F=TRUE;
  break;
 case FL_KFS:
  KFS_F=TRUE;
  break;
 case FL_CFM:
  CFM_F=TRUE;
  break;
 case FL_XMA:
  XMA_F=TRUE;
  break;
 case FL_IMM:
  IMM_F=TRUE;
  break;
 case FL_TFS:
  TFS_F=TRUE;
  break;
 case FL_AS:
  AS_F=TRUE;
  break;
 case FL_HUB:
  HUB_F=TRUE;
  break;
 default:
  ind=0;
  while (TRUE) {
  ind=substr(config.flags,lbuf1,ind,',');
  if (!*lbuf1) break;
  if (!strcmp(lbuf1,lbuf)) goto knownflg;
  }
  sprintf(lbuf1,"Unknown flag %s",lbuf);
  write_log('^',lbuf1);
  knownflg:
  break;
 } /* switch */
 } /* while */
 break;
case K_MSGID:
 substr(msgbuf,msgid,index,' ');
 /* Dupe Checking */
 if (FBas==NULL) {
 if ((TBas=farcalloc(1,sizeof(DupeBase)))==NULL) {
 write_log('!',"Not Enough memmory to add dupe base record\n");
 exit_mntrack(2);
 }
 TBas->next=NULL;
 TBas->duperec=farcalloc(1,strlen(msgbuf)+1);
 strcpy(TBas->duperec,msgbuf);
 FBas=TBas;
 } else {
   TBas=FBas;
    while (TRUE) if (strcmp(TBas->duperec,msgbuf)) {
                         if (TBas->next==NULL) {
                         /* Add new dupe record */
                         PBas=TBas;
                         if ((TBas=farcalloc(1,sizeof(DupeBase)))==NULL) {
                         write_log('!',"Not Enough memmory to add dupe base record\n");
                         exit_mntrack(2);
                         }
                         TBas->next=NULL;
                         TBas->duperec=farcalloc(1,strlen(msgbuf)+1);
                         strcpy(TBas->duperec,msgbuf);
                         PBas->next=TBas;
                         break;
                         } else TBas=TBas->next;
                 } else {
                   /* Dupe Detected */
                   F_Dupe=TRUE;
                   break;
                   }
   }
 break;
case K_Via:
 F_VIA=TRUE;
 /* Loop Checking */
 if (F_Loop) break;
 ind=substr(msgbuf,lbuf,5,' ');
 substr(lbuf,lbuf1,0,'@');
 ind=substr(msgbuf,lbuf,ind,' ');
 if (strncmp(msgbuf+ind,"MNTrack",7)) break;
 if (!stricmp(lbuf1,config.bouadr)) {F_Loop=TRUE;break;}
 TAKA=FAKA;
 while(TAKA!=NULL) {
 if (!stricmp(lbuf1,TAKA->addr)) {F_Loop=TRUE;break;}
 TAKA=(AKAType *)TAKA->next;
 }
 break;
default: break;
}
} else {
  /* Process not kludge line */
  F_EMPTY=FALSE;
  if (*msgbuf=='M' && strlen(msgbuf)>15) {
   F_UUE=TRUE;
   if ((c=strchr(msgbuf,' '))!=NULL) while (*c && F_UUE) if (*c!=' ') F_UUE=FALSE; else c++;
   c=msgbuf;
   while (*c && F_UUE) if (((unsigned char)*c)>96) F_UUE=FALSE; else c++;
   if (F_UUE) uued++;
  } /* UUE */
  } /* not kludge lines */
*msgbuf=0;
}
/* Calculate From Address */
adr.zone=0;
if (*msgid!=0) txt2adr(msgid,&adr);
else write_log('^',"No MSGID Kludge");
if (*intl_from!=0) strcpy(FromAddr,intl_from);
else sprintf(FromAddr,"%u:%u/%u",adr.zone,hea.OrigNet,hea.OrigNode);
if (*fmpt!=0) {
strcat(FromAddr,".");
strcat(FromAddr,fmpt);
}
txt2adr(FromAddr,&FmAd);
if (!CheckAddress(FmAd)) write_log('^',"Unlisted From Address");
/* Calculate To Address */
if (*intl_to!=0) strcpy(ToAddr,intl_to);
else {
write_log('^',"No INTL Kludge");
sprintf(ToAddr,"%u:%u/%u",FmAd.zone,hea.DestNet,hea.DestNode);
}
if (*topt!=0) {
strcat(ToAddr,".");
strcat(ToAddr,topt);
}
txt2adr(ToAddr,&ToAd);
if (!CheckAddress(ToAd)) write_log('^',"Unlisted To Address");
ParseScripts(msgf);
if (!F_CLOSED) fclose(msgf);
F_CLOSED=TRUE;
#ifdef DEBUG
write_log('~',"<-scanfile");
#endif
}
/* Main Program Entry Point */
int main(int argc,char *argv[])
{
static int i;
static char dbuf[255];
#ifdef __WIN32__
WIN32_FIND_DATA fd;
HANDLE          sh;
static UINT     oldmode;
#else
struct ffblk fblock;
#endif

#ifdef __WATCOMC__
tzset();
#endif

printf("MNTrack %s Copyright (C) 1996-02 Nicol Morozov 2:5020/991\n",version);
/* Check busy */
/*
if (FileExist("mntrack.bsy")) {
printf("MNTrack is busy\n");
exit(0);
}
fclose(fopen("mntrack.bsy","w"));
*/
/* Command line arguments */
if (argc>1) for (i=1;i<argc;i++)
switch(GetToken(ArgTokens,argv[i],0,FALSE)){
case 0:
 printf("Unknown command line argument : %s\nTry MNTRACK /H.\n",argv[i]);
 exit_mntrack(3);
case ARG_HELP:
 printf("Command line arguments:\n");
 printf(" /H - Display this help message.\n");
 printf(" /Q - Quiet mode.\n");
 printf(" /F <mask> - Scan files using <mask> instead of configuration file mask.\n");
 printf(" /S <script> - Execute only one script <script>.\n");
 printf(" /U <fromdir> <todir> - Unpack PKT from directory <fromdir> to directory <todir>.\n");
 exit_mntrack(0);
case ARG_QUIET:
 F_Quiet=TRUE;
 break;
case ARG_SCAN:
case ARG_SCR:
 i++;
 break;
case ARG_UNPKT:
 i+=2;
 break;
}
LoadConfig();
if (argc>1) for (i=1;i<argc;i++)
switch(GetToken(ArgTokens,argv[i],0,FALSE)){
case ARG_SCAN:
 i++;
 strcpy(config.scanfiles,argv[i]);
 break;
case ARG_SCR:
 i++;
 if ((FScr=farcalloc(1,sizeof(ScriptRec)))==NULL) {
 write_log('!',"Not Enough memmory.");
 exit_mntrack(2);
 }
 FScr->next=NULL;
 strcpy(FScr->scr.name,argv[i]);
 break;
case ARG_UNPKT:
 UnPackPKT(argv[i+1],argv[i+2]);
 i+=2;
 break;
}
/* Find and Scan Files */
fnsplit(config.scanfiles,Drive,Dir,Name,Ext);
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(config.scanfiles,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh==INVALID_HANDLE_VALUE) write_log('^',"Nothing to do");
else while (TRUE){
sprintf(FileName,"%s%s%s",Drive,Dir,fd.cFileName);
#else
if (findfirst((char *)&config.scanfiles,&fblock,ATTRIB)!=-1) while (TRUE) {
sprintf(FileName,"%s%s%s",Drive,Dir,fblock.ff_name);
#endif
F_CR=TRUE;
if (!F_Quiet) {
printf("\r");
for(i=1;i<80;i++) printf(" ");
printf("\rScaning : %s",FileName);
sprintf(dbuf,"Scaning : %s",FileName);
write_log('~',dbuf);
}
scanfile();
#ifdef __WIN32__
if (!FindNextFile(sh,&fd)) break;
}
FindClose(sh);
#else
if (findnext(&fblock)==-1) break;
} else write_log('^',"Nothing to do");
#endif
#ifdef DEBUG
write_log('~',"Finishing");
#endif
printf("\n");
unlink("mntrack.bsy");
return 0;
}
