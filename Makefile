LDFLAGS=-Wall -Werror

main : main.o interface.o
	gcc -o main main.o interface.o ${LDFLAGS}
	rm -f *.o *~
main.o : main.c main.h interface.h
	gcc -c main.c
interface.o : interface.c main.h interface.h
	gcc -c interface.c