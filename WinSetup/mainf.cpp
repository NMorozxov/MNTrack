//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "mainf.h"
#include "about.h"
#include "genopt.h"
#include "addr.h"
#include "path.h"
#include "log.h"
#include "mes.h"
#include "scptopt.h"
#include "paopt.h"
#include "cfg.h"
#include "scr.h"
#include "dmn.h"
#include "wsetup.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
int ConfigChanged=false;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Quit1Click(TObject *Sender)
{
 MainForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
if (ConfigChanged && Application->MessageBox("Save changes ?","Warning",MB_YESNO|MB_ICONQUESTION)==ID_YES) SaveConfig();
unlink("mntrack.bsy");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender)
{
 AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::GeneralOptions1Click(TObject *Sender)
{
 GenOptBox->Edit1->Text=config.sysopname;
 GenOptBox->Edit3->Text=config.uuedepth;
 if (GenOptBox->ShowModal()!=mrOk) return;
 ConfigChanged=true;
 GenOptBox->Edit1->GetTextBuf(config.sysopname,255);
 config.uuedepth=GenOptBox->Edit3->Text.ToInt();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AddressMaintenance1Click(TObject *Sender)
{
 AddrBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PathAndFileNames1Click(TObject *Sender)
{
 PathBox->Edit1->Text=config.scanfiles;
 PathBox->Edit2->Text=config.pktout;
 PathBox->Edit3->Text=config.out;
 if (PathBox->ShowModal()!=mrOk) return;
 ConfigChanged=true;
 PathBox->Edit1->GetTextBuf(config.scanfiles,255);
 PathBox->Edit2->GetTextBuf(config.pktout,255);
 if (config.pktout[strlen(config.pktout)-1]!='\\' && config.pktout[strlen(config.pktout)-1]!='/')
  strcat(config.pktout,"\\");
 PathBox->Edit3->GetTextBuf(config.out,255);
 if (config.out[strlen(config.out)-1]=='\\' || config.out[strlen(config.out)-1]=='/')
  config.out[strlen(config.out)-1]=0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LogOptions1Click(TObject *Sender)
{
 LogOptBox->Edit1->Text=config.logfile;
 LogOptBox->CheckBox1->Checked=config.loglevel&1;
 LogOptBox->CheckBox2->Checked=config.loglevel&2;
 LogOptBox->CheckBox3->Checked=config.loglevel&4;
 LogOptBox->CheckBox4->Checked=config.loglevel&8;
 LogOptBox->CheckBox5->Checked=config.loglevel&16;
 LogOptBox->CheckBox6->Checked=config.loglevel&32;
 LogOptBox->CheckBox7->Checked=config.loglevel&64;
 LogOptBox->CheckBox8->Checked=config.loglevel&128;
 LogOptBox->CheckBox9->Checked=config.loglevel&256;
 LogOptBox->CheckBox10->Checked=config.loglevel&512;
 if (LogOptBox->ShowModal()!=mrOk) return;
 ConfigChanged=true;
 LogOptBox->Edit1->GetTextBuf(config.logfile,255);
 config.loglevel = (UINT_2)(LogOptBox->CheckBox1->Checked+
                   LogOptBox->CheckBox2->Checked*2+
                   LogOptBox->CheckBox3->Checked*4+
                   LogOptBox->CheckBox4->Checked*8+
                   LogOptBox->CheckBox5->Checked*16+
                   LogOptBox->CheckBox6->Checked*32+
                   LogOptBox->CheckBox7->Checked*64+
                   LogOptBox->CheckBox8->Checked*128+
                   LogOptBox->CheckBox9->Checked*256+
                   LogOptBox->CheckBox10->Checked*512);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MessageOptions1Click(TObject *Sender)
{
 MesBox->Edit1->Text=config.flags;
 MesBox->CheckBox1->Checked=config.updatelastread;
 if (MesBox->ShowModal()!=mrOk) return;
 ConfigChanged=true;
 MesBox->Edit1->GetTextBuf(config.flags,255);
 config.updatelastread=MesBox->CheckBox1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::scopt_mnuClick(TObject *Sender)
{
 SOBox->CheckBox1->Checked=!config.ksanswer;
 SOBox->RadioGroup1->ItemIndex=config.stop;
 if (SOBox->ShowModal()!=mrOk) return;
 config.ksanswer=!SOBox->CheckBox1->Checked;
 config.stop=SOBox->RadioGroup1->ItemIndex;
 ConfigChanged=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::packing_options_mnuClick(TObject *Sender)
{
 PABox->CheckBox1->Checked=config.insintl;
 PABox->CheckBox2->Checked=config.clearbefore&1;
 PABox->CheckBox3->Checked=config.clearbefore&2;
 PABox->CheckBox4->Checked=config.clearbefore&4;
 PABox->CheckBox5->Checked=config.clearbefore&8;
 PABox->CheckBox6->Checked=config.clearbefore&16;
 PABox->CheckBox7->Checked=config.clearbefore&32;
 PABox->CheckBox8->Checked=config.clearbefore&64;
 PABox->CheckBox9->Checked=config.clearbefore&128;
 PABox->CheckBox10->Checked=config.clearbefore&256;
 PABox->CheckBox11->Checked=config.clearbefore&512;
 PABox->CheckBox12->Checked=config.clearbefore&1024;
 PABox->CheckBox13->Checked=config.clearbefore&2048;
 PABox->CheckBox14->Checked=config.clearbefore&4096;
 PABox->CheckBox15->Checked=config.clearbefore&8192;
 PABox->CheckBox16->Checked=config.clearbefore&16384;
 PABox->CheckBox17->Checked=config.setafter&1;
 PABox->CheckBox18->Checked=config.setafter&2;
 PABox->CheckBox19->Checked=config.setafter&4;
 PABox->CheckBox20->Checked=config.setafter&8;
 PABox->CheckBox21->Checked=config.setafter&16;
 PABox->CheckBox22->Checked=config.setafter&32;
 PABox->CheckBox23->Checked=config.setafter&64;
 PABox->CheckBox24->Checked=config.setafter&128;
 PABox->CheckBox25->Checked=config.setafter&256;
 PABox->CheckBox26->Checked=config.setafter&512;
 PABox->CheckBox27->Checked=config.setafter&1024;
 PABox->CheckBox28->Checked=config.setafter&2048;
 PABox->CheckBox29->Checked=config.setafter&4096;
 PABox->CheckBox30->Checked=config.setafter&8192;
 PABox->CheckBox31->Checked=config.setafter&16384;
 if (PABox->ShowModal()!=mrOk) return;
 ConfigChanged=true;
 config.insintl=PABox->CheckBox1->Checked;
 config.clearbefore=(UINT_2)(PABox->CheckBox2->Checked+
                    PABox->CheckBox3->Checked*2+
                    PABox->CheckBox4->Checked*4+
                    PABox->CheckBox5->Checked*8+
                    PABox->CheckBox6->Checked*16+
                    PABox->CheckBox7->Checked*32+
                    PABox->CheckBox8->Checked*64+
                    PABox->CheckBox9->Checked*128+
                    PABox->CheckBox10->Checked*256+
                    PABox->CheckBox11->Checked*512+
                    PABox->CheckBox12->Checked*1024+
                    PABox->CheckBox13->Checked*2048+
                    PABox->CheckBox14->Checked*4096+
                    PABox->CheckBox15->Checked*8192+
                    PABox->CheckBox16->Checked*16384
                    );
 config.setafter=(UINT_2)(PABox->CheckBox17->Checked+
                 PABox->CheckBox18->Checked*2+
                 PABox->CheckBox19->Checked*4+
                 PABox->CheckBox20->Checked*8+
                 PABox->CheckBox21->Checked*16+
                 PABox->CheckBox22->Checked*32+
                 PABox->CheckBox23->Checked*64+
                 PABox->CheckBox24->Checked*128+
                 PABox->CheckBox25->Checked*256+
                 PABox->CheckBox26->Checked*512+
                 PABox->CheckBox27->Checked*1024+
                 PABox->CheckBox28->Checked*2048+
                 PABox->CheckBox29->Checked*4096+
                 PABox->CheckBox30->Checked*8192+
                 PABox->CheckBox31->Checked*16384
                 );

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::scrp_mnuClick(TObject *Sender)
{
 Script->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::dones_mnuClick(TObject *Sender)
{
 DMNForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Contents1Click(TObject *Sender)
{
 Application->HelpCommand(HELP_CONTENTS, 0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Index1Click(TObject *Sender)
{
 Application->HelpCommand(HELP_PARTIALKEY,(long)"");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
Application->HelpFile = "SETUPN.HLP";
LoadConfig();
}
//---------------------------------------------------------------------------

