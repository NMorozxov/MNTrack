//---------------------------------------------------------------------------
#ifndef mainfH
#define mainfH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
        TMenuItem *General_mnu;
        TMenuItem *scripts_mnu;
        TMenuItem *pack_mnu;
        TMenuItem *packing_options_mnu;
        TMenuItem *dones_mnu;
        TMenuItem *help_mnu;
        TMenuItem *scopt_mnu;
        TMenuItem *scrp_mnu;
        TMenuItem *GeneralOptions1;
        TMenuItem *AddressMaintenance1;
        TMenuItem *PathAndFileNames1;
        TMenuItem *LogOptions1;
        TMenuItem *MessageOptions1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TMenuItem *About1;
        TMenuItem *Contents1;
        TMenuItem *Index1;
	TStatusBar *StatusBar1;
	TBevel *Bevel1;
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall GeneralOptions1Click(TObject *Sender);
        void __fastcall AddressMaintenance1Click(TObject *Sender);
        void __fastcall PathAndFileNames1Click(TObject *Sender);
        void __fastcall LogOptions1Click(TObject *Sender);
	void __fastcall MessageOptions1Click(TObject *Sender);
	void __fastcall scopt_mnuClick(TObject *Sender);
	void __fastcall packing_options_mnuClick(TObject *Sender);
	
	void __fastcall scrp_mnuClick(TObject *Sender);
	void __fastcall dones_mnuClick(TObject *Sender);
	void __fastcall Contents1Click(TObject *Sender);
	void __fastcall Index1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
