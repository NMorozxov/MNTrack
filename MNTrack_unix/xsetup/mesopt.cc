#include "mesopt.h"
#include "mesopt.moc"

extern ConfigType config;
extern int ConfigChanged;

TMesOptsForm::TMesOptsForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(260,75);
setMaximumSize(260,75);
resize(260,75);
setCaption( "Message Options" );

Box1 = new QCheckBox("Update lastread",this);
Box1->setGeometry(70,0,160,20);

Label3 = new QLabel("Non Standart Flags",this);
Label3->setGeometry(10,20,129,20);

Edit1 = new QLineEdit( this );
Edit1->setGeometry(130,20,120,20);
Edit1->setMaxLength(5);

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(33/*X*/,45/*Y*/,80/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(146/*X*/,45/*Y*/,80/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TMesOptsForm::OkPressed()
{
ConfigChanged=true;
config.updatelastread=Box1->isChecked();
strcpy(config.flags,Edit1->text());
close();
}
