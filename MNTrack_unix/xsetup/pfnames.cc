#include "pfnames.h"
#include "pfnames.moc"

extern ConfigType config;
extern int ConfigChanged;

TPFNamesForm::TPFNamesForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
char buf[6];

setMinimumSize(260,90);
setMaximumSize(260,90);
resize(260,90);
setCaption( "Path And File Names");

Label1 = new QLabel("Scan Files",this);
Label1->setGeometry(10,0,100,20);
Label2 = new QLabel("PKT Outbound",this);
Label2->setGeometry(10,20,100,20);
Label3 = new QLabel("Outbound",this);
Label3->setGeometry(10,40,100,20);

Edit1 = new QLineEdit( this );
Edit1->setGeometry(100,0,150,20);
Edit1->setMaxLength(255);

Edit2 = new QLineEdit( this );
Edit2->setGeometry(100,20,150,20);
Edit2->setMaxLength(255);

Edit3 = new QLineEdit( this );
Edit3->setGeometry(100,40,150,20);
Edit3->setMaxLength(255);

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(33/*X*/,60/*Y*/,80/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(146/*X*/,60/*Y*/,80/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TPFNamesForm::OkPressed()
{
ConfigChanged=true;
strcpy(config.scanfiles,Edit1->text());
strcpy(config.pktout,Edit2->text());
strcpy(config.out,Edit3->text());
close();
}
