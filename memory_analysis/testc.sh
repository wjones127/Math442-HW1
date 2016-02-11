#!/bin/bash

objs=1048576
valgrind --tool=massif --massif-out-file=massif_out ./a.out $objs 500 0;
ms_print massif_out > massif_print

## Loop over repetitions
#for i in  {1..5}
#do
#    # Loop over size
#    for (( k = 2048; k <= 131072; k *= 2))
#    do
#
#    done
#done
