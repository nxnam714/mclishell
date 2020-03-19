all : Atmain
Atmain: Atmain.o AtOsal.o
	gcc -o Atmain Atmain.o AtOsal.o
Atmain.o: Atmain.c AtOsal.h
	gcc -o Atmain.o -c Atmain.c
AtOsal.o: AtOsal.c AtOsal.h
	gcc -o AtOsal.o -c AtOsal.c
clean:
	rm Atmain
	rm *.o
