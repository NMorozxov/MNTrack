#ifndef _MN_MesOpts_H
#define _MN_MesOpts_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <mntcfg.h>
#include <stdio.h>

class TMesOptsForm : public QWidget
{
    Q_OBJECT
public:
    TMesOptsForm( QWidget *parent=0, const char *name=0, WFlags f=WType_Modal);
    QLineEdit *Edit1;
    QCheckBox *Box1;
public slots:
    void OkPressed();
private:
    QPushButton *okButton,*CancelButton;
    QLabel *Label3;
};


#endif
