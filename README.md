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

![Comparison of C optimizations](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/c_code/c_optimizations.png)

Here we can see that optimization level of the compiler doesn't have a significant
effect on performance of the program. Here we see greater variance in run time
with greater input size.

![Comparison of types in C](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/c_code/c_type.png)

We also see that in our test there wasn't a significant difference between using
float or double in our program, at least in terms of speed. 



## Running the Benchmarks

We used a variety of methods to do the benchmarks, mainly to try out different
tools. We created CSVs of data, with multiple observations for each combination
of iteration counts and input sizes.

We use R with ggplot2 to create plots to show the data.

### The Python Test

The test is run using the python script `python_code/find-times.py`. It creates
a csv file with the data.

### The C Test

The shell script `testc.sh` is designed to run the C function in a loop testing
various numbers of iterations and input sizes. You can save a CSV file of the
results by entering

```{sh}
./testc.sh > c_test_data.csv
```

into the shell.

**Note**: the C function does not compile on Mac OS X, because the timer function
only exists on other OSes. I may look into a more portable option later.

### The Assembly Test
We implemented a `combine_array` function in assembly, which takes as input two float arrays and performs the the `+=` operation.
We then replaced `update_coordinates` with three calls to `combine_array`, one call for each coordinate. 

TODO add timings

### Memory Profiling
To profile the memory we used the massif tool inside of valgrind.
The tool is used with the following commands:
```
valgrind --tool=massif  --massif-out-file=massif_out ./a.out 1048576 500 0;
ms_print massif_out > massif_print
```

Running the profiler on the c code using floats produces the following:

![c-float graph](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_c_float.png)

c-float graph ^

![c-double chart](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_c_double.png)

c-double graph ^

![c-c-asm chart](https://raw.githubusercontent.com/wjones127/Math442-HW1/master/memory_analysis/massif_graph_asm.png)

c-inline assembly with floats grpah ^

First, the x-axis is Gi which is number of instructions times 1,000 (because its giga).
We think of Gi as a unit of time.
The y-axis is MB, megabytes, the amount of memory on the heap.

Observations: we notice that the graphs for c-float and asm are similar, but that the x-axis is longer for asm. 
First, it is expected that the total amont of memory used by the two programs is the same, since our assembly optimizations were only for speeding up the `+=` operation, not reducing memory. However it is surprising that the x-axis is longer for asm. THis suggests that the asm code requires more instructions. Perhaps the compiler does some optimization, maybe vectorizes, to reduce the number of instructions.

TODO analyze double graph

- Sources for memory profiling:
    - http://valgrind.org/docs/manual/ms-manual.html
    - https://sites.google.com/a/case.edu/hpc-upgraded-cluster/home/important-notes-for-new-users/valgrind-utility
    - https://developer.gnome.org/optimization-guide/stable/massif.html.en

