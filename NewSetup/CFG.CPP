#include "cfg.h"
//---------------------------------------------------------------------------
ConfigType config;
extern ScriptRec *FScr,*TScr,*PScr;
extern DmnRec *FDmn,*TDmn,*PDmn;
extern AKAType *FAKA,*TAKA,*PAKA;
extern unsigned long tact,maxact,tdmn,maxdmn,taka,maxaka;
extern int ConfigChanged;
#if defined(__MSDOS__) && !defined(_MNTRACK_WINSETUP_CFG_H) && !defined(_MNTRACK_TV_SETUP_CFG_H) && !defined (MNTRACK_SETUP_QT_CFG)
extern NdxRec    far *FNdx,far *TNdx,far *PNdx;
extern DmnRec    far *FDmn,far *TDmn,far *PDmn;
extern ScriptRec far *FScr,far *TScr, far *PScr;
extern AKAType   far *FAKA,far *TAKA,far *PAKA;
#endif
#if !defined(_MNTRACK_WINSETUP_CFG_H) && !defined(_MNTRACK_TV_SETUP_CFG_H) && !defined (MNTRACK_SETUP_QT_CFG)
extern NdxRec    *FNdx,*TNdx,*PNdx;
extern DmnRec    *FDmn,*TDmn,*PDmn;
extern ScriptRec *FScr,*TScr,*PScr;
extern AKAType   *FAKA,*TAKA,*PAKA;
#endif


//---------------------------------------------------------------------------
void SaveConfig(void)
{
/* Save mntrack.cfg */
FILE *configfile=fopen("mntrack.cfg","wb");
if (configfile==NULL)
 {
#ifdef _MNTRACK_WINSETUP_CFG_H
 Application->MessageBox("Can't save mntrack.cfg","Fatal",MB_ICONERROR|MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
 messageBox("Can't save mntrack.cfg",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
 QMessageBox::critical(NULL,"MNTrack Setup","Can't save mntrack.cfg");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
 printf("Can't save mntrack.cfg\n");
#endif
 unlink("mntrack.bsy");
 exit(9);
 } 
else
 {
 fwrite("MNTRACK",1,8,configfile);
 fwrite(&config,sizeof(ConfigType),1,configfile);
 fclose(configfile);
 }
/* Write MNTrack.msk*/
configfile=fopen("mntrack.msk","wb");
if (configfile==NULL)
 {
#ifdef _MNTRACK_WINSETUP_CFG_H
 Application->MessageBox("Can't save mntrack.msk","Fatal",MB_ICONERROR|MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
 messageBox("Can't save mntrack.msk",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
 QMessageBox::critical(NULL,"MNTrack Setup","Can't save mntrack.msk");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
 printf("Can't save mntrack.msk\n");
#endif
 unlink("mntrack.bsy");
 exit(9);
 }
else
 {
 TScr=FScr;
 while(TScr!=NULL)
  {
  if (*TScr->scr.name && strcmp(TScr->scr.name,"(null)"))
   fwrite(&TScr->scr,sizeof(ScriptType),1,configfile);
  TScr=(ScriptRec far *)TScr->next;
  }
 fclose(configfile);
 }
/* Write mntrack.dmn */
configfile=fopen("mntrack.dmn","wb");
if (configfile==NULL)
 {
#ifdef _MNTRACK_WINSETUP_CFG_H
 Application->MessageBox("Can't save mntrack.dmn","Fatal",MB_ICONERROR|MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
 messageBox("Can't save mntrack.dmn",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
 QMessageBox::critical(NULL,"MNTrack Setup","Can't save mntrack.dmn");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
 printf("Can't save mntrack.dmn\n");
#endif
 unlink("mntrack.bsy");
 exit(9);
 }
else
 {
 TDmn=FDmn;
 while(TDmn!=NULL)
  {
  fwrite(&TDmn->dmn,sizeof(DomenType),1,configfile);
  TDmn=(DmnRec far *)TDmn->next;
  }
 fclose(configfile);
 }

/* Write mntrack.aka */
configfile=fopen("mntrack.aka","wb");
if (configfile==NULL)
 {
#ifdef _MNTRACK_WINSETUP_CFG_H
 Application->MessageBox("Can't save mntrack.aka","Fatal",MB_ICONERROR|MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
 messageBox("Can't save mntrack.aka",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
 QMessageBox::critical(NULL,"MNTrack Setup","Can't save mntrack.aka");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
 printf("Can't save mntrack.aka\n");
#endif
 unlink("mntrack.bsy");
 exit(9);
 }
else
 {
 TAKA=FAKA;
 while(TAKA!=NULL)
  {
  if (*TAKA->zone && *TAKA->net && *TAKA->addr)
   {
   fwrite(&TAKA->zone,1,255,configfile);
   fwrite(&TAKA->net,1,255,configfile);
   fwrite(&TAKA->addr,1,255,configfile);
   }
  TAKA=(AKAType *)TAKA->next;
  }
 fclose(configfile);
 }
}
//---------------------------------------------------------------------------
void LoadConfig(void)
{
FILE *configfile;
static char buf[8];
/* Check busy */
if (FileExist("mntrack.bsy"))
 {
#ifdef _MNTRACK_WINSETUP_CFG_H
 Application->MessageBox("MNTrack is busy","Stop",MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
 messageBox("MNTrack is busy",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
 QMessageBox::critical(NULL,"MNTrack Setup","MNTrack is busy");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
 printf("MNTrack is busy\n");
#endif
 exit(0);
 }
fclose(fopen("mntrack.bsy","w"));
/* Load mntrack.cfg */
configfile=fopen("mntrack.cfg","rb");
if (configfile==NULL)
 {
#if defined(_MNTRACK_WINSETUP_CFG_H) || defined(_MNTRACK_TV_SETUP_CFG_H) || defined (MNTRACK_SETUP_QT_CFG)
 strcpy(config.scanfiles,"*.msg");
 strcpy(config.logfile,"mntrack.log");
 strcpy(config.utc,"+3");
 strcpy(config.sysopname,"SysOp");
 config.insintl=TRUE;
 config.uuedepth=5;
 config.stop=2;
 config.loglevel=0x17f;
 config.clearbefore=18412;
 config.version=MNTRACK_CONFIGURATION_VERSION;
 ConfigChanged=TRUE;
#else
 printf("Fatal : Can't open mntrack.cfg\n");
 unlink("mntrack.bsy");
 exit(1);
#endif
 }
else
 {
 fread(&buf,1,8,configfile);
 if (strcmp(buf,"MNTRACK"))
  {
#ifdef _MNTRACK_WINSETUP_CFG_H
  Application->MessageBox("File mntrack.cfg is not a MNTrack configuration file","Fatal",MB_ICONERROR|MB_OK);
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
  messageBox("File mntrack.cfg is not a MNTrack configuration file",mfError | mfOKButton);
#endif
#ifdef MNTRACK_SETUP_QT_CFG
  QMessageBox::critical(NULL,"MNTrack Setup","File mntrack.cfg is not a MNTrack configuration file");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
  printf("Fatal : File mntrack.cfg is not a MNTrack configuration file\n");
#endif
  unlink("mntrack.bsy");
  exit(1);
  }
 fread(&config,sizeof(ConfigType),1,configfile);
 fclose(configfile);
#ifdef _MNTRACK_WINSETUP_CFG_H
if (config.version!=MNTRACK_CONFIGURATION_VERSION && Application->MessageBox("Incorect configuration version ID. Continue ?","Warning",MB_YESNO|MB_ICONWARNING)!=ID_YES)
  {
#endif
#ifdef  _MNTRACK_TV_SETUP_CFG_H
if (config.version!=MNTRACK_CONFIGURATION_VERSION && messageBox("Invalid MNTrack configuration version ID.\nContinue ?",mfConfirmation | mfYesButton | mfNoButton) == 13 )
  {
#endif
#ifdef MNTRACK_SETUP_QT_CFG
if (config.version!=MNTRACK_CONFIGURATION_VERSION)
  {
  QMessageBox::critical(NULL,"MNTrack Setup","Invalid MNTrack configuration version ID.");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
if (config.version!=MNTRACK_CONFIGURATION_VERSION)
  {
#endif
  unlink("mntrack.bsy");
  exit(4);
  }
 }

#if !defined(_MNTRACK_WINSETUP_CFG_H) && !defined(_MNTRACK_TV_SETUP_CFG_H) && !defined (MNTRACK_SETUP_QT_CFG)
/* Load mntrack.ndx */
if ((configfile=fopen("mntrack.ndx","rb"))==NULL)
 {
 write_log('^',"Can't open mntrack.ndx, run nodelist compiler.");
 FNdx=NULL;
 }
else
 {
 FNdx=NULL;TNdx=NULL;
 while(!feof(configfile))
  {
  PNdx=TNdx;
  if ((TNdx=(NdxRec far *)farcalloc(1,sizeof(NdxRec)))==NULL)
   {
   write_log('!',"Not Enough memmory to load mntrack.ndx.");
   exit_mntrack(2);
   }
  if (fread(&TNdx->address,1,sizeof(Adr4D),configfile)!=sizeof(Adr4D))
   if (FNdx==NULL)
    {
    write_log('!',"File mntrack.ndx is empty or corrupt, run nodelist compiler.");
    exit_mntrack(4);
    }
   else break;
   TNdx->next=NULL;
   if (FNdx==NULL) FNdx=TNdx;
   else PNdx->next=TNdx;
  }
  fclose(configfile);
 }
#endif

/* Load  MNTrack.aka */
if ((configfile=fopen("mntrack.aka","rb"))==NULL)
 {
 }
else
 {
 FAKA=NULL;TAKA=NULL;maxaka=0;
 while(!feof(configfile))
  {
  PAKA=TAKA;
  if ((TAKA=(AKAType far *)farcalloc(1,sizeof(AKAType)))==NULL)
   {
#ifdef _MNTRACK_WINSETUP_CFG_H
   Application->MessageBox("Not Enough memmory to load mntrack.aka.","Error",MB_ICONERROR|MB_OK);
#endif
#ifdef _MNTRACK_TV_SETUP_CFG_H
   messageBox("Not Enough memmory to load mntrack.msk.",mfError | mfOKButton);
#endif
#ifdef  MNTRACK_SETUP_QT_CFG
   QMessageBox::critical(NULL,"MNTrack Setup","Not Enough memmory to load mntrack.msk.");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
   write_log('!',"Not Enough memmory to load mntrack.aka.");
#endif
   fclose(configfile);
   unlink("mntrack.bsy");
   exit(8);
   }
  fread(&TAKA->zone,255,1,configfile);
  if (feof(configfile))
   {
   farfree(TAKA);
   break;
   }
  fread(&TAKA->net,255,1,configfile);
  fread(&TAKA->addr,255,1,configfile);
  TAKA->next=NULL;
  if (FAKA==NULL) FAKA=TAKA;
  else PAKA->next=TAKA;
  maxaka++;
  }
  fclose(configfile);
 }

/* Load mntrack.msk */
if ((configfile=fopen("mntrack.msk","rb"))==NULL)
 {
#if !defined(_MNTRACK_WINSETUP_CFG_H) && !defined(_MNTRACK_TV_SETUP_CFG_H) && !defined (MNTRACK_SETUP_QT_CFG)
write_log('^',"Can't open mntrack.msk, scaning without any user script.");
#endif
 }
else
 {
 FScr=NULL;TScr=NULL;maxact=0;
 while(!feof(configfile))
  {
  PScr=TScr;
  if ((TScr=(ScriptRec far *)farcalloc(1,sizeof(ScriptRec)))==NULL)
   {
#ifdef _MNTRACK_WINSETUP_CFG_H
   Application->MessageBox("Not Enough memmory to load mntrack.msk.","Error",MB_ICONERROR|MB_OK);
#endif
#ifdef _MNTRACK_TV_SETUP_CFG_H
   messageBox("Not Enough memmory to load mntrack.msk.",mfError | mfOKButton);
#endif
#ifdef  MNTRACK_SETUP_QT_CFG
   QMessageBox::critical(NULL,"MNTrack Setup","Not Enough memmory to load mntrack.msk.");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
   write_log('!',"Not Enough memmory to load mntrack.msk.");
#endif
   unlink("mntrack.bsy");
   exit(2);
   }
  fread(&TScr->scr,sizeof(ScriptType),1,configfile);
  if (feof(configfile))
   {
   farfree(TScr);
   break;
   }
  TScr->next=NULL;
  if (FScr==NULL) FScr=TScr;
  else PScr->next=TScr;
  maxact++;
  }
 fclose(configfile);
 }

/* load  MNTrack.dmn */
if ((configfile=fopen("mntrack.dmn","rb"))==NULL)
 {
#if !defined(_MNTRACK_WINSETUP_CFG_H) && !defined(_MNTRACK_TV_SETUP_CFG_H) && !defined (MNTRACK_SETUP_QT_CFG)
 write_log('!',"Can't open mntrack.dmn, run setup utility.");
 exit_mntrack(6);
#endif
 }
else
 {
 TDmn=NULL;FDmn=NULL;maxdmn=0;
 while(!feof(configfile))
  {
  PDmn=TDmn;
  if ((TDmn=(DmnRec far *)farcalloc(1,sizeof(DmnRec)))==NULL)
   {
#ifdef _MNTRACK_WINSETUP_CFG_H
   Application->MessageBox("Not Enough memmory to load mntrack.dmn.","Error",MB_ICONERROR|MB_OK);
#endif
#ifdef _MNTRACK_TV_SETUP_CFG_H
   messageBox("Not Enough memmory to load mntrack.dmn.",mfError | mfOKButton);
#endif
#ifdef  MNTRACK_SETUP_QT_CFG
   QMessageBox::critical(NULL,"MNTrack Setup","Not Enough memmory to load mntrack.dmn.");
#endif
#ifdef _MAIN_MNTRACK_CONFIGURATION_H
   write_log('!',"Not Enough memmory to load mntrack.dmn.");
#endif
   unlink("mntrack.bsy");
   exit(2);
   }
  fread(&TDmn->dmn.name,sizeof(DomenType),1,configfile);
  if (feof(configfile))
   {
   farfree(TDmn);
   break;
   }
  TDmn->next=NULL;
  if (FDmn==NULL) FDmn=TDmn;
  else PDmn->next=TDmn;
  maxdmn++;
  }
 fclose(configfile);
 }

/* end load */
}
//---------------------------------------------------------------------------

