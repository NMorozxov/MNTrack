//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "scr.h"
#include <stdio.h>
#include <stdlib.h>
#include <mn_types.h>
//---------------------------------------------------------------------------
#pragma link "ToolEdit"
#pragma resource "*.dfm"
TScript *Script;
unsigned long tact,maxact;
ScriptRec *FScr,*TScr,*PScr;
extern int ConfigChanged;
//---------------------------------------------------------------------------
void TScript::ScrSetData(void)
{
char buf[25],buf2[255];
sprintf(buf,"%lu/%lu",tact,maxact);
Script->Edit1->Text=buf;
sprintf(buf2,"%s",TScr->scr.name);
Script->FilenameEdit1->Text=buf2;
// Buttons
Script->Button2->Enabled=true;
Script->Button3->Enabled=true;
Script->Button4->Enabled=true;
Script->Button5->Enabled=true;
Script->Button7->Enabled=true;
if (FScr==TScr) {
if (TScr->next==NULL) Script->Button2->Enabled=false;
Script->Button3->Enabled=false;
Script->Button5->Enabled=false;
}
if (TScr->next==NULL) {
Script->Button4->Enabled=false;
Script->Button7->Enabled=false;
}
}
//---------------------------------------------------------------------------
void TScript::ScrGetData(void)
{
Script->FilenameEdit1->GetTextBuf(TScr->scr.name,255);
}
//---------------------------------------------------------------------------
__fastcall TScript::TScript(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button6Click(TObject *Sender)
{
 ScrGetData();
}
//---------------------------------------------------------------------------
void __fastcall TScript::FormActivate(TObject *Sender)
{
if (FScr==NULL) {
FScr=(ScriptRec *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(ScriptRec));
FScr->next=NULL;
}
TScr=FScr;
tact=1;
ScrSetData();
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button5Click(TObject *Sender)
{
ScrGetData();
tact=1;
TScr=FScr;
ScrSetData();
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button4Click(TObject *Sender)
{
ScrGetData();
if (TScr->next!=NULL) {
TScr=(ScriptRec *)TScr->next;
tact++;
}
ScrSetData();
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button3Click(TObject *Sender)
{
ScrGetData();
   if (TScr!=FScr) {
   PScr=TScr;
   tact=1;
   TScr=FScr;
   while (TRUE) {
   if (TScr->next==PScr) break;
   TScr=(ScriptRec *)TScr->next;
   tact++;
   } /* while */
   } /* if */
ScrSetData();
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button2Click(TObject *Sender)
{
ScrGetData();
   if (TScr!=FScr) {
   maxact--;
   PScr=TScr;
   tact=1;
   TScr=FScr;
   while (TRUE) {
   if (TScr->next==PScr) break;
   TScr=(ScriptRec *)TScr->next;
   tact++;
   } /* while */
   TScr->next=PScr->next;
   HeapFree(GetProcessHeap(),0,PScr);
   } else if (FScr->next!=NULL) {
          maxact--;
          FScr=(ScriptRec *)FScr->next;
          HeapFree(GetProcessHeap(),0,TScr);
          TScr=FScr;
          }
ScrSetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button1Click(TObject *Sender)
{
ScrGetData();
   maxact++;tact++;
   PScr=(ScriptRec *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(ScriptRec));
   PScr->next=TScr->next;
   //*PScr->scr.name=0;
   TScr->next=PScr;
   TScr=PScr;
ScrSetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TScript::Button7Click(TObject *Sender)
{
ScrGetData();
while (TScr->next!=NULL) {
TScr=(ScriptRec *)TScr->next;
tact++;
}
ScrSetData();

}
//---------------------------------------------------------------------------
void __fastcall TScript::FilenameEdit1Change(TObject *Sender)
{
ConfigChanged=true;
}
//---------------------------------------------------------------------------
