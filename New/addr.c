#include "addr.h"
BOOL_1 CheckAddress(const Adr4D adr)
{
TNdx=FNdx;
while (TNdx!=NULL) {
if (TNdx->address.zone==adr.zone && TNdx->address.net==adr.net && TNdx->address.node==adr.node) return TRUE;
TNdx=TNdx->next;
}
return FALSE;
}