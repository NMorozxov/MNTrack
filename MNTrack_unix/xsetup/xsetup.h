#ifndef _MN_XSETUP_H
#define _MN_XSETUP_H

#include <stdio.h>
#include <qwidget.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qkeycode.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include "genopts.h"
#include "cfg.h"
#include "pfnames.h"
#include "logopt.h"
#include "mesopt.h"
#include "xsetapp.h"
#include "version.h"
#include "paopt.h"
#include "scopt.h"
#include "addmai.h"
#include "dmn.h"
#include "scr.h"

class XSetup : public QWidget
{
    Q_OBJECT
public:
    XSetup( QWidget *parent=0, const char *name=0 );

public slots:
    void genopts();
    void addrmai();
    void pnames();
    void logopts();
    void mopts();
//    void quit();
    void scropts();
    void scrmain();
    void popts();
    void domout();
    void about();

private:
    QMenuBar *menu;
    TGenOptsForm *GenOptsForm;
    TPFNamesForm *PFNamesForm;
    TLogOptForm *LogOptForm;
    TMesOptsForm *MesOptsForm;
    TPackOptForm *PackOptForm;
    TAddMaiForm *AddMaiForm;
    TScriptOptForm *ScriptOptForm;
    TDmnForm *DmnForm;
    TScrForm *ScrForm;
};

#endif 
