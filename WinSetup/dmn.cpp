//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <mn_types.h>
#include "dmn.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDMNForm *DMNForm;
//---------------------------------------------------------------------------
DmnRec *FDmn;
DmnRec *TDmn;
DmnRec *PDmn;
unsigned long tdmn,maxdmn;
extern int ConfigChanged;
//---------------------------------------------------------------------------
void TDMNForm::DmnGetData(void)
{
static char buf[255];
DMNForm->Edit1->GetTextBuf(TDmn->dmn.name,255);
DMNForm->Edit2->GetTextBuf(TDmn->dmn.out,255);
TDmn->dmn.Default=DMNForm->CheckBox1->Checked;
TDmn->dmn.HaveMainZone=DMNForm->CheckBox2->Checked;
DMNForm->Edit3->GetTextBuf(buf,255);
TDmn->dmn.MainZone=(UINT_2)atoi(buf);
DMNForm->Edit4->GetTextBuf(TDmn->dmn.zones,255);
}
//---------------------------------------------------------------------------
void TDMNForm::DmnSetData(void)
{
char buf[255],buf3[255];
sprintf(buf,"%lu/%lu",tdmn,maxdmn);
DMNForm->Edit5->Text=buf;

DMNForm->Edit1->Text=TDmn->dmn.name;
DMNForm->Edit2->Text=TDmn->dmn.out;
DMNForm->CheckBox1->Checked=TDmn->dmn.Default;
DMNForm->CheckBox2->Checked=TDmn->dmn.HaveMainZone;
sprintf(buf3,"%u",TDmn->dmn.MainZone);
DMNForm->Edit3->Text=buf3;
DMNForm->Edit4->Text=TDmn->dmn.zones;
// Main Zone
if (DMNForm->CheckBox2->Checked) DMNForm->Edit3->Enabled=true;
else DMNForm->Edit3->Enabled=false;
// Buttons
DMNForm->Button2->Enabled=true;
DMNForm->Button3->Enabled=true;
DMNForm->Button4->Enabled=true;
DMNForm->Button5->Enabled=true;
DMNForm->Button7->Enabled=true;
if (FDmn==TDmn) {
if (TDmn->next==NULL) DMNForm->Button2->Enabled=false;
DMNForm->Button3->Enabled=false;
DMNForm->Button5->Enabled=false;
}
if (TDmn->next==NULL) {
DMNForm->Button4->Enabled=false;
DMNForm->Button7->Enabled=false;
}
}
//---------------------------------------------------------------------------
__fastcall TDMNForm::TDMNForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::FormActivate(TObject *Sender)
{
if (FDmn==NULL) {
if ((FDmn=(DmnRec *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(DmnRec)))==NULL) {
Application->MessageBox("Not Enough memmory to add domain record.","Error",MB_OK);
DMNForm->Close();
}
FDmn->next=NULL;
maxdmn=1;
}
tdmn=1;
TDmn=FDmn;
DmnSetData();
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button6Click(TObject *Sender)
{
 DmnGetData();	
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button4Click(TObject *Sender)
{
 DmnGetData();
 if (TDmn->next!=NULL) {TDmn=(DmnRec *)TDmn->next;tdmn++;}
 DmnSetData();
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button3Click(TObject *Sender)
{
 DmnGetData();
  if (TDmn!=FDmn) {
   PDmn=TDmn;
   tdmn=1;
   TDmn=FDmn;
   while (TRUE) {
   if (TDmn->next==PDmn) break;
   TDmn=(DmnRec *)TDmn->next;
   tdmn++;
   } /* while */
   } /* if */
 DmnSetData();
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button5Click(TObject *Sender)
{
 DmnGetData();
 TDmn=FDmn;
 tdmn=1;
 DmnSetData();
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button2Click(TObject *Sender)
{
 DmnGetData();
 if (TDmn!=FDmn) {
   maxdmn--;
   PDmn=TDmn;
   tdmn=1;
   TDmn=FDmn;
   while (TRUE) {
   if (TDmn->next==PDmn) break;
   TDmn=(DmnRec *)TDmn->next;
   tdmn++;
   } /* while */
   TDmn->next=PDmn->next;
   HeapFree(GetProcessHeap(),0,PDmn);
   } else if (FDmn->next!=NULL) {
          maxdmn--;
          FDmn=(DmnRec *)FDmn->next;
          HeapFree(GetProcessHeap(),0,TDmn);
          TDmn=FDmn;
          }
 DmnSetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button1Click(TObject *Sender)
{
DmnGetData();
   maxdmn++;tdmn++;
   PDmn=(DmnRec *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(DmnRec));
   PDmn->next=TDmn->next;
   TDmn->next=PDmn;
   TDmn=PDmn;
DmnSetData();
ConfigChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::Button7Click(TObject *Sender)
{
 DmnGetData();
 while (TDmn->next!=NULL) {TDmn=(DmnRec *)TDmn->next;tdmn++;}
 DmnSetData();
}
//---------------------------------------------------------------------------
void __fastcall TDMNForm::CheckBox2Click(TObject *Sender)
{
if (DMNForm->CheckBox2->Checked) DMNForm->Edit3->Enabled=true;
else DMNForm->Edit3->Enabled=false;
ConfigChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TDMNForm::Edit1Change(TObject *Sender)
{
ConfigChanged=true;
}
//---------------------------------------------------------------------------

