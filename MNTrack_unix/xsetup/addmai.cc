#include "addmai.h"
#include "addmai.moc"

extern ConfigType config;
extern int ConfigChanged;
extern unsigned long taka,maxaka;
extern AKAType *FAKA,*TAKA,*PAKA;

TAddMaiForm::TAddMaiForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(384,191);
setMaximumSize(384,191);
resize(191,191);
setCaption( "Address Maintenace" );

textLabel3 = new QLabel("Main Network Address",this);
textLabel3->setGeometry( QRect( 10, 20, 135, 20 ) );

lineEdit2 = new QLineEdit("",this);
lineEdit2->setGeometry( QRect( 150, 20, 220, 23 ) );
connect(lineEdit2,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

textLabel2 = new QLabel("",this); /*Stat*/
textLabel2->setGeometry( QRect( 10, 0, 64, 20 ) );

groupBox1 = new QGroupBox("AKA",this);
groupBox1->setGeometry( QRect( 10, 40, 370, 110 ) );

lineEdit3 = new QLineEdit("",groupBox1);
lineEdit3->setGeometry( QRect( 10, 40, 40, 23 ) );
connect(lineEdit3,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

lineEdit4 = new QLineEdit("",groupBox1);
lineEdit4->setGeometry( QRect( 70, 40, 40, 23 ) );
connect(lineEdit4,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

textLabel7 = new QLabel("Netwok Address",groupBox1);
textLabel7->setGeometry( QRect( 120, 20, 100, 20 ) );

textLabel4 = new QLabel("Net",groupBox1);
textLabel4->setGeometry( QRect( 70, 20, 40, 20 ) );

textLabel5 = new QLabel(":",groupBox1);
textLabel5->setGeometry( QRect( 50, 20, 16, 20 ) );

textLabel6 = new QLabel("Zone",groupBox1);
textLabel6->setGeometry( QRect( 10, 20, 33, 20 ) );

lineEdit5 = new QLineEdit("",groupBox1);
lineEdit5->setGeometry( QRect( 120, 40, 240, 23 ) );
connect(lineEdit5,SIGNAL(textChanged(const QString &)),this,SLOT(EditChanged()));

pushButtonIns = new QPushButton("&Ins",groupBox1);
pushButtonIns->setGeometry( QRect( 10, 70, 50, 24 ) );
connect(pushButtonIns,SIGNAL(clicked()),this,SLOT(InsPressed()));

pushButtonDel = new QPushButton("&Del",groupBox1);
pushButtonDel->setGeometry( QRect( 70, 70, 50, 24 ) );
connect(pushButtonDel,SIGNAL(clicked()),this,SLOT(DelPressed()));

pushButtonFirst = new QPushButton("|<-",groupBox1);;
pushButtonFirst->setGeometry( QRect( 130, 70, 50, 24 ) );
connect(pushButtonFirst,SIGNAL(clicked()),this,SLOT(FirstPressed()));

pushButtonPrev = new QPushButton("<-",groupBox1);
pushButtonPrev->setGeometry( QRect( 190, 70, 50, 24 ) );
connect(pushButtonPrev,SIGNAL(clicked()),this,SLOT(PrevPressed()));

pushButtonNext = new QPushButton("->",groupBox1);
pushButtonNext->setGeometry( QRect( 250, 70, 50, 24 ) );
connect(pushButtonNext,SIGNAL(clicked()),this,SLOT(NextPressed()));

pushButtonLast = new QPushButton("->|",groupBox1);
pushButtonLast->setGeometry( QRect( 310, 70, 50, 24 ) );
connect(pushButtonLast,SIGNAL(clicked()),this,SLOT(LastPressed()));

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(150/*X*/,160/*Y*/,87/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));
}
//----------------------------------------------------------------------------
void TAddMaiForm::OkPressed()
{
GetFormData();
ConfigChanged=true;
close();
}
//----------------------------------------------------------------------------
void TAddMaiForm::GetFormData(void)
{
strcpy(config.bouadr,lineEdit2->text());
strcpy(TAKA->zone,lineEdit3->text());
strcpy(TAKA->net,lineEdit4->text());
strcpy(TAKA->addr,lineEdit5->text());
}
//----------------------------------------------------------------------------
void TAddMaiForm::SetFormData(void)
{
static char buf[255];
sprintf(buf,"%lu/%lu",taka,maxaka);
textLabel2->setText(buf);
lineEdit2->setText(config.bouadr);
lineEdit3->setText(TAKA->zone);
lineEdit4->setText(TAKA->net);
lineEdit5->setText(TAKA->addr);

pushButtonDel->setDisabled(false);
if (FAKA==TAKA)
 {
 pushButtonFirst->setDisabled(true);
 pushButtonPrev->setDisabled(true);
 if (TAKA->next==NULL) pushButtonDel->setDisabled(true);
 }
else
 {
 pushButtonFirst->setDisabled(false);
 pushButtonPrev->setDisabled(false);
 }

if (TAKA->next==NULL)
 {
 pushButtonLast->setDisabled(true);
 pushButtonNext->setDisabled(true);
 }
else
 {
 pushButtonLast->setDisabled(false);
 pushButtonNext->setDisabled(false);
 }
}
//----------------------------------------------------------------------------
void TAddMaiForm::EditChanged()
{
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TAddMaiForm::InsPressed()
{
GetFormData();
maxaka++;taka++;
PAKA=(AKAType *)calloc(sizeof(AKAType),1);
PAKA->next=TAKA->next;
TAKA->next=PAKA;
TAKA=PAKA;
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TAddMaiForm::DelPressed()
{
GetFormData();
if (TAKA!=FAKA) 
 {
 maxaka--;
 PAKA=TAKA;
 taka=1;
 TAKA=FAKA;
 while (TRUE) 
  {
  if (TAKA->next==PAKA) break;
  TAKA=(AKAType *)TAKA->next;
  taka++;
  } 
 TAKA->next=PAKA->next;
 free(PAKA);
 } 
else if (FAKA->next!=NULL) 
 {
 maxaka--;
 FAKA=(AKAType *)FAKA->next;
 free(TAKA);
 TAKA=FAKA;
 }
SetFormData();
ConfigChanged=true;
}
//----------------------------------------------------------------------------
void TAddMaiForm::NextPressed()
{
GetFormData();
if (TAKA->next!=NULL) 
 {
 TAKA=(AKAType *)TAKA->next;
 taka++;
 }
SetFormData();
}
//----------------------------------------------------------------------------
void TAddMaiForm::PrevPressed()
{
GetFormData();
if (TAKA!=FAKA) 
 {
 PAKA=TAKA;
 taka=1;
 TAKA=FAKA;
 while (TRUE) 
  {
  if (TAKA->next==PAKA) break;
  TAKA=(AKAType *)TAKA->next;
  taka++;
  } 
 }
SetFormData();
}
//----------------------------------------------------------------------------
void TAddMaiForm::FirstPressed()
{
GetFormData();
taka=1;
TAKA=FAKA;
SetFormData();
}
//----------------------------------------------------------------------------
void TAddMaiForm::LastPressed()
{
GetFormData();
while (TAKA->next!=NULL) 
 {
 TAKA=(AKAType *)TAKA->next;
 taka++;
 }
SetFormData();
}
//----------------------------------------------------------------------------
