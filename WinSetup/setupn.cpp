//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mainf.cpp", MainForm);
USEFORM("about.cpp", AboutBox);
USEFORM("genopt.cpp", GenOptBox);
USEFORM("addr.cpp", AddrBox);
USEFORM("path.cpp", PathBox);
USEFORM("log.cpp", LogOptBox);
USEFORM("mes.cpp", MesBox);
USEFORM("scptopt.cpp", SOBox);
USEFORM("paopt.cpp", PABox);
USEFORM("scr.cpp", Script);
USEFORM("dmn.cpp", DMNForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TGenOptBox), &GenOptBox);
                 Application->CreateForm(__classid(TAddrBox), &AddrBox);
                 Application->CreateForm(__classid(TPathBox), &PathBox);
                 Application->CreateForm(__classid(TLogOptBox), &LogOptBox);
                 Application->CreateForm(__classid(TMesBox), &MesBox);
                 Application->CreateForm(__classid(TSOBox), &SOBox);
                 Application->CreateForm(__classid(TPABox), &PABox);
                 Application->CreateForm(__classid(TScript), &Script);
                 Application->CreateForm(__classid(TDMNForm), &DMNForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
