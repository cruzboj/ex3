EXEC = pr2hrm
OBJS = pr2hrm.o pr2hrm.o

run: prog
	./prog

prog: my_prog.o main.o
	gcc *.o -o prog

main.o: main.c pr2hrm.h pr2ex3.h
	gcc -c main.c

my_prog.o: my_prog.c pr2hrm.h pr2ex3.h linked_list.h libprog2.a
	gcc -c my_prog.c

clean:
	rm -f *.o prog