#include <stdint.h>
#include <stdio.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

float* generate_random_array (float *array, size_t array_size, int bound) {
  array = (float *) malloc ( sizeof (float) * array_size); // Allocate array
  
  srand(time(NULL)); // Need a better way of doing this

  for (uint32_t i = 0; i < array_size; i++)
    array[i] = (rand() % (2 * bound)) - bound;

  return array;
}

 int main() { 

   uint32_t n = 10;
   float *x = generate_random_array(x, n, 5);

  for (uint32_t i = 0; i < n; i++)
    printf("%.6f\n", x[i]);

  free(x); // Need to free x

}
