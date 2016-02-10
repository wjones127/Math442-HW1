#!/bin/bash
echo "size, iter, time, chksum"

# Loop over repetitions
for i in  {1..5}
do
    # Loop over size
    for (( k = 2048; k <= 131072; k *= 2))
    do
        ./doubletest $k 5000
    done
done
