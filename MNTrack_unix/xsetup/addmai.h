#ifndef _MN_ADD_MAI_H
#define _MN_ADD_MAI_H

#include <qwidget.h>
#include <qvariant.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <mntcfg.h>
#include <stdio.h>

class TAddMaiForm : public QWidget
{
    Q_OBJECT
public:
    TAddMaiForm( QWidget *parent=0, const char *name=0, WFlags f=WType_Modal);
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
    QLabel* textLabel3;
    QLineEdit* lineEdit2;
    QLabel* textLabel2;
    QGroupBox* groupBox1;
    QLineEdit* lineEdit3;
    QLineEdit* lineEdit4;
    QLineEdit* lineEdit5;
    QLabel* textLabel7;
    QLabel* textLabel4;
    QLabel* textLabel5;
    QLabel* textLabel6;
    QPushButton* pushButtonFirst;
    QPushButton* pushButtonLast;
    QPushButton* pushButtonNext;
    QPushButton* pushButtonPrev;
    QPushButton* pushButtonIns;
    QPushButton* pushButtonDel;
    QPushButton *okButton;
};

#endif
