#include "bink.h"
#ifdef __MSDOS__
extern DmnRec far *FDmn;
extern DmnRec far *TDmn;
extern DmnRec far *PDmn;
#else
extern DmnRec *FDmn;
extern DmnRec *TDmn;
extern DmnRec *PDmn;
#endif

/* Get Outbound from address */
void GetOutbound(const Adr4D adr,char * domain,char * name)
{
static int index;
static char buf[255];
#ifdef DEBUG
write_log('~',"->GetOutbound");
#endif
TDmn=FDmn;
while(TDmn!=NULL) {
if (!stricmp(TDmn->dmn.name,domain)) {
sprintf(name,(TDmn->dmn.HaveMainZone && adr.zone==TDmn->dmn.MainZone)?("%s"):("%s.%3.3x"),TDmn->dmn.out,adr.zone);
#ifdef DEBUG
write_log('~',"<-GetOutbound Exit 1");
#endif
return;
}
TDmn=TDmn->next;
}

TDmn=FDmn;
while(TDmn!=NULL) {
index=substr(TDmn->dmn.zones,buf,0,',');
while (*buf) {
if (atoi(buf)==adr.zone) {
sprintf(name,(TDmn->dmn.HaveMainZone && adr.zone==TDmn->dmn.MainZone)?("%s"):("%s.%3.3x"),TDmn->dmn.out,adr.zone);
#ifdef DEBUG
write_log('~',"<-GetOutbound Exit 2");
#endif
return;
}
index=substr(TDmn->dmn.zones,buf,index,',');
}
TDmn=TDmn->next;
}

TDmn=FDmn;
while(TDmn!=NULL) {
if (TDmn->dmn.Default) {
sprintf(name,(TDmn->dmn.HaveMainZone && adr.zone==TDmn->dmn.MainZone)?("%s"):("%s.%3.3x"),TDmn->dmn.out,adr.zone);
#ifdef DEBUG
write_log('~',"<-GetOutbound Exit 3");
#endif
return;
}
TDmn=TDmn->next;
}

write_log('!',"No default domain");
}
/* Get Bink Name */
void GetBinkName(Adr4D adr,char * domain,char * binkname)
{
static char buf[255],buf1[255];
#ifdef DEBUG
write_log('~',"->GetBinkName");
#endif
GetOutbound(adr,domain,buf1);
mkdir(buf1);
#ifdef UNIX
sprintf(buf,"%s/%4.4x%4.4x",buf1,adr.net,adr.node);
#else
sprintf(buf,"%s\\%4.4x%4.4x",buf1,adr.net,adr.node);
#endif
if (adr.point) {
sprintf(buf1,"%s.pnt",buf);
mkdir(buf1);
#ifdef UNIX
sprintf(buf1,".pnt/%8.8x",adr.point);
#else
sprintf(buf1,".pnt\\%8.8x",adr.point);
#endif
strcat(buf,buf1);
}
strcpy(binkname,buf);
#ifdef DEBUG
write_log('~',"<-GetBinkName");
#endif
}
/* Check busy System */
BOOL_1 BusySystemCheck(Adr4D adr,char * domain)
{
static char buf[255];
#ifdef DEBUG
write_log('~',"BusySystemCheck");
#endif
GetBinkName(adr,domain,buf);
strcat(buf,".?sy");
if (FileExist(buf)) return TRUE;
else return FALSE;
}
/* Set System busy */
void BusySystemSet(Adr4D adr,char * domain)
{
static char buf[255];
#ifdef DEBUG
write_log('~',"->BusySystemSet");
#endif
GetBinkName(adr,domain,buf);
strcat(buf,".bsy");
fclose(fopen(buf,"wb+"));
#ifdef DEBUG
write_log('~',"<-BusySystemSet");
#endif
}
/* Free Busy System */
void BusySystemUnSet(Adr4D adr,char * domain)
{
static char buf[255];
#ifdef DEBUG
write_log('~',"->BusySystemUnSet");
#endif
GetBinkName(adr,domain,buf);
strcat(buf,".bsy");
unlink(buf);
GetBinkName(adr,domain,buf);
strcat(buf,".csy");
unlink(buf);
#ifdef DEBUG
write_log('~',"<-BusySystemUnSet");
#endif
}
