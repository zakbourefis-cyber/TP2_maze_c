CFLAGS = -Wall -Wextra -std=c99

all: maze

maze: maze.o main.o stack.o coord.o print_maze.o
	gcc $(CFLAGS) -o $@ $^

print_maze.o: print_maze.c maze.h coord.h print_maze.h
	gcc $(CFLAGS) -c $<

maze.o: maze.c maze.h coord.h
	gcc $(CFLAGS) -c $<

main.o: main.c maze.h stack.h coord.h
	gcc $(CFLAGS) -c $<

stack.o: stack.c stack.h coord.h
	gcc $(CFLAGS) -c $<

coord.o: coord.c coord.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o maze

