#include "logopt.h"
#include "logopt.moc"

extern ConfigType config;
extern int ConfigChanged;

TLogOptForm::TLogOptForm( QWidget *parent, const char *name,WFlags f)
    : QWidget( parent, name, WType_Modal )
{
setMinimumSize(260,160);
setMaximumSize(260,160);
resize(260,160);
setCaption( "Log Options");

Label1 = new QLabel("Log File",this);
Label1->setGeometry(10,0,100,20);

Edit1 = new QLineEdit( this );
Edit1->setGeometry(100,0,150,20);
Edit1->setMaxLength(255);

Box1 = new QCheckBox("Error",this);
Box1->setGeometry(30,25,100,20);

Box2 = new QCheckBox("Warning",this);
Box2->setGeometry(30,45,100,20);

Box3 = new QCheckBox("User",this);
Box3->setGeometry(30,65,100,20);

Box4 = new QCheckBox("Netmail",this);
Box4->setGeometry(30,85,100,20);

Box5 = new QCheckBox("BSO",this);
Box5->setGeometry(30,105,100,20);

Box6 = new QCheckBox("Semaphore",this);
Box6->setGeometry(140,25,100,20);

Box7 = new QCheckBox("File",this);
Box7->setGeometry(140,45,100,20);

Box8 = new QCheckBox("Debug",this);
Box8->setGeometry(140,65,100,20);

Box9 = new QCheckBox("External",this);
Box9->setGeometry(140,85,100,20);

Box10 = new QCheckBox("Unknown",this);
Box10->setGeometry(140,105,100,20);

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(33/*X*/,130/*Y*/,80/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(146/*X*/,130/*Y*/,80/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TLogOptForm::OkPressed()
{
ConfigChanged=true;
strcpy(config.logfile,Edit1->text());
config.loglevel = (UINT_2)(Box1->isChecked()+
                   Box2->isChecked()*2+
                   Box3->isChecked()*4+
                   Box4->isChecked()*8+
                   Box5->isChecked()*16+
                   Box6->isChecked()*32+
                   Box7->isChecked()*64+
                   Box8->isChecked()*128+
                   Box9->isChecked()*256+
                   Box10->isChecked()*512);
close();
}
