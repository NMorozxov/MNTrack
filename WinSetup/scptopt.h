//---------------------------------------------------------------------------
#ifndef scptoptH
#define scptoptH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSOBox : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *CheckBox1;
	TRadioGroup *RadioGroup1;
        TButton *ButtonOk;
        TButton *Button1;
private:	// User declarations
public:		// User declarations
	__fastcall TSOBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSOBox *SOBox;
//---------------------------------------------------------------------------
#endif
