#include "ind.h"

#ifdef __BORLANDC__
#pragma pack 1
#endif
//----------------------------------------------------------------------------

TIndicator::TIndicator( const TRect& bounds, int aMaxLen ):
    TInputLine(bounds,aMaxLen)
{
if (state&sfCursorVis) state-=sfCursorVis;
if (options&ofSelectable) options-=ofSelectable;
if (options&ofFirstClick) options-=ofFirstClick;
}
//----------------------------------------------------------------------------

TPalette& TIndicator::getPalette() const
{
static TPalette palette( cpIndicator, sizeof( cpIndicator )-1 );
return palette;
}
void  TIndicator::handleEvent( TEvent& event )
{
TView::handleEvent(event);
}

//----------------------------------------------------------------------------
