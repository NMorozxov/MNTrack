#include "genopts.h"
#include "genopts.moc"

extern ConfigType config;
extern int ConfigChanged;

TGenOptsForm::TGenOptsForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(260,75);
setMaximumSize(260,75);
resize(260,75);
setCaption( "General Options" );

Label1 = new QLabel("SysOp Name",this);
Label1->setGeometry(10,0,100,20);
Label3 = new QLabel("UUE Depth",this);
Label3->setGeometry(10,20,100,20);

Edit1 = new QLineEdit( this );
Edit1->setGeometry(100,0,150,20);
Edit1->setMaxLength(255);

Edit3 = new QLineEdit( this );
Edit3->setGeometry(100,20,150,20);
Edit3->setMaxLength(5);

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(33/*X*/,45/*Y*/,80/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(146/*X*/,45/*Y*/,80/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TGenOptsForm::OkPressed()
{
ConfigChanged=true;
strcpy(config.sysopname,Edit1->text());
config.uuedepth=atoi(Edit3->text());
close();
}
