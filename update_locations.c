#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))



float random_float (int lower_bound, int upper_bound) {
  float scale = upper_bound - lower_bound;
  float x = ((rand()/(float)RAND_MAX) * scale) + lower_bound;
  return x;
}

float* generate_random_array (float *array, size_t array_size, int bound) {
  array = (float *) malloc ( sizeof (float) * array_size); // Allocate array
  
  for (uint32_t i = 0; i < array_size; i++)
    array[i] = random_float(-bound, bound);

  return array;
}

void update_coords(float *x, float *y, float *z, float *vx, float *vy,
                   float *vz, size_t size) {
  for (uint32_t i = 0; i < size; i++) {
    x[i] = x[i] + vx[i];
    y[i] = y[i] + vy[i];
    z[i] = z[i] + vz[i];
  }
}


int main(int argc, char **argv) {
  int size = 10; //strtol(argv[0], NULL, 10);
  int iter = 10; //strtol(argv[1], NULL, 10);
  
  srand(size); // Set time seed
  
  // Position vector
  float *x = generate_random_array(x, size, 1000);
  float *y = generate_random_array(y, size, 1000);
  float *z = generate_random_array(y, size, 1000);
  // Velocity vector
  float *vx = generate_random_array(y, size, 1);
  float *vy = generate_random_array(y, size, 1);
  float *vz = generate_random_array(y, size, 1);

  for (uint32_t i = 0; i < size; i++)
    printf("%lu: (%.6f, %.6f, %.6f)\n", (unsigned long)i, x[i], y[i], z[i]);

  for (uint32_t i = 0; i < iter; i++)
    update_coords(x, y, z, vx, vy, vz, size);

  for (uint32_t i = 0; i < size; i++)
    printf("%lu: (%.6f, %.6f, %.6f)\n", (unsigned long)i, x[i], y[i], z[i]);

  // Free vectors
  free(x); 
  free(y); 
  free(z); 
  free(vx);
  free(vy);
  free(vz);
}
