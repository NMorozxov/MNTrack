//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "addr.h"
#include "wsetup.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TAddrBox *AddrBox;
//---------------------------------------------------------------------------
AKAType *FAKA,*TAKA,*PAKA;
unsigned long taka,maxaka;
extern int ConfigChanged;
//---------------------------------------------------------------------------
__fastcall TAddrBox::TAddrBox(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddrBox::ButtonOkClick(TObject *Sender)
{
AKAGetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::FormActivate(TObject *Sender)
{
if (FAKA==NULL) 
 {
 FAKA=(AKAType *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(AKAType));
 FAKA->next=NULL;
 maxaka=1;
 }
TAKA=FAKA;
taka=1;
AKASetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonInsClick(TObject *Sender)
{
AKAGetData();
   maxaka++;taka++;
   PAKA=(AKAType *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(AKAType));
   PAKA->next=TAKA->next;
   TAKA->next=PAKA;
   TAKA=PAKA;
AKASetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonDelClick(TObject *Sender)
{
AKAGetData();
   if (TAKA!=FAKA) {
   maxaka--;
   PAKA=TAKA;
   taka=1;
   TAKA=FAKA;
   while (TRUE) {
   if (TAKA->next==PAKA) break;
   TAKA=(AKAType *)TAKA->next;
   taka++;
   } /* while */
   TAKA->next=PAKA->next;
   HeapFree(GetProcessHeap(),0,PAKA);
   } else if (FAKA->next!=NULL) {
          maxaka--;
          FAKA=(AKAType *)FAKA->next;
          HeapFree(GetProcessHeap(),0,TAKA);
          TAKA=FAKA;
          }
AKASetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonFirstClick(TObject *Sender)
{
AKAGetData();
taka=1;
TAKA=FAKA;
AKASetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonPrevClick(TObject *Sender)
{
AKAGetData();
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
AKASetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonNextClick(TObject *Sender)
{
AKAGetData();
if (TAKA->next!=NULL) {
TAKA=(AKAType *)TAKA->next;
taka++;
}
AKASetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::ButtonLastClick(TObject *Sender)
{
AKAGetData();
while (TAKA->next!=NULL) {
TAKA=(AKAType *)TAKA->next;
taka++;
}
AKASetData();
}
//---------------------------------------------------------------------------

void __fastcall TAddrBox::Edit1Change(TObject *Sender)
{
ConfigChanged=true;
}
//---------------------------------------------------------------------------

void TAddrBox::AKAGetData(void)
{
Edit1->GetTextBuf(config.bouadr,255);
Edit3->GetTextBuf(TAKA->zone,255);
Edit4->GetTextBuf(TAKA->net,255);
Edit5->GetTextBuf(TAKA->addr,255);
}
//---------------------------------------------------------------------------

void TAddrBox::AKASetData(void)
{
static char buf[25];
sprintf(buf,"%lu/%lu",taka,maxaka);
Edit2->Text=buf;
Edit1->Text=config.bouadr;
Edit3->Text=TAKA->zone;
Edit4->Text=TAKA->net;
Edit5->Text=TAKA->addr;
ButtonDel->Enabled=true;
if (FAKA==TAKA)
 {
 ButtonFirst->Enabled=false;
 ButtonPrev->Enabled=false;
 if (TAKA->next==NULL) ButtonDel->Enabled=false;
 }
else
 {
 ButtonFirst->Enabled=true;
 ButtonPrev->Enabled=true;
 }
if (TAKA->next==NULL)
 {
 ButtonLast->Enabled=false;
 ButtonNext->Enabled=false;
 }
else
 {
 ButtonLast->Enabled=true;
 ButtonNext->Enabled=true;
 }

}
//---------------------------------------------------------------------------

