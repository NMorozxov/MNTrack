#ifndef _MNTRACK_TV_SETUP_AKA_H
#define _MNTRACK_TV_SETUP_AKA_H

#define Uses_TInputLine
#define Uses_TDialog
#define Uses_TEvent
#define Uses_TButton
#define Uses_TStaticText
#define Uses_TLabel
#define Uses_TKeys

#include <cport.h>
#include <trackmod.h>
#include <tv.h>
#include "ind.h"
#include "cfg.h"
#include "set_evt.h"
#include "set_hlp.h"

class TAKADialog : public TDialog
{
public:
    TAKADialog(const TRect& bounds, const char *aTitle);
    void handleEvent(TEvent& event);
private:
    TInputLine *ILNA,*ILA,*ILZ,*ILN;
    TIndicator *Ind;
    void SetDiaData(void);
    void GetDiaData(void);
    void Home(void);
    void Left(void);
    void Right(void);
    void End(void);
    void Ins(void);
    void Del(void);
};

#endif
