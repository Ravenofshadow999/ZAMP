__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp ../opis_dzialan/opis_dzialan.cmd

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall
FILE=klient
OBJ=obj
SRC=src
APP=./klient
COMPFLAGS= -iquote inc -W -Wall -std=c++17 -pedantic 
LINKFLAGS= -W -Wall 
LIBS=-ldl -lpthread -lxerces-c
LINKERFLAGS=-L/opt/lib -lxerces-c -lpthread -ldl
COMPILERFLAGS=-I/opt/include


interp: obj/main.o obj/LibInterface.o obj/xmlinterp.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/xmlinterp.o ${LINKERFLAGS} ${LINKERFLAGS}

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/Set4LibInterfaces.hh inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp ${COMPILERFLAGS}

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp
	
obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh 
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp ${COMPILERFLAGS}

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
