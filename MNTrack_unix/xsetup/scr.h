#ifndef _MN_XSETUP_QT_SCR_H
#define _MN_XSETUP_QT_SCR_H

#include <qwidget.h>
#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <mntcfg.h>
#include <stdio.h>

class TScrForm : public QWidget
{
    Q_OBJECT

public:
    TScrForm( QWidget* parent = 0, const char* name = 0, WFlags f=WType_Modal );
    void GetFormData(void);
    void SetFormData(void);
public slots:
    void OkPressed();
    void InsPressed();
    void DelPressed();
    void NextPressed();
    void PrevPressed();
    void FirstPressed();
    void LastPressed();
    void EditChanged();
private:
    QLabel* textLabel8;
    QLabel* textLabel9;
    QPushButton* pushButtonIns;
    QPushButton* pushButtonDel;
    QPushButton* pushButtonFirst;
    QPushButton* pushButtonPrev;
    QPushButton* pushButtonNext;
    QPushButton* pushButtonLast;
    QPushButton* okButton;
    QLineEdit* lineEdit10;
};
#endif
