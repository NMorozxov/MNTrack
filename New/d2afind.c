#include "d2afind.h"
int findfirst(const char *pathname,struct ffblk *ffblk, int attrib)
{
if (_dos_findfirst(pathname,attrib,ffblk)) return -1;
else return 0;
}
int findnext(struct ffblk *ffblk)
{
if (_dos_findnext(ffblk)) return -1;
else return 0;
}
