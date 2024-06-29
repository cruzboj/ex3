FLAGS=-Wall -Werror
EXEC = prog
OBJS = pr2hrm.h pr2ex3.h
CC = gcc

run: prog
	./prog

$(EXEC): my_prog.o main.o
	$(CC) *.o -o $(EXEC) -L. -lprog2 -o $@

main.o: main.c $(OBJS)
	$(CC) -c main.c

my_prog.o: my_prog.c $(OBJS) linked_list.h
	$(CC) -c my_prog.c

clean:
	rm -f *.o $(EXEC)