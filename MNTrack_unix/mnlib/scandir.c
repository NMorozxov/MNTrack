#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef HAVE_SCANDIR

#include "scandir.h"

int scandir (__const char *__dir,
	     struct dirent ***__namelist,
             int select,
             int cmp)
{
  DIR *dp = opendir (__dir);
  struct dirent **v = NULL;
  size_t vsize = 0, i;
  struct dirent *d;
  struct dirent **new;  

  if (dp == NULL)
    return -1;

  i = 0;
  
  while ((d = readdir (dp)) != NULL) {
	    if (vsize == 0)
	      vsize = 10;
	    else
	      vsize *= 2;
	    new = (struct dirent **) realloc (v, vsize * sizeof (*v));
	    v = new;
	v[i] = (struct dirent *) malloc (d->d_reclen);
	memcpy (v[i++], d, d->d_reclen);
      }
closedir (dp);
*__namelist=v;
return i;
}

#endif /* HAVE_SCANDIR */