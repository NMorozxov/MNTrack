#include "nodeadd.h"
#include "version.h"
int main(int argc,char *argv[])
{
Adr4D adr;
FILE *f;
int i;
#ifdef __WIN32__
int oldmode;
#endif

printf("MNTrack %s Node Add Tool (C) 1996-98 Nicol Morozov 2:5020/991\n",version);
#ifdef __WIN32__
oldmode=SetErrorMode(SEM_FAILCRITICALERRORS);
__try { f=fopen("mntrack.ndx","ab+"); }
__finally { SetLastError(0); SetErrorMode(oldmode);}
#else
f=fopen("mntrack.ndx","ab+");
#endif
if (f==NULL) {
printf("Can't open mntrack.ndx\n");
exit(1);
}
if (argc>1) for (i=1;i<argc;i++) {
txt2adr(argv[i],&adr);
fwrite(&adr,1,sizeof(Adr4D),f);
printf("Adding %d:%d/%d\n",adr.zone,adr.net,adr.node);
} else {
printf("Usage: NODEADD <address> [<address> ...]\n");
}
fclose(f);
return 0;
}
