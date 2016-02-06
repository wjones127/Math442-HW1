#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1E9

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

float sum(float *x, int size) {
  float sum = 0;
  for (uint32_t i = 0; i < size; i++)
    sum += x[i];
  return sum;
}


int main(int argc, char **argv) {
  int size = strtol(argv[1], NULL, 0);
  int iter = strtol(argv[2], NULL, 0);

printf("%lu,%lu,", (unsigned long)size, (unsigned long)iter);
  
  srand(size); // Set time seed
  
  // Position vector
  float *x = generate_random_array(x, size, 1000);
  float *y = generate_random_array(y, size, 1000);
  float *z = generate_random_array(y, size, 1000);
  // Velocity vector
  float *vx = generate_random_array(y, size, 1);
  float *vy = generate_random_array(y, size, 1);
  float *vz = generate_random_array(y, size, 1);



  // Calculate time taken by a request
  struct timespec requestStart, requestEnd;
  clock_gettime(CLOCK_REALTIME, &requestStart); // Timer start
  
  for (uint32_t i = 0; i < iter; i++)
    update_coords(x, y, z, vx, vy, vz, size);

  clock_gettime(CLOCK_REALTIME, &requestEnd); // Timer end

  // Calculate time it took
  double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
    + ( requestEnd.tv_nsec - requestStart.tv_nsec )
    / BILLION;
  printf( "%lf,", accum );


  // Checksum
  float chksum = sum(x, size) + sum(y, size) + sum(z, size);
  printf("%.6f\n", chksum);
 
  // Free vectors
  free(x); 
  free(y); 
  free(z); 
  free(vx);
  free(vy);
  free(vz);
}
