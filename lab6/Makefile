all: lab6

lab6: lab6.o
	gcc -I../utils/logger/lib -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

lab6.o: lab6.c
	gcc -c -I../utils/logger/lib -o $@ $^

clean:
	rm -f *.o *.txt lab6
