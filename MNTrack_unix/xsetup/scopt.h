#ifndef _MNTACK_SCRIPT_OPTIONS_H
#define _MNTACK_SCRIPT_OPTIONS_H

#include <qwidget.h>
#include <qvariant.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <mntcfg.h>

class TScriptOptForm : public QWidget
{
    Q_OBJECT

public:
    TScriptOptForm( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    QButtonGroup* buttonGroup1;
    QRadioButton* radioButton1;
    QRadioButton* radioButton2;
    QRadioButton* radioButton3;
    QCheckBox* checkBox1;
protected:
    QGridLayout* buttonGroup1Layout;
    QPushButton *okButton,*CancelButton;
public slots:
    void OkPressed();
};

#endif