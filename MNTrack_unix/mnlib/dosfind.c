#include "dosfind.h"

/* Splits file name */
int  fnsplit(const char *__path, char *__drive, char *__dir, char *__name, char *__ext )
{
char *c,*c1;
strcpy(__dir,__path);

for(c=__dir,c1=NULL;*c!=0;c++) if (*c=='/') c1=c;
if (c1==NULL) { *__dir=0; strcpy(__name,__path);
} else { c1++; strcpy(__name,c1); *c1=0; }

for(c=__name,c1=NULL;*c!=0;c++) if (*c=='.') c1=c;
if (c1==NULL) *__ext=0;
else { strcpy(__ext,c1); *c1=0; }

*__drive=0;
return 0;
}

/* checkfile returns TRUE when filename is correct */
int checkfile(char *name, char *mask)
{
char *mask_regex,*c,*d;
int i;
#ifdef HAVE_REGCOMP
regex_t pred;
regmatch_t mat;
int error;
#endif
for(i=2,c=mask;*c!=0;c++,i++) if (*c=='*') i++;
mask_regex=(char *)calloc(1,i);
for(c=mask,d=mask_regex;*c!=0;c++,d++)
 {
 if (*c=='?') {*d='.';continue;}
 if (*c=='*') {*d='.';d++;}
 *d=*c;
 }
//printf("'%s'",mask_regex);
//if (*mask=='*') *mask='\\';
#ifdef HAVE_REGCOMP
regcomp(&pred,mask_regex,REG_ICASE | REG_EXTENDED);
error=regexec(&pred,name,1,&mat,0);
free(mask_regex);
if (error==REG_NOMATCH) return 0;
else return 1;
#else
re_comp(mask_regex);
free(mask_regex);
return re_exec(name);
#endif
}

int findfirst( const char *__path,struct ffblk *__ffblk,int __attrib)
{
static char drv1,dir1[255],name1[255],ext1[255];
fnsplit(__path,&drv1,dir1,name1,ext1);
strcat(name1,ext1); *ext1=0;
if (*dir1) dir1[strlen(dir1)-1]=0;
else strcpy(dir1,".");
if (!*dir1) strcpy(dir1,"/");
#ifdef HAVE_SCANDIR
__ffblk->ff_maxfile=scandir(dir1,&__ffblk->ff_namelist,0,alphasort);
#else
__ffblk->ff_maxfile=scandir(dir1,&__ffblk->ff_namelist,0,0);
#endif
if (__ffblk->ff_maxfile<0) return -1;
strcpy(__ffblk->ff_mask,name1);
__ffblk->ff_curfile=0;
while (__ffblk->ff_curfile<__ffblk->ff_maxfile) {
//printf("FindFirst : %s\n",__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name);
if (checkfile(__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name,__ffblk->ff_mask)) {
       strcpy(__ffblk->ff_name,__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name);
       __ffblk->ff_curfile++;
       return 0; 
       }
__ffblk->ff_curfile++;
}
return -1;
}

int findnext( struct ffblk *__ffblk )
{
while (__ffblk->ff_curfile<__ffblk->ff_maxfile) {
//printf("FindNext : %s\n",__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name);
if (checkfile(__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name,__ffblk->ff_mask)) {
       strcpy(__ffblk->ff_name,__ffblk->ff_namelist[__ffblk->ff_curfile]->d_name);
       __ffblk->ff_curfile++;
       return 0; 
       }
__ffblk->ff_curfile++;
}
return -1;
}
