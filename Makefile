PREFIX = /usr/local
CC = cc
CFILES = $(wildcard src/*.c)
EXECUTABLE = smoothbrain
CFLAGS = -O2

.PHONY: build install clean run debug

build:
	$(CC) $(CFILES) -o $(EXECUTABLE) $(CFLAGS)

install: ./$(EXECUTABLE)
	cp ./$(EXECUTABLE) $(PREFIX)/bin/

uninstall: $(PREFIX)/bin/$(EXECUTABLE)
	rm $(PREFIX)/bin/$(EXECUTABLE)

clean:
	rm ./$(EXECUTABLE) 2> /dev/null || true
	rm ./$(EXECUTABLE)_debug 2> /dev/null || true
	rm ./vgcore* 2> /dev/null || true

run: build
	./$(EXECUTABLE)

debug: clean
	$(CC) -DDEBUG -g  $(CFILES) -o $(EXECUTABLE)_debug $(CFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)_debug
	./$(EXECUTABLE)_debug

