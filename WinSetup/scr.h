//---------------------------------------------------------------------------
#ifndef scrH
#define scrH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "ToolEdit.hpp"
#include <vcl\Mask.hpp>
//---------------------------------------------------------------------------
class TScript : public TForm
{
__published:	// IDE-managed Components
	TFilenameEdit *FilenameEdit1;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TEdit *Edit1;
	TButton *Button7;
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
        void __fastcall FilenameEdit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void ScrSetData(void);
        void ScrGetData(void);
	__fastcall TScript(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TScript *Script;
//---------------------------------------------------------------------------
#endif
