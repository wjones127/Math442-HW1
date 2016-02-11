
CFLAGS = -Wall -Wextra -pedantic -Werror -std=gnu11

default:
	gcc $(CFLAGS) update_locations.c 

run:
	./a.out 100 100 0
run_asm:
	./a.out 100 100  1
gdb:
	gdb --args ./a.out 100 100 1

valg:
	valgrind ./a.out 100 100 1
