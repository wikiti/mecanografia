CC=g++
CFLAGS=-Iinclude

meca: src/main.cpp
	$(CC) $(CFLAGS) -o bin/meca.exe src/main.cpp