#include "dmn.h"
#include "dmn.moc"

extern ConfigType config;
extern int ConfigChanged;
extern DmnRec *FDmn,*TDmn,*PDmn;
extern unsigned long tdmn,maxdmn;

TDmnForm::TDmnForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(432,222);
setMaximumSize(432,222);
resize(432,222);
setCaption( "Domains and outbounds" );

textLabel8 = new QLabel("",this);
textLabel8->setGeometry( QRect( 10, 0, 64, 20 ) );
textLabel8->setFrameShape( QLabel::NoFrame );
textLabel8->setFrameShadow( QLabel::Plain );

textLabel10 = new QLabel("Name",this);
textLabel10->setGeometry( QRect( 10, 20, 70, 20 ) );

textLabel11 = new QLabel("Outbound",this);
textLabel11->setGeometry( QRect( 10, 50, 71, 20 ) );

textLabel12 = new QLabel("Main Zone",this);
textLabel12->setGeometry( QRect( 10, 130, 71, 20 ) );

textLabel13 = new QLabel("Zones In Domain",this);
textLabel13->setGeometry( QRect( 10, 160, 103, 20 ) );

checkBox1 = new QCheckBox("Default",this);
checkBox1->setGeometry( QRect( 10, 80, 120, 21 ) );
connect(checkBox1,SIGNAL(toggled(bool)),this,SLOT(EditChanged()));

checkBox2 = new QCheckBox("Have Main Zone",this);
checkBox2->setGeometry( QRect( 10, 110, 120, 21 ) );
connect(checkBox2,SIGNAL(toggled(bool)),this,SLOT(EditChanged()));

lineEdit12 = new QLineEdit("",this);
lineEdit12->setGeometry( QRect( 90, 20, 330, 23 ) );
connect(lineEdit12,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

lineEdit13 = new QLineEdit("",this);
lineEdit13->setGeometry( QRect( 90, 50, 330, 23 ) );
connect(lineEdit13,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

lineEdit14 = new QLineEdit("",this);
lineEdit14->setGeometry( QRect( 130, 130, 60, 23 ) );
connect(lineEdit14,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

lineEdit15 = new QLineEdit("",this);
lineEdit15->setGeometry( QRect( 130, 160, 290, 23 ) );
connect(lineEdit15,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

pushButtonIns = new QPushButton("&Ins",this);
pushButtonIns->setGeometry( QRect( 10, 190, 50, 24 ) );
connect(pushButtonIns,SIGNAL(clicked()),this,SLOT(InsPressed()));

pushButtonDel = new QPushButton("&Del",this);
pushButtonDel->setGeometry( QRect( 70, 190, 50, 24 ) );
connect(pushButtonDel,SIGNAL(clicked()),this,SLOT(DelPressed()));

pushButtonFirst = new QPushButton("|<-",this);
pushButtonFirst->setGeometry( QRect( 130, 190, 50, 24 ) );
connect(pushButtonFirst,SIGNAL(clicked()),this,SLOT(FirstPressed()));

pushButtonPrev = new QPushButton("<-",this);
pushButtonPrev->setGeometry( QRect( 190, 190, 50, 24 ) );
connect(pushButtonPrev,SIGNAL(clicked()),this,SLOT(PrevPressed()));

pushButtonNext = new QPushButton("->",this);
pushButtonNext->setGeometry( QRect( 250, 190, 50, 24 ) );
connect(pushButtonNext,SIGNAL(clicked()),this,SLOT(NextPressed()));

pushButtonLast = new QPushButton("->|",this);
pushButtonLast->setGeometry( QRect( 310, 190, 50, 24 ) );
connect(pushButtonLast,SIGNAL(clicked()),this,SLOT(LastPressed()));

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry( QRect( 370, 190, 50, 24 ) );
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));
}
//----------------------------------------------------------------------------
void TDmnForm::OkPressed()
{
GetFormData();
ConfigChanged=true;
close();
}
//----------------------------------------------------------------------------
void TDmnForm::GetFormData(void)
{
strcpy(TDmn->dmn.name,lineEdit12->text());
strcpy(TDmn->dmn.out,lineEdit13->text());
TDmn->dmn.Default=checkBox1->isChecked();
TDmn->dmn.HaveMainZone=checkBox2->isChecked();
TDmn->dmn.MainZone=(UINT_2)atoi(lineEdit14->text());
strcpy(TDmn->dmn.zones,lineEdit15->text());
}
//----------------------------------------------------------------------------
void TDmnForm::SetFormData(void)
{
static char buf[255];
sprintf(buf,"%lu/%lu",tdmn,maxdmn);
textLabel8->setText(buf);

lineEdit12->setText(TDmn->dmn.name);
lineEdit13->setText(TDmn->dmn.out);
checkBox1->setChecked(TDmn->dmn.Default);
checkBox2->setChecked(TDmn->dmn.HaveMainZone);
sprintf(buf,"%u",TDmn->dmn.MainZone);
lineEdit14->setText(buf);
lineEdit15->setText(TDmn->dmn.zones);
// Main Zone
lineEdit14->setDisabled(!checkBox2->isChecked());
// Buttons
pushButtonDel->setDisabled(false);
pushButtonFirst->setDisabled(false);
pushButtonPrev->setDisabled(false);
pushButtonNext->setDisabled(false);
pushButtonLast->setDisabled(false);

if (FDmn==TDmn) 
 {
 if (TDmn->next==NULL) pushButtonDel->setDisabled(true);
 pushButtonFirst->setDisabled(true);
 pushButtonPrev->setDisabled(true);
 }
if (TDmn->next==NULL) 
 {
 pushButtonNext->setDisabled(true);
 pushButtonLast->setDisabled(true);
 }
}
//----------------------------------------------------------------------------
void TDmnForm::EditChanged()
{
lineEdit14->setDisabled(!checkBox2->isChecked());
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TDmnForm::InsPressed()
{
GetFormData();
maxdmn++;tdmn++;
PDmn=(DmnRec *)calloc(1,sizeof(DmnRec));
PDmn->next=TDmn->next;
TDmn->next=PDmn;
TDmn=PDmn;
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TDmnForm::DelPressed()
{
GetFormData();
if (TDmn!=FDmn) 
 {
 maxdmn--;
 PDmn=TDmn;
 tdmn=1;
 TDmn=FDmn;
 while (TRUE) 
  {
  if (TDmn->next==PDmn) break;
  TDmn=(DmnRec *)TDmn->next;
  tdmn++;
  } /* while */
 TDmn->next=PDmn->next;
 free(PDmn);
 } 
else if (FDmn->next!=NULL) 
 {
 maxdmn--;
 FDmn=(DmnRec *)FDmn->next;
 free(TDmn);
 TDmn=FDmn;
 }
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TDmnForm::NextPressed()
{
GetFormData();
if (TDmn->next!=NULL) {TDmn=(DmnRec *)TDmn->next;tdmn++;}
SetFormData();
}
//----------------------------------------------------------------------------
void TDmnForm::PrevPressed()
{
GetFormData();
if (TDmn!=FDmn) 
 {
 PDmn=TDmn;
 tdmn=1;
 TDmn=FDmn;
 while (TRUE) 
  {
  if (TDmn->next==PDmn) break;
  TDmn=(DmnRec *)TDmn->next;
  tdmn++;
  }
 }
SetFormData();
}
//----------------------------------------------------------------------------
void TDmnForm::FirstPressed()
{
GetFormData();
tdmn=1;
TDmn=FDmn;
SetFormData();
}
//----------------------------------------------------------------------------
void TDmnForm::LastPressed()
{
GetFormData();
while (TDmn->next!=NULL) {TDmn=(DmnRec *)TDmn->next;tdmn++;}
SetFormData();
}
//----------------------------------------------------------------------------
