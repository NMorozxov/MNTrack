//---------------------------------------------------------------------------
#ifndef mesH
#define mesH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TMesBox : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *CheckBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
        TButton *Button2;
private:	// User declarations
public:		// User declarations
	__fastcall TMesBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMesBox *MesBox;
//---------------------------------------------------------------------------
#endif
