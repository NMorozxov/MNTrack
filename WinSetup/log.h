//---------------------------------------------------------------------------
#ifndef logH
#define logH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TLogOptBox : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TButton *Button1;
	TCheckBox *CheckBox10;
        TButton *Button2;
private:	// User declarations
public:		// User declarations
        __fastcall TLogOptBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TLogOptBox *LogOptBox;
//---------------------------------------------------------------------------
#endif
