#ifndef _MNTACK_PACKING_OPTIONS_H
#define _MNTACK_PACKING_OPTIONS_H

#include <qwidget.h>
#include <qvariant.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <mntcfg.h>

class TPackOptForm : public QWidget
{
    Q_OBJECT

public:
    TPackOptForm( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );

    QButtonGroup* buttonGroup2;
    QCheckBox* checkBox2;
    QCheckBox* checkBox3;
    QCheckBox* checkBox4;
    QCheckBox* checkBox5;
    QCheckBox* checkBox6;
    QCheckBox* checkBox7;
    QCheckBox* checkBox8;
    QCheckBox* checkBox9;
    QCheckBox* checkBox10;
    QCheckBox* checkBox11;
    QCheckBox* checkBox12;
    QCheckBox* checkBox13;
    QCheckBox* checkBox14;
    QCheckBox* checkBox15;
    QCheckBox* checkBox16;
    QButtonGroup* buttonGroup2_2;
    QCheckBox* checkBox17;
    QCheckBox* checkBox18;
    QCheckBox* checkBox19;
    QCheckBox* checkBox20;
    QCheckBox* checkBox21;
    QCheckBox* checkBox22;
    QCheckBox* checkBox23;
    QCheckBox* checkBox24;
    QCheckBox* checkBox25;
    QCheckBox* checkBox26;
    QCheckBox* checkBox27;
    QCheckBox* checkBox28;
    QCheckBox* checkBox29;
    QCheckBox* checkBox30;
    QCheckBox* checkBox31;
    QCheckBox* checkBox1;

protected:
    QGridLayout* buttonGroup2Layout;
    QGridLayout* buttonGroup2_2Layout;
    QPushButton *okButton,*CancelButton;

public slots:
    void OkPressed();
};

#endif