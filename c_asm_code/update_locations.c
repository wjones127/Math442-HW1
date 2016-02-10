#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void triangle_number()
{

    // rbx = counter
    // rax = sum
    uint64_t a = 10;
    uint64_t b = 0;
    asm (
         // rax = sum
         // pre
         "movq %1, %%rbx;\n"
         "movq $0, %%rax\n"
         "movq $0, %%rcx\n"

         // loop
         "loop_start:\n"
         "addq %%rcx, %%rax\n"
         "addq $1, %%rcx\n"

         "cmpq %%rbx, %%rcx\n"
         "jl loop_start\n"

         // loop end
         "movq %%rax, %0\n"
         :"=r"(b)        /* output c = %0  */
         :"r"(a)
         :"%rax"         /* clobbered register */
         );    
    printf("a = %" PRId64 "\n", a);
    printf("b = %" PRId64 "\n", b);
}

void combine_arrays(uint64_t *arr, uint64_t *add, uint64_t size)
{
    /* Adds the number add to all elements in array */

    uint64_t out;
    asm (
         //"movq %1, %%rbx;\n"
         "movq %1, %%rax\n" // target array
         "movq %2, %%rbx\n" // add array
         "movq %3, %%rdx\n" // size 
         "movq $0, %%rcx\n" // counter

         "loop_start3:\n"
         "movq (%%rbx, %%rcx, 8), %%rsi\n"
         "addq %%rsi, (%%rax, %%rcx, 8)\n"
         "incq %%rcx\n"

         "cmpq %%rdx, %%rcx\n"
         "jl loop_start3\n"

         // loop end
         "movq $0, %0\n"
         :"=r"(out)
         :"r"(arr), "r"(add), "r"(size)
         :"%rax"         /* clobbered register */
         );    
    assert(out == 0);
}

void double_arr() 
{
    printf("here\n");
    //double arr[2] = {1.0, 2.0}
    //uint64_t length = 2;
    //uint64_t out
    //asm (
    //    "xorpd   xmm0, xmm0\n"
    //    "addsd   xmm0, [rdi]\n"
    //    "add     rdi, 8\n"
    //    "dec     rsi\n"
    //    "jnz     next\n"


    //     // loop end
    //     "movq $0, %0\n"
    //     :"=r"(out)
    //     :"r"(arr), "r"(add), "r"(size)
    //     :"%rax"         /* clobbered register */
    //     );    

}

//void update_coords_better(float *x, float *y, float *z, float *vx, float *vy,
//                   float *vz, size_t size) 
//{
//    combine_arrays_better(x, vx, size);
//    combine_arrays_better(y, vy, size);
//    combine_arrays_better(z, vy, size);
//
//}

void update_coords(float *x, float *y, float *z, float *vx, float *vy,
                   float *vz, size_t size) 
{
    for (uint32_t i = 0; i < size; i++) {
        x[i] += vx[i];
        y[i] += vy[i];
        z[i] += vz[i];
  }
}

int main(int argc, char *argv[])
{
    assert(argc > 0);
    assert(argv);

    uint64_t size = 4;
    uint64_t pos[4] = {10, 20, 30, 40};
    uint64_t vel[4] = {1, 2, 3, 4};

    //printf("%lf\n", pos[0]);
    //printf("%lf\n", pos[1]);
    //printf("%lf\n", pos[2]);

    combine_arrays(pos, vel, size);

    //printf("%lf\n", pos[0]);
    //printf("%lf\n", pos[1]);
    //printf("%lf\n", pos[2]);

    printf("[0] = %" PRId64 "\n", pos[0]);
    printf("[1] = %" PRId64 "\n", pos[1]);
    printf("[2] = %" PRId64 "\n", pos[2]);
    printf("[3] = %" PRId64 "\n", pos[3]);
    return 0;
}
