all : Atmain
Atmain: Atmain.o AtOsal.o AtCliAPI.o
	gcc -o Atmain Atmain.o AtOsal.o AtCliAPI.o
AtCliAPI: AtCliAPI.c AtCliAPI.h
	gcc -o AtCliAPI.o AtCliAPI.c
Atmain.o: Atmain.c AtOsal.h AtCliAPI.h
	gcc -o Atmain.o -c Atmain.c
AtOsal.o: AtOsal.c AtOsal.h
	gcc -o AtOsal.o -c AtOsal.c
clean:
	rm Atmain
	rm *.o
