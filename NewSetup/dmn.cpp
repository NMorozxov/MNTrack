#include "dmn.h"

extern unsigned long tdmn,maxdmn;
extern DmnRec *FDmn,*TDmn,*PDmn;
#ifdef __BORLANDC__
#pragma pack 1
#endif
//----------------------------------------------------------------------------
TDMNDialog::TDMNDialog(const TRect& bounds, const char *aTitle):
  TDialog(bounds,aTitle),
  TWindowInit(TDMNDialog::initFrame)
{
options=options | ofCentered;
helpCtx=hcdomains;
if (FDmn==NULL) {
FDmn=(DmnRec far *)farcalloc(1,sizeof(DmnRec));
FDmn->next=NULL;
*FDmn->dmn.name=0;
*FDmn->dmn.out=0;
FDmn->dmn.Default=0;
FDmn->dmn.HaveMainZone=0;
FDmn->dmn.MainZone=0;
*FDmn->dmn.zones=0;
}
TDmn=FDmn;
// Indicator
Ind=new TIndicator(TRect(1,1,77,2),255);
insert(Ind);
// Name
ILName=new TInputLine(TRect(22,3,77,4),255);
insert(ILName);
insert(new TLabel(TRect(2,3,21,4),"Name",ILName));
// Outbound
ILout=new TInputLine(TRect(22,5,77,6),255);
insert(ILout);
insert(new TLabel(TRect(2,5,21,6),"Outbound",ILout));
// Default
CDef=new TCheckBoxes(TRect(2,7,21,8),new TSItem("Default",0));
insert(CDef);
// Have Main Zone
CHMZ=new TCheckBoxes(TRect(2,8,21,9),new TSItem("Have Main Zone",0));
insert(CHMZ);
// Main Zone
ILMZ=new TInputLine(TRect(22,10,29,11),5);
insert(ILMZ);
insert(new TLabel(TRect(2,10,21,11),"Main Zone",ILMZ));
// Zones
ILZones=new TInputLine(TRect(22,12,77,13),255);
insert(ILZones);
insert(new TLabel(TRect(2,12,21,13),"Zones In Domain",ILZones));
// Buttons
insert(new TButton(TRect(2,15,13,17),"~I~ns",cmScrIns,bfNormal));
insert(new TButton(TRect(13,15,24,17),"~D~el",cmScrDel,bfNormal));
insert(new TButton(TRect(24,15,35,17),"~H~ome",cmScrHome,bfNormal));
insert(new TButton(TRect(35,15,45,17),"~<~-",cmScrLeft,bfNormal));
insert(new TButton(TRect(45,15,55,17),"-~>~",cmScrRight,bfNormal));
insert(new TButton(TRect(55,15,66,17),"~E~nd",cmScrEnd,bfNormal));
insert(new TButton(TRect(66,15,76,17),"~O~k",cmOK,bfDefault));
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::GetDiaData(void)
{
static ushort a,d;
static char buf[255];
ILName->getData(TDmn->dmn.name);
ILout->getData(TDmn->dmn.out);
CDef->getData(&a);
TDmn->dmn.Default=(BOOL_1)a;
CHMZ->getData(&d);
TDmn->dmn.HaveMainZone=(BOOL_1)d;
ILMZ->getData(buf);
TDmn->dmn.MainZone=(UINT_2)atoi(buf);
ILZones->getData(TDmn->dmn.zones);
}
//----------------------------------------------------------------------------
void TDMNDialog::SetDiaData(void)
{
static char buf[255],buf1[255];
static ushort a,d;
sprintf(buf1,"%lu/%lu",tdmn,maxdmn);
Ind->setData(buf1);
// Set Data
ILName->setData(TDmn->dmn.name);
ILout->setData(TDmn->dmn.out);
a=TDmn->dmn.Default;
CDef->setData(&a);
d=TDmn->dmn.HaveMainZone;
CHMZ->setData(&d);
sprintf(buf,"%u",TDmn->dmn.MainZone);
ILMZ->setData(buf);
ILZones->setData(TDmn->dmn.zones);
}
//----------------------------------------------------------------------------
void TDMNDialog::Ins(void)
{
GetDiaData();
 maxdmn++;tdmn++;
 PDmn=(DmnRec far *)farcalloc(1,sizeof(DmnRec));
 PDmn->next=TDmn->next;
 *PDmn->dmn.name=0;
 *PDmn->dmn.out=0;
 PDmn->dmn.Default=0;
 PDmn->dmn.HaveMainZone=0;
 PDmn->dmn.MainZone=0;
 *PDmn->dmn.zones=0;
 TDmn->next=PDmn;
 TDmn=PDmn;
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::Del(void)
{
GetDiaData();
 if (TDmn!=FDmn) {
 maxdmn--;
 PDmn=TDmn;
 tdmn=1;
 TDmn=FDmn;
 while (TRUE) {
 if (TDmn->next==PDmn) break;
 TDmn=(DmnRec far *)TDmn->next;
 tdmn++;
 } /* while */
 TDmn->next=PDmn->next;
 farfree(PDmn);
 } else if (FDmn->next!=NULL) {
        maxdmn--;
        FDmn=(DmnRec far *)FDmn->next;
        farfree(TDmn);
        TDmn=FDmn;
        }
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::Home(void)
{
GetDiaData();
 TDmn=FDmn;
 tdmn=1;
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::Left(void)
{
GetDiaData();
 if (TDmn!=FDmn) {
 PDmn=TDmn;
 tdmn=1;
 TDmn=FDmn;
 while (TRUE) {
 if (TDmn->next==PDmn) break;
 TDmn=(DmnRec far *)TDmn->next;
 tdmn++;
 } /* while */
 } /* if */
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::Right(void)
{
GetDiaData();
 if (TDmn->next!=NULL) {TDmn=(DmnRec far *)TDmn->next;tdmn++;}
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::End(void)
{
GetDiaData();
 while (TDmn->next!=NULL) {TDmn=(DmnRec far *)TDmn->next;tdmn++;}
SetDiaData();
}
//----------------------------------------------------------------------------
void TDMNDialog::handleEvent(TEvent& event)
{
if ( event.what == evKeyDown ) switch ( event.keyDown.keyCode ) {
                                case kbIns:
                                 Ins();
                                 break;
                                case kbDel:
                                 Del();
                                 break;
                                case kbHome:
                                 Home();
                                 break;
                                case kbLeft:
                                 Left();
                                 break;
                                case kbRight:
                                 Right();
                                 break;
                                case kbEnd:
                                 End();
                                 break;
                                }
if ( event.what == evCommand ) switch ( event.message.command ) {
                               case cmScrIns:
                                Ins();
                                break;
                               case cmScrRight:
                                Right();
                                break;
                              case cmScrEnd:
                                End();
                                break;
                              case cmScrLeft:
                                Left();
                                break;
                              case cmScrHome:
                                Home();
                                break;
                              case cmScrDel:
                                Del();
                                break;
                              case cmOK:
                                GetDiaData();
                              }
TDialog::handleEvent(event);
}

//----------------------------------------------------------------------------
