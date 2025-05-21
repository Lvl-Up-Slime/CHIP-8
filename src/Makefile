CC = gcc
CFLAGS = 'pkg-config --cflags sdl2'
LDFLAGS = 'pkg-config --libs sdl2'

main: main.c
		$(CC) -o main main.o $(LDFLAGS)

main.o: main.c
    $(CC) $(CFLAGS) -c main.c

clean:
		rm -f main main.o


