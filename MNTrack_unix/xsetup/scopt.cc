#include "scopt.h"
#include "scopt.moc"

extern ConfigType config;
extern int ConfigChanged;

TScriptOptForm::TScriptOptForm( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, WType_Modal )
{
    setCaption("Script Options");
    setMinimumSize(185,181);
    setMaximumSize(185,181);
    resize( QSize(185, 181).expandedTo(minimumSizeHint()) );

    checkBox1 = new QCheckBox("Keep MNTrack Answers",this );
    checkBox1->setGeometry( QRect( 10, 10, 170, 21 ) );

    buttonGroup1 = new QButtonGroup(this, "After DELETE/MOVE do" );
    buttonGroup1->setGeometry( QRect( 10, 40, 170, 108 ) );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    radioButton1 = new QRadioButton("Nothing",buttonGroup1 );
    buttonGroup1Layout->addWidget( radioButton1, 0, 0 );

    radioButton2 = new QRadioButton("Stop Current Script",buttonGroup1 );
    buttonGroup1Layout->addWidget( radioButton2, 1, 0 );

    radioButton3 = new QRadioButton("Stop All Scripts",buttonGroup1 );
    buttonGroup1Layout->addWidget( radioButton3, 2, 0 );

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(10/*X*/,150/*Y*/,80/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(100/*X*/,150/*Y*/,80/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TScriptOptForm::OkPressed()
{
ConfigChanged=true;
config.ksanswer=checkBox1->isChecked();
if (radioButton1->isChecked()) config.stop=0;
if (radioButton2->isChecked()) config.stop=1;
if (radioButton3->isChecked()) config.stop=2;
close();
}
