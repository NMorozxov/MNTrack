#ifndef MNTRACK_SETUP_QT_CFG
#define MNTRACK_SETUP_QT_CFG

#define far

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qmessagebox.h>

#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_ALLOC_H
#include <alloc.h>
#endif

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#include <mntcfg.h>
#include <trackmod.h>
void LoadConfig(void);
void SaveConfig(void);
#endif
