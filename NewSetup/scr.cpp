#include "scr.h"

extern unsigned long tact,maxact;
extern ScriptRec *FScr,*TScr,*PScr;
#ifdef __BORLANDC__
#pragma pack 1
#endif
//----------------------------------------------------------------------------
TScriptDialog::TScriptDialog(const TRect& bounds, const char *aTitle):
  TDialog(bounds,aTitle),
  TWindowInit(TScriptDialog::initFrame)
{
options=options | ofCentered;
helpCtx=hcScripts;
// First List Init
if (FScr==NULL) {
FScr=(ScriptRec far *)farcalloc(1,sizeof(ScriptRec));
FScr->next=NULL;
*FScr->scr.name=0;
}
TScr=FScr;
// Indicator
Ind=new TIndicator(TRect(1,1,77,2),255);
insert(Ind);
// Script
ILScan=new TInputLine(TRect(22,3,77,4),255);
insert(ILScan);
insert(new TLabel(TRect(2,3,21,4),"Script",ILScan));
// Buttons
insert(new TButton(TRect(2,6,13,8),"~I~ns",cmScrIns,bfNormal));
insert(new TButton(TRect(13,6,24,8),"~D~el",cmScrDel,bfNormal));
insert(new TButton(TRect(24,6,35,8),"~H~ome",cmScrHome,bfNormal));
insert(new TButton(TRect(35,6,45,8),"~<~-",cmScrLeft,bfNormal));
insert(new TButton(TRect(45,6,55,8),"-~>~",cmScrRight,bfNormal));
insert(new TButton(TRect(55,6,66,8),"~E~nd",cmScrEnd,bfNormal));
insert(new TButton(TRect(66,6,76,8),"~O~k",cmOK,bfDefault));
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::SetDiaData(void)
{
static char buf[255];
ILScan->setData(TScr->scr.name);
sprintf(buf,"%lu/%lu",tact,maxact);
Ind->setData(buf);
}
//----------------------------------------------------------------------------
void TScriptDialog::GetDiaData(void)
{
ILScan->getData(TScr->scr.name);
}
//----------------------------------------------------------------------------
void TScriptDialog::Ins(void)
{
GetDiaData();
 maxact++;tact++;
 PScr=(ScriptRec far *)farcalloc(1,sizeof(ScriptRec));
 PScr->next=TScr->next;
 *PScr->scr.name=0;
 TScr->next=PScr;
 TScr=PScr;
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::Del(void)
{
GetDiaData();
 if (TScr!=FScr) {
 maxact--;
 PScr=TScr;
 tact=1;
 TScr=FScr;
 while (TRUE) {
 if (TScr->next==PScr) break;
 TScr=(ScriptRec far *)TScr->next;
 tact++;
 } /* while */
 TScr->next=PScr->next;
 farfree(PScr);
 } else if (FScr->next!=NULL) {
        maxact--;
        FScr=(ScriptRec far *)FScr->next;
        farfree(TScr);
        TScr=FScr;
        }
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::Home(void)
{
GetDiaData();
 TScr=FScr;
 tact=1;
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::Right(void)
{
GetDiaData();
 if (TScr->next!=NULL) {TScr=(ScriptRec far *)TScr->next;tact++;}
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::End(void)
{
GetDiaData();
 while (TScr->next!=NULL) {TScr=(ScriptRec far *)TScr->next;tact++;}
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::Left(void)
{
GetDiaData();
 if (TScr!=FScr) {
 PScr=TScr;
 tact=1;
 TScr=FScr;
 while (TRUE) {
 if (TScr->next==PScr) break;
 TScr=(ScriptRec far *)TScr->next;
 tact++;
 } /* while */
 } /* if */
SetDiaData();
}
//----------------------------------------------------------------------------
void TScriptDialog::handleEvent(TEvent& event)
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
