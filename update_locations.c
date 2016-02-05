#include <stdint.h>
#include <stdio.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void generate_random_array (float *array, size_t array_size, float bound) {
  srand(time(NULL));
  for (uint32_t i = 0; i < array_size; i++)
    array[i] = rand() % 40;
}

 int main() { 

   uint32_t n = 10;
   float x[n];
   generate_random_array(x, n, 1);

  for (uint32_t i = 0; i < n; i++)
    printf("%.6f\n", x[i]);

}
