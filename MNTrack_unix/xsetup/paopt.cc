#include "paopt.h"
#include "paopt.moc"

extern ConfigType config;
extern int ConfigChanged;

TPackOptForm::TPackOptForm( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, WType_Modal )
{
    setCaption("Packing Options");
    setMinimumSize(400,231);
    setMaximumSize(400,231);
    resize( QSize(400, 231).expandedTo(minimumSizeHint()) );

    buttonGroup2 = new QButtonGroup( this, "Clear Before PACK" );
    buttonGroup2->setGeometry( QRect( 10, 30, 186, 162 ) );
    buttonGroup2->setFrameShape( QButtonGroup::GroupBoxPanel );
    buttonGroup2->setFrameShadow( QButtonGroup::Sunken );
    buttonGroup2->setColumnLayout(0, Qt::Vertical );
    buttonGroup2->layout()->setSpacing( 6 );
    buttonGroup2->layout()->setMargin( 11 );
    buttonGroup2Layout = new QGridLayout( buttonGroup2->layout() );
    buttonGroup2Layout->setAlignment( Qt::AlignTop );

    checkBox2 = new QCheckBox("PVT",buttonGroup2);
    buttonGroup2Layout->addWidget( checkBox2, 0, 0 );

    checkBox3 = new QCheckBox("CRA",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox3, 1, 0 );

    checkBox4 = new QCheckBox("RCV",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox4, 2, 0 );

    checkBox5 = new QCheckBox("SNT",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox5, 3, 0 );

    checkBox6 = new QCheckBox("ATT",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox6, 4, 0 );

    checkBox7 = new QCheckBox("TRS",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox7, 0, 1 );

    checkBox8 = new QCheckBox("ORP",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox8, 1, 1 );

    checkBox9 = new QCheckBox("K/S",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox9, 2, 1 );

    checkBox10 = new QCheckBox("LOC",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox10, 3, 1 );

    checkBox11 = new QCheckBox("HLD",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox11, 4, 1 );

    checkBox12 = new QCheckBox("FRQ",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox12, 0, 2 );

    checkBox13 = new QCheckBox("RRQ",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox13, 1, 2 );

    checkBox14 = new QCheckBox("RRC",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox14, 2, 2 );

    checkBox15 = new QCheckBox("ARQ",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox15, 3, 2 );

    checkBox16 = new QCheckBox("URQ",buttonGroup2 );
    buttonGroup2Layout->addWidget( checkBox16, 4, 2 );

    buttonGroup2_2 = new QButtonGroup( this, "Set After PACK" );
    buttonGroup2_2->setGeometry( QRect( 200, 30, 186, 162 ) );
    buttonGroup2_2->setColumnLayout(0, Qt::Vertical );
    buttonGroup2_2->layout()->setSpacing( 6 );
    buttonGroup2_2->layout()->setMargin( 11 );
    buttonGroup2_2Layout = new QGridLayout( buttonGroup2_2->layout() );
    buttonGroup2_2Layout->setAlignment( Qt::AlignTop );

    checkBox17 = new QCheckBox("PVT",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox17, 0, 0 );

    checkBox18 = new QCheckBox("CRA",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox18, 1, 0 );

    checkBox19 = new QCheckBox("RCV",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox19, 2, 0 );

    checkBox20 = new QCheckBox("SNT",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox20, 3, 0 );

    checkBox21 = new QCheckBox("ATT",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox21, 4, 0 );

    checkBox22 = new QCheckBox("TRS",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox22, 0, 1 );

    checkBox23 = new QCheckBox("ORP",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox23, 1, 1 );

    checkBox24 = new QCheckBox("K/S",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox24, 2, 1 );

    checkBox25 = new QCheckBox("LOC",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox25, 3, 1 );

    checkBox26 = new QCheckBox("HLD",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox26, 4, 1 );

    checkBox27 = new QCheckBox("FRQ",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox27, 0, 2 );

    checkBox28 = new QCheckBox("RRQ",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox28, 1, 2 );

    checkBox29 = new QCheckBox("RRC",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox29, 2, 2 );

    checkBox30 = new QCheckBox("ARQ",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox30, 3, 2 );

    checkBox31 = new QCheckBox("URQ",buttonGroup2_2 );
    buttonGroup2_2Layout->addWidget( checkBox31, 4, 2 );

    checkBox1 = new QCheckBox("Insert INTL Kludge",this);
    checkBox1->setGeometry( QRect( 130, 0, 130, 21 ) );

okButton = new QPushButton( "&Ok", this );
okButton->setGeometry(100/*X*/,200/*Y*/,87/*Width*/,24/*Height*/);
connect(okButton,SIGNAL(clicked()),this,SLOT(OkPressed()));

CancelButton = new QPushButton( "&Cancel", this );
CancelButton->setGeometry(210/*X*/,200/*Y*/,87/*Width*/,24/*Height*/);
connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void TPackOptForm::OkPressed()
{
ConfigChanged=true;
 config.insintl=checkBox1->isChecked();
 config.clearbefore=(UINT_2)(checkBox2->isChecked()+
                    checkBox3->isChecked()*2+
                    checkBox4->isChecked()*4+
                    checkBox5->isChecked()*8+
                    checkBox6->isChecked()*16+
                    checkBox7->isChecked()*32+
                    checkBox8->isChecked()*64+
                    checkBox9->isChecked()*128+
                    checkBox10->isChecked()*256+
                    checkBox11->isChecked()*512+
                    checkBox12->isChecked()*1024+
                    checkBox13->isChecked()*2048+
                    checkBox14->isChecked()*4096+
                    checkBox15->isChecked()*8192+
                    checkBox16->isChecked()*16384
                    );
 config.setafter=(UINT_2)(checkBox17->isChecked()+
                 checkBox18->isChecked()*2+
                 checkBox19->isChecked()*4+
                 checkBox20->isChecked()*8+
                 checkBox21->isChecked()*16+
                 checkBox22->isChecked()*32+
                 checkBox23->isChecked()*64+
                 checkBox24->isChecked()*128+
                 checkBox25->isChecked()*256+
                 checkBox26->isChecked()*512+
                 checkBox27->isChecked()*1024+
                 checkBox28->isChecked()*2048+
                 checkBox29->isChecked()*4096+
                 checkBox30->isChecked()*8192+
                 checkBox31->isChecked()*16384
                 );

close();
}
