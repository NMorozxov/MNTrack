DIRS	= mnlib src setup xsetup

all:
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done

clean:
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done

distclean: 
	for i in $(DIRS); do (cd $$i && $(MAKE) $@) || exit 1; done
	rm -f config.cache config.status config.h config.log config.h.in configure
