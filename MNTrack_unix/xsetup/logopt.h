#ifndef _MN_LOG_OPT_H
#define _MN_LOG_OPT_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <mntcfg.h>
#include <stdio.h>

class TLogOptForm : public QWidget
{
    Q_OBJECT
public:
    TLogOptForm( QWidget *parent=0, const char *name=0, WFlags f=WType_Modal);
    QLineEdit *Edit1;
    QCheckBox *Box1,*Box2,*Box3,*Box4,*Box5,*Box6,*Box7,*Box8,*Box9,*Box10;
public slots:
    void OkPressed();
private:
    QPushButton *okButton,*CancelButton;
    QLabel *Label1;
};


#endif
