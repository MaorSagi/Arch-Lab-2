# All Targets
all: run


run: main.o toy_printf.o 
	gcc -g -Wall -o run main.o toy_printf.o 

toy_printf.o: toy_printf.c toy_stdio.h
	gcc -g -Wall -c -o toy_printf.o toy_printf.c 
 
main[1].o: main[1].c toy_stdio.h
	gcc -g -Wall -c -o main.o main.c


.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o run
