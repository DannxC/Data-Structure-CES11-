all: program

run: program
	@./program

program: main.o deque.o
	@gcc -std=c99 $^ -o $@

%.o: %.c
	@gcc -c -std=c99 $< -o $@
