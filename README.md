# Math442-HW1
First homework for Math 442 at Reed College: "Galaxy Explorers."

We are given python code for a function that initializes random arrays of a given
size (`x`, `y`, `z` for position and `vx`, `vy`, and `vz` for velocity) and
repeats a function (`update_coords`) for a given number of iterations that adds
each velocity vector to the corresponding position vector (e.g. update
`x[i] = x[i] + vx[i]` on each iteration.)

In this assignment, we

- Benchmark the supplied python code
- Write a C implementation of the function
- Write an Assembly implementation of the `update_coords` function
- Benchmark the C and Assembly versions and compare to the python version

## Results

### Question 1. Python benchmarks

The test is run using the python script `python_code/find-times.py`. 
It creates a csv file with the data.
We then use R and ggplot2 to create plots to show the data.

Here we plot the benchmark observations, with a LOESS fitted curve showing the
general trend along with the standard error of the fitted curve.


![First python benchmark](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/data_analysis/original_python_benchmark.jpeg)

Our first attempt at benchmarking the python script showed an immediate problem:
instead of getting slower with larger input size, the function got faster. In this
plot we display the order of execution of the tests with the variable `i`:
darker points were run earlier and lighter points were run later. There doesn't
seem to be an extremely clear trend as far as which ran faster.

However, there is a lot more variance in the tests with small data size. In fact,
the plot shows two different trends: about half of the tests show a slowly
increasing runtime, but are all generally lower, while the other half of the
data shows an exponentially decreasing runtime curve with larger datasets
performing much faster. It's clear there that there is some choice the processor
is making inconsistently about how to run the program that has a huge effect
on performance. It will be interesting to see whether this effect persists in
the C and assembly implementations.

### Question 2: C-float benchmarks

The shell script `testc.sh` is designed to run the C function in a loop testing
various numbers of iterations and input sizes. You can save a CSV file of the
results by entering `./testc.sh > c_test_data.csv` into the shell.

![Comparison of C optimizations](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/c_code/c_optimizations.png)

Here we can see that optimization level of the compiler doesn't have a significant
effect on performance of the program. Here we see greater variance in run time
with greater input size.

### Question 3: C-double benchmarks
We benchmarked the c-double program using the same techniques as used in the c-float benchmarks

![Comparison of types in C](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/c_code/c_type.png)

We see that in our test there wasn't a significant difference in speed between using float or double in our program.

### The C Test

The shell script `testc.sh` is designed to run the C function in a loop testing
various numbers of iterations and input sizes. You can save a CSV file of the
results by entering

```{sh}
./testc.sh > c_test_data.csv
```

### Question 4: C-assembly Test
We then tried using inline assembly to see how that affected performance. 
To do this, we implemented a `combine_array` function in assembly, which takes as input two float arrays and performs the the `+=` operation.
We then replaced `update_coordinates` with three calls to `combine_array`, one call for each coordinate. 

We benchmarked the c-assembly program using the same benchmarking techniques as described above.

TODO add timings

### Question Memory Profiling
To profile the memory we used the massif tool inside of valgrind.
The tool is used with the following commands:
```
valgrind --tool=massif  --massif-out-file=massif_out ./a.out 1048576 500 0;
ms_print massif_out > massif_print
```

Running the profiler on the c code using floats produces the following:

![c-float graph](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_c_float.png)

above is c-float graph

![c-double chart](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_c_double.png)

above is c-double graph

![c-c-asm chart](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_asm.png)

above is c-inline assembly with floats graph

These graphs were generated by running 500 iterations with 2 to the 20 objects. 


The x-axis has units Gi which is number of instructions times 1,000 (because its giga).
Gi is considered a unit of time in measuring memory usage. 
The y-axis is MB, megabytes, and is a measure of the amount of memory on the heap.

Observations: 

1. We notice that the graphs for c-float and asm are similar, but that the x-axis is longer for asm. 
It is expected that the total amont of memory used by the two programs is the same, since our assembly optimizations were only for speeding up the `+=` operation, not reducing memory. However it is surprising that the x-axis is longer for asm. THis suggests that the asm code requires more instructions. Perhaps the compiler does some optimization, maybe vectorizes, to reduce the number of instructions.

1. The graph of the program run using doubles uses twice as much memory as the two programs that use floats. This is expected since a double is twice the amount of memory as a float. Also note that the x-axis of the double graph is as long as the double graph. This indicates that the double program and the float program use the same number of instructions. This is consistent with our hypothesis in point 1, where we hypothesize that the float program requires less instructions due to some compiler optimizations, maybe vectorizing or some similar trick with 32/64 bit numbers. Since a float is 32 bits, and we are running this on a 64 bit machine, this is possible if the numbers are encoded with floats, but it is not possible if the numbers are encoded using doubles. 

- Sources for memory profiling:
    - http://valgrind.org/docs/manual/ms-manual.html
    - https://sites.google.com/a/case.edu/hpc-upgraded-cluster/home/important-notes-for-new-users/valgrind-utility
    - https://developer.gnome.org/optimization-guide/stable/massif.html.en

