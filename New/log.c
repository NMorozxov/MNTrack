#include "log.h"
extern ConfigType config;
extern char FileName[255];
extern BOOL_1 F_Quiet;
extern BOOL_1 F_CR;
char MesPrev[255]="",MesPost[255]="";
/* Writes Message to Log file */
void write_log(char type,char *message)
{
FILE *logfile;
static char buf[255];
static char moth[4];
struct tm *tmm;
time_t timer;
switch (type) {
case '!':if (!(config.loglevel&1)) return;
         else break;
case '^':if (!(config.loglevel&2)) return;
         else break;
case '-':if (!(config.loglevel&4)) return;
         else break;
case '#':if (!(config.loglevel&8)) return;
         else break;
case '+':if (!(config.loglevel&16)) return;
         else break;
case '&':if (!(config.loglevel&32)) return;
         else break;
case '%':if (!(config.loglevel&64)) return;
         else break;
case '~':if (!(config.loglevel&128)) return;
         else break;
case '@':if (!(config.loglevel&256)) return;
         else break;
default: if (!(config.loglevel&512)) return;
         else break;
}
logfile=fopen(config.logfile,"a+");
if (logfile==NULL) {
if (F_CR) {printf("\n");F_CR=FALSE;}
printf("Fatal : Can't Open/Create Log File %s\n",config.logfile);
exit_mntrack(7);
}
timer=time(NULL);
tmm=localtime(&timer);
GetMonth(tmm->tm_mon+1,moth);
fwrite(buf,1,sprintf(buf,"%c %2.2d %s %2.2d:%2.2d:%2.2d MNTR %s %s%s%s\n",type,tmm->tm_mday,moth,tmm->tm_hour,tmm->tm_min,tmm->tm_sec,FileName,MesPrev,message,MesPost),logfile);
fclose(logfile);
if (!F_Quiet) {
if (F_CR) {printf("\n");F_CR=FALSE;}
switch(type){
case '!':printf("Error");break;
case '^':printf("Warning");break;
case '-':printf("User");break;
case '#':printf("Netmail");break;
case '+':printf("BSO");break;
case '&':printf("Semaphore");break;
case '%':printf("File");break;
case '~':printf("Debug");break;
case '@':printf("External");break;
default: printf("Unknown");
}
printf(" : %s%s%s\n",MesPrev,message,MesPost);
}
*MesPrev=0;
*MesPost=0;
return;
}
