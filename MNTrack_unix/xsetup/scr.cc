#include "scr.h"
#include "scr.moc"

extern ConfigType config;
extern int ConfigChanged;
extern unsigned long tact,maxact;
extern ScriptRec *FScr,*TScr,*PScr;

TScrForm::TScrForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(426,91);
setMaximumSize(426,91);
resize(426,91);
setCaption( "Scripts" );

textLabel8 = new QLabel("",this);
textLabel8->setGeometry( QRect( 10, 0, 64, 20 ) );
textLabel8->setFrameShape( QLabel::NoFrame );
textLabel8->setFrameShadow( QLabel::Plain );

textLabel9 = new QLabel("Script",this);
textLabel9->setGeometry( QRect( 10, 30, 40, 20 ) );

lineEdit10 = new QLineEdit("",this);
lineEdit10->setGeometry( QRect( 50, 30, 370, 23 ) );
connect(lineEdit10,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

pushButtonIns = new QPushButton("&Ins",this);
pushButtonIns->setGeometry( QRect( 10, 60, 50, 24 ) );
connect(pushButtonIns,SIGNAL(clicked()),this,SLOT(InsPressed()));

pushButtonDel = new QPushButton("&Del",this);
pushButtonDel->setGeometry( QRect( 70, 60, 50, 24 ) );
connect(pushButtonDel,SIGNAL(clicked()),this,SLOT(DelPressed()));

pushButtonFirst = new QPushButton("|<-",this);
pushButtonFirst->setGeometry( QRect( 130, 60, 50, 24 ) );
connect(pushButtonFirst,SIGNAL(clicked()),this,SLOT(FirstPressed()));

pushButtonPrev = new QPushButton("<-",this);
pushButtonPrev->setGeometry( QRect( 190, 60, 50, 24 ) );
connect(pushButtonPrev,SIGNAL(clicked()),this,SLOT(PrevPressed()));

pushButtonNext = new QPushButton("->",this);
pushButtonNext->setGeometry( QRect( 250, 60, 50, 24 ) );
connect(pushButtonNext,SIGNAL(clicked()),this,SLOT(NextPressed()));

pushButtonLast = new QPushButton("->|",this);
pushButtonLast->setGeometry( QRect( 310, 60, 50, 24 ) );
connect(pushButtonLast,SIGNAL(clicked()),this,SLOT(LastPressed()));

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry( QRect( 370, 60, 50, 24 ) );
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));
}
//----------------------------------------------------------------------------
void TScrForm::OkPressed()
{
GetFormData();
ConfigChanged=true;
close();
}
//----------------------------------------------------------------------------
void TScrForm::GetFormData(void)
{
strcpy(TScr->scr.name,lineEdit10->text());
}
//----------------------------------------------------------------------------
void TScrForm::SetFormData(void)
{
static char buf[255];
sprintf(buf,"%lu/%lu",tact,maxact);
textLabel8->setText(buf);
lineEdit10->setText(TScr->scr.name);

// Buttons
pushButtonDel->setDisabled(false);
pushButtonFirst->setDisabled(false);
pushButtonPrev->setDisabled(false);
pushButtonNext->setDisabled(false);
pushButtonLast->setDisabled(false);

if (FScr==TScr) 
 {
 if (TScr->next==NULL) pushButtonDel->setDisabled(true);
 pushButtonFirst->setDisabled(true);
 pushButtonPrev->setDisabled(true);
 }
if (TScr->next==NULL) 
 {
 pushButtonNext->setDisabled(true);
 pushButtonLast->setDisabled(true);
 }
}
//----------------------------------------------------------------------------
void TScrForm::EditChanged()
{
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TScrForm::InsPressed()
{
GetFormData();
maxact++;tact++;
PScr=(ScriptRec *)calloc(1,sizeof(ScriptRec));
PScr->next=TScr->next;
//*PScr->scr.name=0;
TScr->next=PScr;
TScr=PScr;
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TScrForm::DelPressed()
{
GetFormData();
if (TScr!=FScr) 
 {
 maxact--;
 PScr=TScr;
 tact=1;
 TScr=FScr;
 while (TRUE) 
  {
  if (TScr->next==PScr) break;
  TScr=(ScriptRec *)TScr->next;
  tact++;
  }
 TScr->next=PScr->next;
 free(PScr);
 } 
else if (FScr->next!=NULL) 
 {
 maxact--;
 FScr=(ScriptRec *)FScr->next;
 free(TScr);
 TScr=FScr;
 }
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TScrForm::NextPressed()
{
GetFormData();
if (TScr->next!=NULL) 
 {
 TScr=(ScriptRec *)TScr->next;
 tact++;
 }
SetFormData();
}
//----------------------------------------------------------------------------
void TScrForm::PrevPressed()
{
GetFormData();
if (TScr!=FScr) 
 {
 PScr=TScr;
 tact=1;
 TScr=FScr;
 while (TRUE) 
  {
  if (TScr->next==PScr) break;
  TScr=(ScriptRec *)TScr->next;
  tact++;
  }
 }
SetFormData();
}
//----------------------------------------------------------------------------
void TScrForm::FirstPressed()
{
GetFormData();
tact=1;
TScr=FScr;
SetFormData();
}
//----------------------------------------------------------------------------
void TScrForm::LastPressed()
{
GetFormData();
while (TScr->next!=NULL) 
 {
 TScr=(ScriptRec *)TScr->next;
 tact++;
 }
SetFormData();
}
//----------------------------------------------------------------------------
