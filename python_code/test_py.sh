#!/bin/bash
echo "size, iter, time, chksum"

# Loop over repetitions
for i in  {1..12}
do
    # Loop over size
    for (( k = 256; k <= 2**24; k *= 2))
    do
        ./update_locations.py $k 60
    done
done
