#ifndef _MN_XSETUP_QT_DMN
#define _MN_XSETUP_QT_DMN

#include <qwidget.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <mntcfg.h>
#include <stdio.h>

class TDmnForm : public QWidget
{
    Q_OBJECT

public:
    TDmnForm( QWidget* parent = 0, const char* name = 0, WFlags f=WType_Modal );
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
    QLabel* textLabel10;
    QLineEdit* lineEdit12;
    QLabel* textLabel11;
    QLineEdit* lineEdit13;
    QCheckBox* checkBox1;
    QCheckBox* checkBox2;
    QLineEdit* lineEdit14;
    QLabel* textLabel12;
    QLineEdit* lineEdit15;
    QLabel* textLabel13;
    QPushButton* pushButtonNext;
    QPushButton* pushButtonFirst;
    QPushButton* pushButtonLast;
    QPushButton* pushButtonPrev;
    QPushButton* pushButtonDel;
    QPushButton* pushButtonIns;
    QPushButton* okButton;
};

#endif // TDmnForm_H
