//---------------------------------------------------------------------------
#ifndef addrH
#define addrH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TAddrBox : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TLabel *Label1;
        TButton *ButtonOk;
    TGroupBox *GroupBox1;
    TEdit *Edit2;
    TStaticText *StaticText1;
    TStaticText *StaticText2;
    TStaticText *StaticText3;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
        TButton *ButtonIns;
        TButton *ButtonDel;
        TButton *ButtonFirst;
        TButton *ButtonPrev;
        TButton *ButtonNext;
        TButton *ButtonLast;
        void __fastcall ButtonOkClick(TObject *Sender);
	
	
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall ButtonInsClick(TObject *Sender);
    void __fastcall ButtonDelClick(TObject *Sender);
    void __fastcall ButtonFirstClick(TObject *Sender);
    void __fastcall ButtonPrevClick(TObject *Sender);
    void __fastcall ButtonNextClick(TObject *Sender);
    void __fastcall ButtonLastClick(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
    void AKASetData(void);
    void AKAGetData(void);
        __fastcall TAddrBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TAddrBox *AddrBox;
//---------------------------------------------------------------------------
#endif
