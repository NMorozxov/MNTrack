#ifndef _MN_GENOPTS_H
#define _MN_GENOPTS_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <mntcfg.h>
#include <stdio.h>

class TGenOptsForm : public QWidget
{
    Q_OBJECT
public:
    TGenOptsForm( QWidget *parent=0, const char *name=0, WFlags f=WType_Modal);
    QLineEdit *Edit1,*Edit3;
public slots:
    void OkPressed();
private:
    QPushButton *okButton,*CancelButton;
    QLabel *Label1,*Label3;
};


#endif
