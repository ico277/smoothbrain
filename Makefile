PREFIX = /usr/local
CC = cc
CFILES = $(wildcard src/*.c)
EXECUTABLE = smoothbrain
CFLAGS = -O2

.PHONY: build install clean run debug

build:
	$(CC) $(CFILES) -o $(EXECUTABLE).out $(CFLAGS)

install: ./$(EXECUTABLE).out
	cp ./$(EXECUTABLE).out $(PREFIX)/bin/$(EXECUTABLE)

uninstall: $(PREFIX)/bin/$(EXECUTABLE)
	rm $(PREFIX)/bin/$(EXECUTABLE)

clean:
	rm ./$(EXECUTABLE).out 2> /dev/null || true
	rm ./$(EXECUTABLE)_debug.out 2> /dev/null || true
	rm ./vgcore* 2> /dev/null || true

run: build
	./$(EXECUTABLE).out

debug: clean
	$(CC) -DDEBUG -g  $(CFILES) -o $(EXECUTABLE)_debug.out $(CFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)_debug.out
	./$(EXECUTABLE)_debug.out

