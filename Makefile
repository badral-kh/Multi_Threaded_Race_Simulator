OPT = -Wall
LIBS = -lpthread -lncurses
OBJ = main.o init.o graphics.o race.o entity.o clean.o print.o

a4:	$(OBJ)
	gcc $(OPT) -o a4 $(OBJ) $(LIBS)

main.o:	main.c defs.h
	gcc -c main.c

init.o:	init.c defs.h
	gcc -c init.c

clean.o:	clean.c defs.h
	gcc -c clean.c

graphics.o:	graphics.c defs.h
	gcc -c graphics.c

entity.o:	entity.c defs.h
	gcc -c entity.c

race.o:	race.c defs.h
	gcc -c race.c

print.o:	print.c defs.h
	gcc -c print.c

valgrind:	a4
	valgrind --leak-check=yes ./a4
clean:
	rm -f a4
