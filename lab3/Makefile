all: client server

client: client.o
	gcc -I../utils/logger/lib -std=c99 -w -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

server: server.o
	gcc -I../utils/logger/lib -std=c99 -w -o $@ $^ -L../utils/logger/lib -llogger -Wl,-rpath,../utils/logger/lib

client.o: client.c
	gcc -c -I../utils/logger/lib -std=c99 -w -o $@ $^

server.o: server.c
	gcc -c -I../utils/logger/lib -std=c99 -w -o $@ $^

clean:
	rm -f *.o *.txt client server
