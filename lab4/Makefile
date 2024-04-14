all: lab4

lab4: lab4.o
	gcc -I../utils/logger/lib -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

lab4.o: lab4.c
	gcc -c -I../utils/logger/lib -o $@ $^

clean:
	rm -f *.o *.txt lab4

