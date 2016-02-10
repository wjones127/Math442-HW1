
#CC = clang
CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -Werror -std=gnu11 
# use gnu11 because c11 doesn't have asm

default:
	$(CC) $(CFLAGS) update_locations.c 

run:
	./a.out
dbg:
	gdb --args ./a.out 
