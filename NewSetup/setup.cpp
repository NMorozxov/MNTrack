#include "setup.h"
extern ConfigType config;
int ConfigChanged=false;
ScriptRec far *FScr=NULL,far *TScr=NULL,far *PScr=NULL;
DmnRec far *FDmn=NULL,far *TDmn=NULL,far *PDmn=NULL;
AKAType far *FAKA=NULL,far *TAKA=NULL,far *PAKA=NULL;
unsigned long tact=1,maxact=1,tdmn=1,maxdmn=1,taka=1,maxaka=1;
#ifdef __BORLANDC__
#pragma pack 1
#endif
//----------------------------------------------------------------------------
TSetupApp::TSetupApp() :
        TProgInit( TSetupApp::initStatusLine,
                   TSetupApp::initMenuBar,
                   TSetupApp::initDeskTop
                 )
{
}
//----------------------------------------------------------------------------
TStatusLine *TSetupApp::initStatusLine(TRect r)
{
 r.a.y = r.b.y - 1;
 return new TStatusLine(r,
   *new TStatusDef(0,0xFFFF) +
   *new TStatusItem("~Alt-X~ Exit",kbAltX,cmQuit) +
   *new TStatusItem("~F1~ Help",kbF1,cmHelp) +
   *new TStatusItem("~F10~ Menu",kbF10,cmMenu)
                        );
}
//----------------------------------------------------------------------------
TMenuBar *TSetupApp::initMenuBar(TRect r)
{
 r.b.y = r.a.y + 1;
 return new TMenuBar( r,
  *new TSubMenu("~G~eneral", kbNoKey) +
   *new TMenuItem("~G~eneral Options", cmGenOpt,kbNoKey,hcGenOpt,"") +
   *new TMenuItem("~A~ddress Maintenance", cmAddMai,kbNoKey,hcAdress,"") +
   *new TMenuItem("~P~ath and file Names", cmPFN,kbNoKey,hcFilePath,"") +
   *new TMenuItem("~L~og Options", cmLogOpt,kbNoKey,hclogopt,"") +
   *new TMenuItem("~M~essage Options", cmMesOpt,kbNoKey,hcmeopt,"") +
   newLine()+
   *new TMenuItem("~Q~uit", cmQuit,kbAltX,hcQuit,"Alt-X") +
  *new TSubMenu("~S~cripts", kbNoKey) +
   *new TMenuItem("Script ~O~ptions", cmScOpt,kbNoKey,hcscropt,"") +
   *new TMenuItem("~S~cripts", cmSc,kbNoKey,hcScripts,"") +
  *new TSubMenu("~P~acking", kbNoKey) +
   *new TMenuItem("~P~acking Options", cmPacOpt,kbNoKey,hcpaopt,"") +
   *new TMenuItem("~D~omains and Outbounds", cmDmn,kbNoKey,hcdomains,"") +
  *new TSubMenu("~H~elp", kbNoKey) +
   *new TMenuItem("~A~bout", cmAbout,kbNoKey,hcAbout,"") +
   *new TMenuItem("~C~ontents", cmContents,kbNoKey,hcCont,"") +
   *new TMenuItem("~I~ndex", cmIndex,kbCtrlF1,hcindex,"Ctrl-F1")
                     );
}
//----------------------------------------------------------------------------
void TSetupApp::outOfMemory()
{
messageBox("Not enough memory to complete operation.",mfError | mfOKButton);
}
#if !defined(NO_TV_STREAMS) && !defined (UNIX)
//----------------------------------------------------------------------------
TPalette& TSetupApp::getPalette() const
{
static TPalette newcolor ( cpColor cHelpColor, sizeof( cpColor cHelpColor )-1 );
static TPalette newblackwhite( cpBlackWhite cHelpBlackWhite, sizeof( cpBlackWhite cHelpBlackWhite)-1 );
static TPalette newmonochrome( cpMonochrome cHelpMonochrome, sizeof( cpMonochrome cHelpMonochrome)-1 );
static TPalette *palettes[] =
 {
 &newcolor,
 &newblackwhite,
 &newmonochrome
 };
return *(palettes[appPalette]);
}
#endif
//----------------------------------------------------------------------------
void TSetupApp::AboutProc(void)
{
TDialog *ad = new TDialog(TRect(0,0,42,11),"About");
ad->options=ad->options | ofCentered;
ad->helpCtx=hcAbout;
ad->insert(new TStaticText(TRect(10,2,30,3),"MNTrack 3.09"));
ad->insert(new TStaticText(TRect(2,4,40,5),"Copyright (C) 1996-2002 by Nicol Morozov"));
ad->insert(new TStaticText(TRect(16,6,30,7),"2:5020/991"));
ad->insert(new TButton(TRect(16,8,26,10),"~O~k",cmOK,bfDefault));
deskTop->execView(ad);
destroy(ad);
}
//----------------------------------------------------------------------------
void TSetupApp::DMNProc(void)
{
TDMNDialog *dmd = new TDMNDialog(TRect(0,0,79,18),"Domain");
deskTop->execView(dmd);
destroy(dmd);
}
//----------------------------------------------------------------------------
void TSetupApp::ScrProc(void)
{
TScriptDialog *sd = new TScriptDialog(TRect(0,0,79,9),"Script");
deskTop->execView(sd);
destroy(sd);
}
//----------------------------------------------------------------------------
void TSetupApp::PacOptProc(void)
{
struct _PacOptDiaData {
ushort insintl,cbefore,safter;
#ifdef UNIX
} __attribute__ ((packed)) PacOptDiaData;
#else
} PacOptDiaData;
#endif
// fill dialog data
PacOptDiaData.insintl=config.insintl;
PacOptDiaData.cbefore=config.clearbefore;
PacOptDiaData.safter=config.setafter;
// Initilise dialog
TDialog *paod = new TDialog(TRect(0,0,63,15),"Packing Options");
paod->options=paod->options | ofCentered;
paod->helpCtx=hcpaopt;
// Insert INTL
paod->insert(new TCheckBoxes(TRect(20,2,44,3),
             new TSItem("Insert INTL Kludge",0
             )));
// Clear Before
paod->insert(new TCheckBoxes(TRect(3,5,30,10),
            new TSItem("PVT",
            new TSItem("CRA",
            new TSItem("RCV",
            new TSItem("SNT",
            new TSItem("ATT",
            new TSItem("TRS",
            new TSItem("ORP",
            new TSItem("K/S",
            new TSItem("LOC",
            new TSItem("HLD",
            new TSItem("FRQ",
            new TSItem("RRQ",
            new TSItem("RRC",
            new TSItem("ARQ",
            new TSItem("URQ",0
            )))))))))))))))));
paod->insert(new TStaticText(TRect(2,4,31,5),"ÚÄ Clear before PACK ÄÄÄÄÄÄÄ¿"));
paod->insert(new TStaticText(TRect(2,5,3,6),"³"));
paod->insert(new TStaticText(TRect(30,5,31,6),"³"));
paod->insert(new TStaticText(TRect(2,6,3,7),"³"));
paod->insert(new TStaticText(TRect(30,6,31,7),"³"));
paod->insert(new TStaticText(TRect(2,7,3,8),"³"));
paod->insert(new TStaticText(TRect(30,7,31,8),"³"));
paod->insert(new TStaticText(TRect(2,8,3,9),"³"));
paod->insert(new TStaticText(TRect(30,8,31,9),"³"));
paod->insert(new TStaticText(TRect(2,9,3,10),"³"));
paod->insert(new TStaticText(TRect(30,9,31,10),"³"));
paod->insert(new TStaticText(TRect(2,10,31,11),"ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"));
// Clear Before
paod->insert(new TCheckBoxes(TRect(33,5,60,10),
            new TSItem("PVT",
            new TSItem("CRA",
            new TSItem("RCV",
            new TSItem("SNT",
            new TSItem("ATT",
            new TSItem("TRS",
            new TSItem("ORP",
            new TSItem("K/S",
            new TSItem("LOC",
            new TSItem("HLD",
            new TSItem("FRQ",
            new TSItem("RRQ",
            new TSItem("RRC",
            new TSItem("ARQ",
            new TSItem("URQ",0
            )))))))))))))))));
paod->insert(new TStaticText(TRect(32,4,61,5),"ÚÄ Set after PACK ÄÄÄÄÄÄÄÄÄÄ¿"));
paod->insert(new TStaticText(TRect(32,5,33,6),"³"));
paod->insert(new TStaticText(TRect(60,5,61,6),"³"));
paod->insert(new TStaticText(TRect(32,6,33,7),"³"));
paod->insert(new TStaticText(TRect(60,6,61,7),"³"));
paod->insert(new TStaticText(TRect(32,7,33,8),"³"));
paod->insert(new TStaticText(TRect(60,7,61,8),"³"));
paod->insert(new TStaticText(TRect(32,8,33,9),"³"));
paod->insert(new TStaticText(TRect(60,8,61,9),"³"));
paod->insert(new TStaticText(TRect(32,9,33,10),"³"));
paod->insert(new TStaticText(TRect(60,9,61,10),"³"));
paod->insert(new TStaticText(TRect(32,10,61,11),"ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"));
// Ok Button
paod->insert(new TButton(TRect(27,12,37,14),"~O~k",cmOK,bfDefault));
// End of Disain
paod->setData(&PacOptDiaData);
if (deskTop->execView(paod)!=cmCancel) {
// Get Dialog Data
paod->getData(&PacOptDiaData);
config.insintl=(BOOL_1)PacOptDiaData.insintl;
config.clearbefore=PacOptDiaData.cbefore;
config.setafter=PacOptDiaData.safter;
}
// Destroy dialog
destroy(paod);
}
//----------------------------------------------------------------------------
void TSetupApp::ScrOptProc(void)
{
struct _ScrOptDiaData {
ushort ksanswer,stop;
#ifdef UNIX
} __attribute__ ((packed)) ScrOptDiaData;
#else
} ScrOptDiaData;
#endif
// fill dialog data
ScrOptDiaData.ksanswer=!config.ksanswer;
ScrOptDiaData.stop=config.stop;
// Initilise dialog
TDialog *sod = new TDialog(TRect(0,0,31,13),"Script Options");
sod->options=sod->options | ofCentered;
sod->helpCtx=hcscropt;
// Update Lastread
sod->insert(new TCheckBoxes(TRect(2,2,29,3),
            new TSItem("Keep MNTrack Answers",0
            )));
// After Delete/MOVE
sod->insert(new TStaticText(TRect(2,4,29,5),"ÚÄÄ After DELETE/MOVE do Ä¿"));
sod->insert(new TStaticText(TRect(2,5,3,6),"³"));
sod->insert(new TStaticText(TRect(2,6,3,7),"³"));
sod->insert(new TStaticText(TRect(2,7,3,8),"³"));
sod->insert(new TStaticText(TRect(28,5,29,6),"³"));
sod->insert(new TStaticText(TRect(28,6,29,7),"³"));
sod->insert(new TStaticText(TRect(28,7,29,8),"³"));
sod->insert(new TStaticText(TRect(2,8,29,9),"ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"));
sod->insert(new TRadioButtons(TRect(3,5,28,8),
       new TSItem("Nothing",
       new TSItem("Stop Current Script",
            new TSItem("Stop All Scripts",0
            )))));
// Ok Button
sod->insert(new TButton(TRect(11,10,21,12),"~O~k",cmOK,bfDefault));
// End of Disain
sod->setData(&ScrOptDiaData);
if (deskTop->execView(sod)!=cmCancel) {
// Get Dialog Data
sod->getData(&ScrOptDiaData);
config.ksanswer=!ScrOptDiaData.ksanswer;
config.stop=(char)ScrOptDiaData.stop;
}
// Destroy dialog
destroy(sod);
}
//----------------------------------------------------------------------------
void TSetupApp::MesOptProc(void)
{
TView *ILF;
struct _MesOptDiaData {
ushort box;
char Fl[255];
#ifdef UNIX
} __attribute__ ((packed)) MesOptDiaData;
#else
} MesOptDiaData;
#endif
// fill dialog data
MesOptDiaData.box=config.updatelastread;
strcpy(MesOptDiaData.Fl,config.flags);
// Initilise dialog
TDialog *mod = new TDialog(TRect(0,0,50,9),"Message Options");
mod->options=mod->options | ofCentered;
mod->helpCtx=hcmeopt;
// Update Lastread
mod->insert(new TCheckBoxes(TRect(14,2,35,3),
            new TSItem("Update lastread",0
            )));
// Flags
ILF= new TInputLine(TRect(22,4,48,5),255);
mod->insert(ILF);
mod->insert(new TLabel(TRect(2,4,21,5),"Non Standart Flags",ILF));
// Ok Button
mod->insert(new TButton(TRect(20,6,30,8),"~O~k",cmOK,bfDefault));
// End of Disain
mod->setData(&MesOptDiaData);
if (deskTop->execView(mod)!=cmCancel) {
// Get Dialog Data
mod->getData(&MesOptDiaData);
config.updatelastread=(char)MesOptDiaData.box;
strcpy(config.flags,MesOptDiaData.Fl);
}
// Destroy dialog
destroy(mod);
}
//----------------------------------------------------------------------------
void TSetupApp::LogOptProc(void)
{
TView *ILLN;
struct _LogOptDiaData {
char LN[255];
ushort box;
#ifdef UNIX
} __attribute__ ((packed)) LogOptDiaData;
#else
} LogOptDiaData;
#endif
// fill dialog data
strcpy(LogOptDiaData.LN,config.logfile);
LogOptDiaData.box=(ushort)config.loglevel;
// Initilise dialog
TDialog *lod = new TDialog(TRect(0,0,45,12),"Log Options");
lod->options=lod->options | ofCentered;
lod->helpCtx=hclogopt;
// Log File Name
ILLN= new TInputLine(TRect(12,2,43,3),255);
lod->insert(ILLN);
lod->insert(new TLabel(TRect(1,2,11,3),"Log File",ILLN));
// Check Boxes
lod->insert(new TCheckBoxes(TRect(2,4,43,8),
            new TSItem("Error",
            new TSItem("Warning",
            new TSItem("User",
            new TSItem("Netmail",
            new TSItem("BSO",
            new TSItem("Semaphore",
            new TSItem("File",
            new TSItem("Debug",
            new TSItem("External",
            new TSItem("Unknown",0
            ))))))))))));
// Ok Button
lod->insert(new TButton(TRect(17,9,27,11),"~O~k",cmOK,bfDefault));
// End of Disain
lod->setData(&LogOptDiaData);
if (deskTop->execView(lod)!=cmCancel) {
// Get Dialog Data
lod->getData(&LogOptDiaData);
strcpy(config.logfile,LogOptDiaData.LN);
config.loglevel=(UINT_2)LogOptDiaData.box;
}
// Destroy dialog
destroy(lod);
}
//----------------------------------------------------------------------------
void TSetupApp::PFNProc(void)
{
TView *ILSF,*ILpkt,*ILout;
struct _PFNDiaData {
char sf[255],pkt[255],out[255];
#ifdef UNIX
} __attribute__ ((packed)) PFNDiaData;
#else
} PFNDiaData;
#endif
// fill dialog data
strcpy(PFNDiaData.sf,config.scanfiles);
strcpy(PFNDiaData.pkt,config.pktout);
strcpy(PFNDiaData.out,config.out);
// Initilise dialog
TDialog *pd = new TDialog(TRect(0,0,76,11),"Path And File Names");
pd->options=pd->options | ofCentered;
pd->helpCtx=hcFilePath;
// Scan Files
ILSF= new TInputLine(TRect(22,2,73,3),255);
pd->insert(ILSF);
pd->insert(new TLabel(TRect(2,2,21,3),"Scan Files",ILSF));
// PKT Outbound
ILpkt= new TInputLine(TRect(22,4,73,5),255);
pd->insert(ILpkt);
pd->insert(new TLabel(TRect(2,4,21,5),"PKT Outbound",ILpkt));
// Outbound
ILout= new TInputLine(TRect(22,6,73,7),255);
pd->insert(ILout);
pd->insert(new TLabel(TRect(2,6,21,7),"Outbound",ILout));
// Ok Button
pd->insert(new TButton(TRect(35,8,45,10),"~O~k",cmOK,bfDefault));
// End of Disain
pd->setData(&PFNDiaData);
if (deskTop->execView(pd)!=cmCancel) {
// Get Dialog Data
pd->getData(&PFNDiaData);
strcpy(config.scanfiles,PFNDiaData.sf);
strcpy(config.pktout,PFNDiaData.pkt);
strcpy(config.out,PFNDiaData.out);
}
// Destroy dialog
destroy(pd);
}
//----------------------------------------------------------------------------
void TSetupApp::AddMaiProc(void)
{
TAKADialog *sd = new TAKADialog(TRect(0,0,75,13),"Address Maintenance");
deskTop->execView(sd);
destroy(sd);
}
//----------------------------------------------------------------------------
void TSetupApp::GenOptProc(void)
{
TView *ILSN,*ILUUE;
struct _GenOptDiaData {
char SysOpName[255];
char UUE[255];
#ifdef UNIX
} __attribute__ ((packed)) GenOptDiaData;
#else
} GenOptDiaData;
#endif
// fill dialog data
strcpy(GenOptDiaData.SysOpName,config.sysopname);
sprintf(GenOptDiaData.UUE,"%u",config.uuedepth);
// Initilise dialog
TDialog *god = new TDialog(TRect(0,0,40,9),"General Options");
god->options=god->options | ofCentered;
god->helpCtx=hcGenOpt;
// SysOp Name Input Line
ILSN=new TInputLine(TRect(15,2,37,3),255);
god->insert(ILSN);
god->insert(new TLabel(TRect(2,2,13,3),"SysOp Name",ILSN));
// UUE Input Line
ILUUE=new TInputLine(TRect(15,4,37,5),255);
god->insert(ILUUE);
god->insert(new TLabel(TRect(2,4,13,5),"UUE Depth",ILUUE));
// Ok Button
god->insert(new TButton(TRect(16,6,26,8),"~O~k",cmOK,bfDefault));
// End of Disain
god->setData(&GenOptDiaData);
if (deskTop->execView(god)!=cmCancel) {
// Get Dialog Data
god->getData(&GenOptDiaData);
strcpy(config.sysopname,GenOptDiaData.SysOpName);
config.uuedepth=(UINT_2)atoi(GenOptDiaData.UUE);
}
// Destroy dialog
destroy(god);
}
#ifndef NO_TV_STREAMS
//----------------------------------------------------------------------------
void TSetupApp::Help(char *HelpFileName,ushort HelpCtx,TEvent& event)
{
TWindow *w;
THelpFile *hFile;
fpstream *helpStrm;
static Boolean helpInUse = False;
   if (helpInUse == False) {
   helpInUse = True;
   helpStrm = new fpstream(HelpFileName, ios::in|ios::binary);
   hFile = new THelpFile(*helpStrm);
    if (!helpStrm) {
    messageBox("Could not open help file", mfError | mfOKButton);
    delete hFile;
    } else {
      w = new THelpWindow(hFile, HelpCtx);
       if (validView(w) != 0) {
       execView(w);
       destroy(w);
       }
      clearEvent(event);
      }
   helpInUse = False;
   }
}
#endif
//----------------------------------------------------------------------------
void TSetupApp::getEvent(TEvent& event)
{
TApplication::getEvent(event);
 if ( event.what == evCommand ) {
  switch ( event.message.command ) {
  case cmHelp:
#ifndef NO_TV_STREAMS
#ifdef UNIX
  Help("unix.hlp",getHelpCtx(),event);
#else
  Help("SETUP.HLP",getHelpCtx(),event);
#endif
#else
  messageBox("No help available in this version.", mfInformation | mfOKButton);
#endif
  break;
  default:
   break;
  }
 }
}
//----------------------------------------------------------------------------
void TSetupApp::handleEvent(TEvent& event)
{
TApplication::handleEvent(event);
 if ( event.what == evCommand ) {
  switch ( event.message.command ) {
  case cmGenOpt:
   GenOptProc();
   break;
  case cmAddMai:
   AddMaiProc();
   break;
  case cmPFN:
   PFNProc();
   break;
  case cmLogOpt:
   LogOptProc();
   break;
  case cmMesOpt:
   MesOptProc();
   break;
  case cmScOpt:
   ScrOptProc();
   break;
  case cmSc:
   ScrProc();
   break;
  case cmPacOpt:
   PacOptProc();
   break;
  case cmDmn:
   DMNProc();
   break;
  case cmAbout:
   AboutProc();
   break;
  case cmContents:
#ifndef NO_TV_STREAMS
   Help("SETUP.HLP",hcCont,event);
#else
   messageBox("No help available in this version.", mfInformation | mfOKButton);
#endif
   break;
  case cmIndex:
#ifndef NO_TV_STREAMS
   Help("SETUP.HLP",hcindex,event);
#else
   messageBox("No help available in this version.", mfInformation | mfOKButton);
#endif
   break;
  default:
   break;
  }
 }
}
void main(void)
{
static TSetupApp SetupApp;
/*
if (FileExist("mntrack.bsy")) {
messageBox("MNTrack is busy",mfError | mfOKButton);
exit(0);
}
fclose(fopen("mntrack.bsy","w"));
*/
LoadConfig();
SetupApp.run();
SaveConfig();
unlink("mntrack.bsy");
}
