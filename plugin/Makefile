

__start__: obj __lines_for_space__ ../libs/Interp4Move.so ../libs/Interp4Rotate.so ../libs/Interp4Pause.so ../libs/Interp4Set.so 
	@echo "  Tworzenie wtyczek zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -Iinc -I../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo
	
	
################ MOVE ###############
../libs/Interp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/Interp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo


obj/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp

################ ROTATE ################
../libs/Interp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/Interp4Rotate.so obj/Interp4Rotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo


obj/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp

################ PAUSE ################
../libs/Interp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/Interp4Pause.so obj/Interp4Pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo


obj/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp

################ SET ################
../libs/Interp4Set.so: obj/Interp4Set.o
	g++ ${LDFLAGS} -o ../libs/Interp4Set.so obj/Interp4Set.o
	@echo
	@echo "  Wtyczka dla polecenia 'Set' zostala utworzona."
	@echo


obj/Interp4Set.o: src/Interp4Set.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Set.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Set.o src/Interp4Set.cpp

clean:
	rm -f obj/*
	rm -f ../libs/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
