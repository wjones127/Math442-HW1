#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BILLION  1E9
#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

/*
 * Used the following function to get time for Mac OS X.
 * Based on this snippet: https://gist.github.com/alfwatt/3588c5aa1f7a1ef7a3bb
 */

int current_utc_time(struct timespec *ts) {

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
    return 1;
#else
    return clock_gettime(CLOCK_REALTIME, ts);
#endif
}

uint64_t current_time()
{
    /* returns time in nanoseconds */
    struct timespec tp;
    int res = current_utc_time(&tp); 
    if (res == -1) {
        fprintf(stderr, "Failure with clock_gettime");
        return 0;
    }
    return BILLION * tp.tv_sec + tp.tv_nsec;
}

double random_float (int32_t lower_bound, int32_t upper_bound) 
{
    double scale = upper_bound - lower_bound;
    return ((rand() / (double) RAND_MAX) * scale) + lower_bound;
}

double* generate_random_array (size_t array_size, int32_t bound) 
{
    double *array = calloc(array_size, sizeof(double));
    assert(array && "give us memory");
    for (uint32_t i = 0; i < array_size; i++) {
        array[i] = random_float(-1 * bound, bound);
    }
    return array;
}

void update_coords(double *x, double *y, double *z, double *vx, double *vy,
                   double *vz, size_t size) 
{
    for (uint32_t i = 0; i < size; i++) {
        x[i] += vx[i];
        y[i] += vy[i];
        z[i] += vz[i];
  }
}

double sum(double *arr, size_t size) 
{
    double sum = 0;
    for (uint32_t i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}


int main(int argc, char **argv) 
{
    assert(argc == 3 && "require two arguments to run");
    uint32_t size = strtol(argv[1], NULL, 0);
    uint32_t iter = strtol(argv[2], NULL, 0);
    assert(iter > 0 && size > 0 && "iter and size must be positive");
    printf("%d,%d,", size, iter);
  
    srand(size); 
  
    // Position vectors
    double *x = generate_random_array(size, 1000);
    double *y = generate_random_array(size, 1000);
    double *z = generate_random_array(size, 1000);

    // Velocity vectors
    double *vx = generate_random_array(size, 1);
    double *vy = generate_random_array(size, 1);
    double *vz = generate_random_array(size, 1);

    uint64_t start = current_time();
    for (uint32_t i = 0; i < iter; i++) {
        update_coords(x, y, z, vx, vy, vz, size);
    }
    uint64_t end = current_time();
    printf("%lu,", end - start);

    // checksum is an invariant of the input parameters (size and iter)
    double chksum = sum(x, size) + sum(y, size) + sum(z, size);
    printf("%.6f\n", chksum);
 
    free(x); 
    free(y); 
    free(z); 
    free(vx);
    free(vy);
    free(vz);
}
