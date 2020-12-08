__start__: obj xmlinterp4config
	./xmlinterp4config

obj:
	mkdir obj

CPPFLAGS=-Wall -g -pedantic -Iinc
LDFLAGS=-Wall

xmlinterp4config: obj/xmlinterp.o obj/main.o
	g++ ${LDFLAGS} -o xmlinterp4config  obj/xmlinterp.o\
                                     obj/main.o -L/opt/lib -lxerces-c

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp -I/opt/include

obj/main.o: src/main.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp -I/opt/include -L/opt/lib -lxerces-c

clean:
	rm -fr obj xmlinterp4config core

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
