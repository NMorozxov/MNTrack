#include "mntrnc.h"
#include "version.h"
FILE *ndx;
static char FileName[255];
static UINT_2 Zone=0,Net=0,Node=0;
static TokenTable CTLTokens[]={
	   {"NODELIST",CTL_NODELIST},
       {"NODELISTMASK",CTL_NODELISTMASK},
       {"NODELISTMASKNUMERIC",CTL_NODELISTMASKNUMERIC},
       {"NODELISTSEGMENT",CTL_NODELISTSEGMENT},
       {"ADDRESS",CTL_ADDRESS},
	   {"",0}};
void add(void)
{
Adr4D adr;
adr.zone=Zone;
adr.net=Net;
adr.node=Node;
adr.point=0;
fwrite(&adr,1,sizeof(adr),ndx);
printf("\r");
printf("Adding to Index : Zone:%-4.4d Net:%-4.4d Node:%-5.5d",Zone,Net,Node);
}
void compile(void)
{
FILE *f;
static char buf[255],buf1[255];
static int index;
#ifdef __WIN32__
static int oldmode;
#endif
static TokenTable NodelistTokens[]={
	   {"Zone",NDL_ZONE},
	   {"Region",NDL_REGION},
	   {"Host",NDL_HOST},
	   {"Hub",NDL_HUB},
	   {"Pvt",NDL_PVT},
	   {"Down",NDL_DOWN},
	   {"Hold",NDL_HOLD},
	   {"",0}};

printf("Compiling nodelist : %s\n",FileName);
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { f=fopen(FileName,"r"); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
#else
f=fopen(FileName,"r");
#endif
if (f==NULL) {printf("Can't open %s\n",FileName);return;}
while(fgets(buf,255,f)!=NULL) {
index=substr(buf,buf1,0,',');
if (*buf==';' || *buf==0xA || *buf==0xD) continue;
if (*buf==',') {
Node=(UINT_2)atoi(buf1);
add();
} else switch(GetToken(NodelistTokens,buf1,0,TRUE)){
       case NDL_ZONE:
	substr(buf,buf1,index,',');
	Zone=(UINT_2)atoi(buf1);
	Net=0;
	Node=0;
	add();
	break;
       case NDL_REGION:
       case NDL_HOST:
	substr(buf,buf1,index,',');
	Net=(UINT_2)atoi(buf1);
	Node=0;
	add();
	break;
       case NDL_HUB:
       case NDL_PVT:
       case NDL_DOWN:
       case NDL_HOLD:
	substr(buf,buf1,index,',');
	Node=(UINT_2)atoi(buf1);
	add();
	break;
       default:
	printf("Unknown nodelist prefix : %s\n",buf1);
       }
}
printf("\n");
fclose(f);
}
int main(int argc,char *argv[])
{
Adr4D adr;
FILE   *ctl=fopen("mntrnc.ctl","r");
static char buf[255],buf1[255];
static char Drive[3],Dir[255],Name[255],Ext[255];
static char Drive1[3],Dir1[255],Name1[255],Ext1[255];
static int i,index;
static TokenTable ArgTokens[]={
	   {"/H",ARG_HELP},
	   {"",0}};
#ifdef __WIN32__
WIN32_FIND_DATA fd;
HANDLE          sh;
static int      oldmode;
#else
struct ffblk fblock;
#endif

printf("MNTrack %s Nodelist Compiler (C) 1996-98 Nicol Morozov 2:5020/991\n",version);
/* Check busy */
if (FileExist("mntrack.bsy")) {
printf("MNTrack is busy\n");
exit(0);
}
fclose(fopen("mntrack.bsy","w"));
/* Command line Arguments */
if (argc>1) for (i=1;i<argc;i++) {
switch(GetToken(ArgTokens,argv[i],0,FALSE)){
case 0:
 printf("Unknown command line argument : %s\nTry MNTRNC /H.\n",argv[i]);
 exit_mntrack(3);
case ARG_HELP:
 printf("Command line arguments:\n");
 printf(" /H - Display this help message\n");
 exit_mntrack(0);
}
}
if (ctl==NULL) {printf("Can't open mntrnc.ctl\n");exit_mntrack(1);}
if ((ndx=fopen("mntrack.ndx","wb"))==NULL) {printf("Can't create mntrack.ndx\n");exit_mntrack(1);}
while(fgets(buf,255,ctl)!=NULL) {
while (strlen(buf)>0 && (buf[strlen(buf)-1]==0xD || buf[strlen(buf)-1]==0xA || buf[strlen(buf)-1]==' ')) buf[strlen(buf)-1]=0;
if (!*buf || *buf==';') continue; 
index=substr(buf,buf1,0,' ');
switch(GetToken(CTLTokens,buf1,0,FALSE)) {
case CTL_NODELIST:
strcpy(FileName,buf+index);
compile();
break;
case CTL_NODELISTMASK:
fnsplit(buf+index,Drive,Dir,Name,Ext);
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(buf+index,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh==INVALID_HANDLE_VALUE) printf("Nodelists %s not found\n",buf+index);
else while (TRUE){
sprintf(FileName,"%s%s%s",Drive,Dir,fd.cFileName);
fnsplit(fd.cFileName,Drive1,Dir1,Name1,Ext1);
#else
if (findfirst(buf+index,&fblock,ATTRIB)!=-1) while (TRUE) {
sprintf(FileName,"%s%s%s",Drive,Dir,fblock.ff_name);
fnsplit(fblock.ff_name,Drive1,Dir1,Name1,Ext1);
#endif
compile();
#ifdef __WIN32__
if (!FindNextFile(sh,&fd)) break;
}
FindClose(sh);
#else
if (findnext(&fblock)==-1) break;
} else printf("Nodelists %s not found\n",buf+index);
#endif
break;
case CTL_NODELISTMASKNUMERIC:
fnsplit(buf+index,Drive,Dir,Name,Ext);
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { sh = FindFirstFile(buf+index,&fd); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
if (sh==INVALID_HANDLE_VALUE) printf("Nodelists %s not found\n",buf+index);
else while (TRUE){
sprintf(FileName,"%s%s%s",Drive,Dir,fd.cFileName);
fnsplit(fd.cFileName,Drive1,Dir1,Name1,Ext1);
#else
if (findfirst(buf+index,&fblock,ATTRIB)!=-1) while (TRUE) {
sprintf(FileName,"%s%s%s",Drive,Dir,fblock.ff_name);
fnsplit(fblock.ff_name,Drive1,Dir1,Name1,Ext1);
#endif
if (atoi(Ext1+1) || !strcmp(Ext1,".0") || !strcmp(Ext1,".00") || !strcmp(Ext1,".000")) compile();
#ifdef __WIN32__
if (!FindNextFile(sh,&fd)) break;
}
FindClose(sh);
#else
if (findnext(&fblock)==-1) break;
} else printf("Nodelists %s not found\n",buf+index);
#endif
break;
case CTL_NODELISTSEGMENT:
index=substr(buf,buf1,index,' ');
txt2adr(buf1,&adr);
Zone=adr.zone;
Net=adr.net;
Node=adr.node;
strcpy(FileName,buf+index);
compile();
break;
case CTL_ADDRESS:
index=substr(buf,buf1,index,' ');
txt2adr(buf1,&adr);
Zone=adr.zone;
Net=adr.net;
Node=adr.node;
add();
break;
default:
printf("Error : Unknown Nodelist Command : %s\n",buf1);
} /* switch */
} /* while */
fclose(ctl);
fclose(ndx);

printf("\n");
unlink("mntrack.bsy");
return 0;
}
