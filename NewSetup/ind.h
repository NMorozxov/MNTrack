#ifndef _NICOL_TV_IND_H
#define _NICOL_TV_IND_H

#define Uses_TInputLine

#include <tv.h>

#define cpIndicator "\x06\x06\x06\x06"

class TIndicator : public TInputLine
{
public:
    TIndicator( const TRect& bounds, int aMaxLen );
    virtual TPalette& getPalette() const;
    void handleEvent(TEvent& event);
};

#endif
