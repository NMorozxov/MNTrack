//---------------------------------------------------------------------------
#ifndef genoptH
#define genoptH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TGenOptBox : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
        TEdit *Edit3;
        TLabel *Label3;
        TButton *Button1;
        TButton *ButtonCancel;
private:	// User declarations
public:		// User declarations
        __fastcall TGenOptBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TGenOptBox *GenOptBox;
//---------------------------------------------------------------------------
#endif
