
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
	valgrind --tool=massif ./a.out 100 100 1

valg2:
	valgrind --tool=massif --depth=5  --alloc-fn=g_malloc --alloc-fn=g_realloc --alloc-fn=g_try_malloc \
	         --alloc-fn=g_malloc0 --alloc-fn=g_mem_chunk_alloc ./a.out 100 100 1
