#include "stringop.h"
int substr(char st[],char *s,unsigned int index,char sp)
/*
 st - string
 s - substring
*/
{
static unsigned int i;
if (!st[0]) {*s=0;return index;}
if (index>(strlen(st)-1)) {*s=0;return index;}
while (st[index]==sp) index++;
for(i=index;i<strlen(st);i++)
 if (st[i]==sp) break; else s[i-index]=st[i];
s[i-index]=0;
while(i<strlen(st) && st[i]==sp) i++;
return i;
}