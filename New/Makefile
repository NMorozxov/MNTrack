CC		= icl
CFLAGS		= /D__WIN32__ /O3 /G6 /QaxiM /GF
#CFLAGS		= /D__WIN32__ /O2 /G6 /GF
INCLUDE_VC	= /I"C:\Program Files\Microsoft Visual Studio .NET 2003\vc7\include" /I"C:\Program Files\Microsoft Visual Studio .NET 2003\vc7\PlatformSDK\include"
INCLUDE		= /I. /Id:\Nicol\MNLib $(INCLUDE_VC)
LIBS            = d:\nicol\mnlib\mnlib32.lib
CFLAGS_ALL	= $(CFLAGS) $(INCLUDE)

MNTRACK_OBJS	= addr.obj bink.obj jam.obj log.obj cfg.obj mntrq.obj pkt.obj version.obj msg.obj upkt.obj mntrack.obj trackmod.obj
MNTRACK_SRCS	= addr.c bink.c jam.c log.c cfg.c mntrq.c pkt.c version.c msg.c upkt.c mntrack.c trackmod.c
NODEADD_OBJS	= version.obj nodeadd.obj trackmod.obj
NODEADD_SRCS	= version.c nodeadd.c trackmod.c
MNTRNC_OBJS	= version.obj mntrnc.obj mntrq.obj trackmod.obj
MNTRNC_SRCS	= version.c mntrnc.c mntrq.c trackmod.c

.c.obj:
	$(CC) /c $(CFLAGS_ALL) $< 

mntrack: $(MNTRACK_OBJS)
	$(CC) /Femntrackn.exe $(MNTRACK_OBJS) mntrackn.res $(LIBS)

nodeadd: $(NODEADD_OBJS)
	$(CC) /Fenodeaddn.exe $(NODEADD_OBJS) $(LIBS)

mntrnc: $(MNTRNC_OBJS)
	$(CC) /Femntrncn.exe $(MNTRNC_OBJS) $(LIBS)

all: mntrack nodeadd mntrnc

clean:
	rm -f core *.obj mntrack.exe nodeadd.exe mntrnc.exe
	rm -f mntrack.ndx mntrack.cfg mntrack.msk mntrack.dmn mntrack.aka

distclean: clean
	rm -f Makefile *~ unix_version.h
	rm -rf .pcomp

# DO NOT DELETE THIS LINE -- make depend depends on it.
