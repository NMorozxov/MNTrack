#ifndef _MNTRACK_TV_SETUP_DMN_H
#define _MNTRACK_TV_SETUP_DMN_H

#define Uses_TInputLine
#define Uses_TDialog
#define Uses_TEvent
#define Uses_TButton
#define Uses_TLabel
#define Uses_TKeys
#define Uses_TCheckBoxes
#define Uses_TSItem

#include <cport.h>
#include <trackmod.h>
#include <tv.h>
#include "ind.h"
#include "cfg.h"
#include "set_evt.h"
#include "set_hlp.h"

class TDMNDialog : public TDialog
{
public:
      TDMNDialog(const TRect& bounds, const char *aTitle);
 void handleEvent(TEvent& event);
private:
      TView *ILName,*ILout,*ILMZ,*ILZones;
      TCheckBoxes *CDef,*CHMZ;
      TIndicator *Ind;
 void SetDiaData(void);
 void GetDiaData(void);
 void Ins(void);
 void Del(void);
 void Home(void);
 void Left(void);
 void Right(void);
 void End(void);
};

#endif
