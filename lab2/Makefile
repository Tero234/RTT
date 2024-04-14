all: process thread

process: process.o
	gcc -I../utils/logger/lib -std=c99 -w -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

thread: thread.o
	gcc -I../utils/logger/lib -std=c99 -w -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

process.o: process.c
	gcc -c -I../utils/logger/lib -std=c99 -w -o $@ $^

thread.o: thread.c
	gcc -c -I../utils/logger/lib -std=c99 -w -o $@ $^

clean:
	rm -f *.o *.txt process thread
