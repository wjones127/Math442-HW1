echo "size, iter, time, chksum"

# Loop over repetitions
for i in  {1..5}
do
    # Loop over iterations
    for (( j = 1000; j <= 5000; j += 1000))
    do
        # Loop over size
        for (( k = 100; k <= 1000; k += 100))
        do
            ./a.out $k $j
        done
    done
done
