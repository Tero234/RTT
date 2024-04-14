all: lab5

lab5: lab5.o
	gcc -I../utils/logger/lib -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

lab5.o: lab5.c
	gcc -c -I../utils/logger/lib -o $@ $^

clean:
	rm -f *.o *.txt lab5
