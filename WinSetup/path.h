//---------------------------------------------------------------------------
#ifndef pathH
#define pathH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TPathBox : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label3;
        TButton *ButtonOk;
        TButton *Button1;
private:	// User declarations
public:		// User declarations
        __fastcall TPathBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPathBox *PathBox;
//---------------------------------------------------------------------------
#endif
