#include "pkt.h"
extern HeaderType hea;
extern int mid;
/* Make PKT Header */
void MakePKTHeader(Adr4D fad,Adr4D tad,char *pass,FILE *f)
{
TPKTFileHeader pkt;
struct tm *tmm;
time_t timer;

#ifdef DEBUG
write_log('~',"->MakePKTHeader");
#endif

timer=time(NULL);
tmm=localtime(&timer);

ZeroMemory(&pkt,sizeof(TPKTFileHeader));
strcpy(pkt.Password,pass);
pkt.OrigNode=fad.node;
pkt.DestNode=tad.node;
pkt.Year=(UINT_2)(tmm->tm_year+1900);
pkt.Month=(UINT_2)tmm->tm_mon;
pkt.Day=(UINT_2)tmm->tm_mday;
pkt.Hour=(UINT_2)tmm->tm_hour;
pkt.Min=(UINT_2)tmm->tm_min;
pkt.Sec=(UINT_2)tmm->tm_sec;
pkt.Baud=0;/*!*/
pkt.PktVer=2;
pkt.OrigNet=fad.net;
pkt.DestNet=tad.net;
pkt.ProdCodeLo=0; /*!*/
pkt.SerialNoHi=0; /*!*/
pkt.QOrigZone=fad.zone;
pkt.QDestZone=tad.zone;
pkt.AuxNet=0;/*!*/
pkt.CWValCopy=0x0100;
pkt.ProdCodeHi=0;/*!*/
pkt.SerialNoLo=0;/*!*/
pkt.CapWord=0x0001;
pkt.OrigZone=fad.zone;
pkt.DestZone=tad.zone;
pkt.OrigPoint=fad.point;
pkt.DestPoint=tad.point;
pkt.Product=0; /*!*/
fwrite(&pkt.OrigNode,1,2,f);
fwrite(&pkt.DestNode,1,2,f);
fwrite(&pkt.Year,1,2,f);
fwrite(&pkt.Month,1,2,f);
fwrite(&pkt.Day,1,2,f);
fwrite(&pkt.Hour,1,2,f);
fwrite(&pkt.Min,1,2,f);
fwrite(&pkt.Sec,1,2,f);
fwrite(&pkt.Baud,1,2,f);
fwrite(&pkt.PktVer,1,2,f);
fwrite(&pkt.OrigNet,1,2,f);
fwrite(&pkt.DestNet,1,2,f);
fwrite(&pkt.ProdCodeLo,1,1,f);
fwrite(&pkt.SerialNoHi,1,1,f);
fwrite(&pkt.Password,1,8,f);
fwrite(&pkt.QOrigZone,1,2,f);
fwrite(&pkt.QDestZone,1,2,f);
fwrite(&pkt.AuxNet,1,2,f);
fwrite(&pkt.CWValCopy,1,2,f);
fwrite(&pkt.ProdCodeHi,1,1,f);
fwrite(&pkt.SerialNoLo,1,1,f);
fwrite(&pkt.CapWord,1,2,f);
fwrite(&pkt.OrigZone,1,2,f);
fwrite(&pkt.DestZone,1,2,f);
fwrite(&pkt.OrigPoint,1,2,f);
fwrite(&pkt.DestPoint,1,2,f);
fwrite(&pkt.Product,1,4,f);
#ifdef DEBUG
write_log('~',"<-MakePKTHeader");
#endif
}
/* Make New PKT Msg Header */
void MakePKTMsgHeader(FILE *f)
{
TPKTFileMSGHeader pkt;
#ifdef DEBUG
write_log('~',"->MakePKTMsgHeader");
#endif
ZeroMemory(&pkt,sizeof(TPKTFileMSGHeader));
pkt.Version=2;
pkt.OrigNode=hea.OrigNode;
pkt.DestNode=hea.DestNode;
pkt.OrigNet=hea.OrigNet;
pkt.DestNet=hea.DestNet;
pkt.Attr=hea.Flags;
pkt.Cost=0; /*!*/
fwrite(&pkt,1,sizeof(TPKTFileMSGHeader),f);
fwrite(&hea.DateTime,1,20,f);
fwrite(&hea.ToUserName,1,strlen(hea.ToUserName)+1,f);
fwrite(&hea.FromUserName,1,strlen(hea.FromUserName)+1,f);
fwrite(&hea.Subject,1,strlen(hea.Subject)+1,f);
#ifdef DEBUG
write_log('~',"<-MakePKTMsgHeader");
#endif
}
/* Make New PKT Msg Header From & To*/
void MakePKTMsgHeaderFromTo(char *fn,Adr4D fa,char *tn,Adr4D ta,char *subj,char *area,FILE *f)
{
TPKTFileMSGHeader pkt;
static char buf[255],buf1[255];
static char moth[4];
struct tm *tmm;
time_t timer;

#ifdef DEBUG
write_log('~',"->MakePKTMsgHeaderFromTo");
#endif
pkt.Version=2;
pkt.OrigNode=fa.node;
pkt.DestNode=ta.node;
pkt.OrigNet=fa.net;
pkt.DestNet=ta.net;
pkt.Attr=0x0101;
pkt.Cost=0; /*!*/
fwrite(&pkt,1,sizeof(TPKTFileMSGHeader),f);

timer=time(NULL);
tmm=localtime(&timer);
GetMonth(tmm->tm_mon+1,moth);
fwrite(&buf,1,sprintf(buf,"%2.2d %s %2.2d  %2.2d:%2.2d:%2.2d",tmm->tm_mday,moth,year42(tmm->tm_year+1900),tmm->tm_hour,tmm->tm_min,tmm->tm_sec)+1,f);
fwrite(tn,1,strlen(tn)+1,f);
fwrite(fn,1,strlen(fn)+1,f);
fwrite(subj,1,strlen(subj)+1,f);

if (stricmp(area,"NETMAIL")) {
sprintf(buf,"AREA:%s\r",area);
fwrite(buf,1,strlen(buf),f);
} else {
  sprintf(buf,"\1INTL %u:%u/%u %u:%u/%u\r",ta.zone,ta.net,ta.node,fa.zone,fa.net,fa.node);
  fwrite(buf,1,strlen(buf),f);

  if (fa.point) {
  sprintf(buf,"\1FMPT %u\r",fa.point);
  fwrite(buf,1,strlen(buf),f);
  }

  if (ta.point) {
  sprintf(buf,"\1TOPT %u\r",ta.point);
  fwrite(buf,1,strlen(buf),f);
  }
  }

adr2txt(fa,buf1);
sprintf(buf,"\1MSGID: %s %08lx\r",buf1,time(NULL)+mid);
mid++;
fwrite(buf,1,strlen(buf),f);

#ifdef DEBUG
write_log('~',"<-MakePKTMsgHeaderFromTo");
#endif
}
