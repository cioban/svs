
all:
	(mkdir -p obj && cd confuse-2.6 && ./configure --enable-shared=no --enable-static=yes --prefix=$(PWD)/obj && $(MAKE) && $(MAKE) install || exit 1)
	

clean:
	(rm -rf obj && cd confuse-2.6 && $(MAKE) distclean)

