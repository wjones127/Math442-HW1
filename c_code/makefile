
CFLAGS = -Wall -Wextra -pedantic -Werror

default:
	clang $(CFLAGS) update_locations.c 

run:
	./a.out 100 100
gdb:
	gdb --args ./a.out 100 100

valg:
	valgrind ./a.out 100 100
