SUBDIRS := lib src

BIN = ./build/svs
CFG = ./svs.conf

all: 
	(cd lib && $(MAKE))
	(cd src && $(MAKE))

install:
	(cp -pf $(BIN) /usr/bin)
	(if [ ! -e /etc/svs.conf ]; then  cp -pf $(CFG) /etc ;fi )

uninstall:
	(rm -f /usr/bin/svs)
	(mv -f /etc/svs.conf /etc/svs.conf.save)


clean:
	(cd lib && $(MAKE) clean)
	(cd src && $(MAKE) clean)
	(rm -rf build)
