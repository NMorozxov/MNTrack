#ifndef MNTRACK_SETUP_H
#define MNTRACK_SETUP_H
/* Turbo Vision Stuff */
#define Uses_TApplication
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TPalette
#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TDeskTop
#define Uses_TStaticText
#define Uses_TRadioButtons
#define Uses_TEvent
#define Uses_fpstream
#define Uses_MsgBox
#define Uses_TView
#define Uses_TKeys
#define Uses_TDialog
#define Uses_TButton
#define Uses_TInputLine
#define Uses_TLabel
#define Uses_TCheckBoxes
#define Uses_TSItem

#include <cport.h>
#include <trackmod.h>
#include "set_evt.h"
#include "set_hlp.h"
#include "cfg.h"
#include "ind.h"
#include "dmn.h"
#include "scr.h"
#include "aka.h"
#ifndef NO_TV_STREAMS
#include <help.h>
#endif

class TSetupApp : public TApplication
{
public:
    TSetupApp();
    static TStatusLine *initStatusLine(TRect r);
    static TMenuBar *initMenuBar(TRect r);
    void handleEvent(TEvent& event);
    void getEvent(TEvent& event);
    virtual void outOfMemory();
#if !defined(NO_TV_STREAMS) && !defined(UNIX)
    virtual TPalette& getPalette() const;
#endif
private:
#ifndef NO_TV_STREAMS
    void Help(char *HelpFileName,ushort HelpCtx,TEvent& event);
#endif
    //General
    static void GenOptProc(void);
    static void AddMaiProc(void);
    static void PFNProc(void);
    static void LogOptProc(void);
    static void MesOptProc(void);
    //Scripts
    static void ScrOptProc(void);
    static void ScrProc(void);
    //Packing
    static void PacOptProc(void);
    static void DMNProc(void);
    //Help
    static void AboutProc(void);
};

#endif
