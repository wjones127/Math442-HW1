#!/bin/bash
echo "size, iter, time, chksum"

# Loop over repetitions
for i in  {1..12}
do
    # Loop over size
    for (( k = 256; k <= 2**24; k *= 2))
    do
        ./3 $k 60 1
    done
done
