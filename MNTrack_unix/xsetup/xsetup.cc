#include "xsetup.h"
#include "xsetup.moc"

extern ConfigType config;
ScriptRec far *FScr=NULL,far *TScr=NULL,far *PScr=NULL;
DmnRec far *FDmn=NULL,far *TDmn=NULL,far *PDmn=NULL;
AKAType far *FAKA=NULL,far *TAKA=NULL,far *PAKA=NULL;
long tact=1,maxact=1,tdmn=1,maxdmn=1,taka=1,maxaka=1;
int ConfigChanged=false;
//---------------------------------------------------------------------------
XSetup::XSetup( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
this->setCaption("MNTrack X Setup");
    QPopupMenu *gener = new QPopupMenu( this );
    CHECK_PTR( gener );
    gener->insertItem( "&General Options", this, SLOT(genopts()));
    gener->insertItem( "&Address Maintenance", this, SLOT(addrmai()));
//    gener->setItemEnabled(1,false);
    gener->insertItem( "&Path and file Names", this, SLOT(pnames()));
    gener->insertItem( "&Log Options", this, SLOT(logopts()));
    gener->insertItem( "&Message Options", this, SLOT(mopts()));
    gener->insertSeparator();
//    gener->insertItem( "&Quit", this, SLOT(quit()));
    gener->insertItem( "&Quit", this, SLOT(close()));

    QPopupMenu *scrmenu = new QPopupMenu( this );
    CHECK_PTR( scrmenu );
    scrmenu->insertItem( "Script &Options", this, SLOT(scropts()));
    scrmenu->insertItem( "&Scripts", this, SLOT(scrmain()));

    QPopupMenu *packmenu = new QPopupMenu( this );
    CHECK_PTR( packmenu );
    packmenu->insertItem( "&Packing Options", this, SLOT(popts()));
    packmenu->insertItem( "&Domains and Outbounds", this, SLOT(domout()));

    QPopupMenu *help = new QPopupMenu( this );
    CHECK_PTR( help );
    help->insertItem( "&About", this, SLOT(about()), CTRL+Key_H );

    menu = new QMenuBar( this );
    CHECK_PTR( menu );
    menu->insertItem( "&General", gener);
    menu->insertItem( "&Scripts", scrmenu);
    menu->insertItem( "&Packing", packmenu);
    menu->insertItem( "&Help", help );
GenOptsForm = new TGenOptsForm;
PFNamesForm = new TPFNamesForm;
LogOptForm = new TLogOptForm;
MesOptsForm = new TMesOptsForm;
PackOptForm = new TPackOptForm;
ScriptOptForm = new TScriptOptForm;
AddMaiForm = new TAddMaiForm;
DmnForm = new TDmnForm;
ScrForm = new TScrForm;
}
//---------------------------------------------------------------------------
void XSetup::genopts()
{
char buf[6];
GenOptsForm->Edit1->setText(config.sysopname);
sprintf(buf,"%u",config.uuedepth);
GenOptsForm->Edit3->setText(buf);
GenOptsForm->show();
}
//---------------------------------------------------------------------------
void XSetup::addrmai()
{
if (FAKA==NULL) 
 {
 FAKA=(AKAType *)calloc(1,sizeof(AKAType));
 FAKA->next=NULL;
 maxaka=1;
 }
TAKA=FAKA;
taka=1;
AddMaiForm->SetFormData();
AddMaiForm->show();
}
//---------------------------------------------------------------------------
void XSetup::pnames()
{
PFNamesForm->Edit1->setText(config.scanfiles);
PFNamesForm->Edit2->setText(config.pktout);
PFNamesForm->Edit3->setText(config.out);
PFNamesForm->show();
}
//---------------------------------------------------------------------------
void XSetup::logopts()
{
LogOptForm->Edit1->setText(config.logfile);
LogOptForm->Box1->setChecked(config.loglevel&1);
LogOptForm->Box2->setChecked(config.loglevel&2);
LogOptForm->Box3->setChecked(config.loglevel&4);
LogOptForm->Box4->setChecked(config.loglevel&8);
LogOptForm->Box5->setChecked(config.loglevel&16);
LogOptForm->Box6->setChecked(config.loglevel&32);
LogOptForm->Box7->setChecked(config.loglevel&64);
LogOptForm->Box8->setChecked(config.loglevel&128);
LogOptForm->Box9->setChecked(config.loglevel&256);
LogOptForm->Box10->setChecked(config.loglevel&512);
LogOptForm->show();
}
//---------------------------------------------------------------------------
void XSetup::mopts()
{
MesOptsForm->Box1->setChecked(config.updatelastread);
MesOptsForm->Edit1->setText(config.flags);
MesOptsForm->show();
}
//---------------------------------------------------------------------------
void XSetup::scropts()
{
ScriptOptForm->checkBox1->setChecked(config.ksanswer);
switch(config.stop)
 {
 case 0:
  ScriptOptForm->radioButton1->setChecked(1);
 break;
 case 1:
  ScriptOptForm->radioButton2->setChecked(1);
 break;
 case 2:
  ScriptOptForm->radioButton3->setChecked(1);
 }
ScriptOptForm->show();
}
//---------------------------------------------------------------------------
void XSetup::scrmain()
{
if (FScr==NULL) 
 {
 FScr=(ScriptRec *)calloc(1,sizeof(ScriptRec));
 FScr->next=NULL;
 }
TScr=FScr;
tact=1;
ScrForm->SetFormData();
ScrForm->show();
}
//---------------------------------------------------------------------------
void XSetup::popts()
{
PackOptForm->checkBox1->setChecked(config.insintl);
 PackOptForm->checkBox2->setChecked(config.clearbefore&1);
 PackOptForm->checkBox3->setChecked(config.clearbefore&2);
 PackOptForm->checkBox4->setChecked(config.clearbefore&4);
 PackOptForm->checkBox5->setChecked(config.clearbefore&8);
 PackOptForm->checkBox6->setChecked(config.clearbefore&16);
 PackOptForm->checkBox7->setChecked(config.clearbefore&32);
 PackOptForm->checkBox8->setChecked(config.clearbefore&64);
 PackOptForm->checkBox9->setChecked(config.clearbefore&128);
 PackOptForm->checkBox10->setChecked(config.clearbefore&256);
 PackOptForm->checkBox11->setChecked(config.clearbefore&512);
 PackOptForm->checkBox12->setChecked(config.clearbefore&1024);
 PackOptForm->checkBox13->setChecked(config.clearbefore&2048);
 PackOptForm->checkBox14->setChecked(config.clearbefore&4096);
 PackOptForm->checkBox15->setChecked(config.clearbefore&8192);
 PackOptForm->checkBox16->setChecked(config.clearbefore&16384);
 PackOptForm->checkBox17->setChecked(config.setafter&1);
 PackOptForm->checkBox18->setChecked(config.setafter&2);
 PackOptForm->checkBox19->setChecked(config.setafter&4);
 PackOptForm->checkBox20->setChecked(config.setafter&8);
 PackOptForm->checkBox21->setChecked(config.setafter&16);
 PackOptForm->checkBox22->setChecked(config.setafter&32);
 PackOptForm->checkBox23->setChecked(config.setafter&64);
 PackOptForm->checkBox24->setChecked(config.setafter&128);
 PackOptForm->checkBox25->setChecked(config.setafter&256);
 PackOptForm->checkBox26->setChecked(config.setafter&512);
 PackOptForm->checkBox27->setChecked(config.setafter&1024);
 PackOptForm->checkBox28->setChecked(config.setafter&2048);
 PackOptForm->checkBox29->setChecked(config.setafter&4096);
 PackOptForm->checkBox30->setChecked(config.setafter&8192);
 PackOptForm->checkBox31->setChecked(config.setafter&16384);
PackOptForm->show();
}
//---------------------------------------------------------------------------
void XSetup::domout()
{
if (FDmn==NULL) 
 {
 FDmn=(DmnRec *)calloc(1,sizeof(DmnRec));
 FDmn->next=NULL;
 maxdmn=1;
 }
tdmn=1;
TDmn=FDmn;
DmnForm->SetFormData();
DmnForm->show();
}
//---------------------------------------------------------------------------
void XSetup::about()
{
static char buf[255];
sprintf(buf,"MNTrack %s\nX Window Setup",version);
QMessageBox::about( this, "About",buf);
}
//---------------------------------------------------------------------------
int main( int argc, char ** argv )
{
XSetupApp a( argc, argv );
LoadConfig();
XSetup m;
a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
a.setMainWidget( &m );
m.show();
return a.exec();
}
//---------------------------------------------------------------------------
