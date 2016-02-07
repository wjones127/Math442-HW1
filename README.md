# Math442-HW1
First homework for Math 442 at Reed College: "Galaxy Explorers"

## Running the C Test

The shell script `testc.sh` is designed to run the C function in a loop testing
various numbers of iterations and input sizes. You can save a CSV file of the
results by entering

```{sh}
./testc.sh > c_test_data.csv
```

into the shell.

**Note**: the C function does not compile on Mac OS X, because the timer function
only exists on other OSes. I may look into a more portable option later.

### Notes on code
- spaces per tab in c (like python)
- 
