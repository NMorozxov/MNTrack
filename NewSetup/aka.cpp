#include "aka.h"

extern ConfigType config;
extern AKAType *FAKA,*TAKA,*PAKA;
extern unsigned long taka,maxaka;
#ifdef __BORLANDC__
#pragma pack 1
#endif
//----------------------------------------------------------------------------
TAKADialog::TAKADialog(const TRect& bounds, const char *aTitle):
  TDialog(bounds,aTitle),
  TWindowInit(TAKADialog::initFrame)
{
options=options | ofCentered;
helpCtx=hcAdress;
// Indicator
Ind=new TIndicator(TRect(1,1,73,2),255);
insert(Ind);
// Network Address
ILNA= new TInputLine(TRect(24,2,72,3),50);
insert(ILNA);
insert(new TLabel(TRect(2,2,23,3),"Main Network Address",ILNA));
//
insert(new TStaticText(TRect(2,3,73,4),"Ú- AKA ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿"));
ILZ= new TInputLine(TRect(3,5,8,6),5);
insert(ILZ);
insert(new TLabel(TRect(3,4,8,5),"Zone",ILZ));
insert(new TStaticText(TRect(9,4,10,5),":"));
ILN= new TInputLine(TRect(10,5,15,6),5);
insert(ILN);
insert(new TLabel(TRect(10,4,15,5),"Net",ILN));
ILA= new TInputLine(TRect(17,5,72,6),50);
insert(ILA);
insert(new TLabel(TRect(17,4,72,5),"Network Address",ILA));
// Buttons
insert(new TButton(TRect(5,7,16,9),"~I~ns",cmScrIns,bfNormal));
insert(new TButton(TRect(16,7,27,9),"~D~el",cmScrDel,bfNormal));
insert(new TButton(TRect(27,7,38,9),"~H~ome",cmScrHome,bfNormal));
insert(new TButton(TRect(38,7,48,9),"~<~-",cmScrLeft,bfNormal));
insert(new TButton(TRect(48,7,58,9),"-~>~",cmScrRight,bfNormal));
insert(new TButton(TRect(58,7,69,9),"~E~nd",cmScrEnd,bfNormal));
insert(new TStaticText(TRect(2,4,3,5),"³"));
insert(new TStaticText(TRect(2,5,3,6),"³"));
insert(new TStaticText(TRect(2,6,3,7),"³"));
insert(new TStaticText(TRect(2,7,3,8),"³"));
insert(new TStaticText(TRect(2,8,3,9),"³"));
insert(new TStaticText(TRect(72,4,73,5),"³"));
insert(new TStaticText(TRect(72,5,73,6),"³"));
insert(new TStaticText(TRect(72,6,73,7),"³"));
insert(new TStaticText(TRect(72,7,73,8),"³"));
insert(new TStaticText(TRect(72,8,73,9),"³"));
insert(new TStaticText(TRect(2,9,73,10),"ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"));
insert(new TButton(TRect(33,10,43,12),"~O~k",cmOK,bfDefault));

// First List Init
if (FAKA==NULL) 
 {
 FAKA=(AKAType far *)farcalloc(1,sizeof(AKAType));
 FAKA->next=NULL;
 maxaka=1;
 }
TAKA=FAKA;
taka=1;
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::SetDiaData(void)
{
static char buf[255];
sprintf(buf,"%lu/%lu",taka,maxaka);
Ind->setData(buf);
ILNA->setData(config.bouadr);
ILZ->setData(TAKA->zone);
ILN->setData(TAKA->net);
ILA->setData(TAKA->addr);
}
//----------------------------------------------------------------------------
void TAKADialog::GetDiaData(void)
{
ILNA->getData(config.bouadr);
ILZ->getData(TAKA->zone);
ILN->getData(TAKA->net);
ILA->getData(TAKA->addr);
}
//----------------------------------------------------------------------------
void TAKADialog::Ins(void)
{
GetDiaData();
 maxaka++;taka++;
 PAKA=(AKAType far *)farcalloc(1,sizeof(AKAType));
 PAKA->next=TAKA->next;
 TAKA->next=PAKA;
 TAKA=PAKA;
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::Del(void)
{
GetDiaData();
 if (TAKA!=FAKA) {
 maxaka--;
 PAKA=TAKA;
 taka=1;
 TAKA=FAKA;
 while (TRUE) {
 if (TAKA->next==PAKA) break;
 TAKA=(AKAType far *)TAKA->next;
 taka++;
 } /* while */
 TAKA->next=PAKA->next;
 farfree(PAKA);
 } else if (FAKA->next!=NULL) {
   maxaka--;
   FAKA=(AKAType far *)FAKA->next;
   farfree(TAKA);
   TAKA=FAKA;
   }
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::Home(void)
{
GetDiaData();
 taka=1;
 TAKA=FAKA;
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::Right(void)
{
GetDiaData();
 if (TAKA->next!=NULL) {
 TAKA=(AKAType *)TAKA->next;
 taka++;
 }
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::End(void)
{
GetDiaData();
while (TAKA->next!=NULL) {
TAKA=(AKAType *)TAKA->next;
taka++;
}
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::Left(void)
{
GetDiaData();
 if (TAKA!=FAKA) {
 PAKA=TAKA;
 taka=1;
 TAKA=FAKA;
 while (TRUE) {
 if (TAKA->next==PAKA) break;
 TAKA=(AKAType *)TAKA->next;
 taka++;
 } /* while */
 } /* if */
SetDiaData();
}
//----------------------------------------------------------------------------
void TAKADialog::handleEvent(TEvent& event)
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
