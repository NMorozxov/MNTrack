//---------------------------------------------------------------------------
#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TImage *Image1;
        TButton *Button1;
private:	// User declarations
public:		// User declarations
        __fastcall TAboutBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAboutBox *AboutBox;
//---------------------------------------------------------------------------
#endif
