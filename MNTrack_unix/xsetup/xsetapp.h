#ifndef _MN_XSETUP_APP_H
#define _MN_XSETUP_APP_H

#include <stdio.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include "cfg.h"

class XSetupApp : public QApplication
{
    Q_OBJECT
public:
    XSetupApp( int &argc, char **argv);

public slots:
    void quit();

private:
};

#endif 
