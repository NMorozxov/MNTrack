#ifndef _MNTRACK_TV_SETUP_SCR_H
#define _MNTRACK_TV_SETUP_SCR_H

#define Uses_TInputLine
#define Uses_TDialog
#define Uses_TKeys
#define Uses_TSItem
#define Uses_TEvent
#define Uses_TLabel
#define Uses_TButton

#include <cport.h>
#include <trackmod.h>
#include <tv.h>
#include "ind.h"
#include "cfg.h"
#include "set_evt.h"
#include "set_hlp.h"

class TScriptDialog : public TDialog
{
public:
      TScriptDialog(const TRect& bounds, const char *aTitle);
 void handleEvent(TEvent& event);
private:
 TView *ILScan;
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
