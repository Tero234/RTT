all: lib/liblogger.so

lib/liblogger.so: src/logger.c
	mkdir -p $(@D)
	gcc -fPIC -std=c99 -w -shared $< -o $@

clean:
	rm -rf lib/