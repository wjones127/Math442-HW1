#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

    /*
     * jmp loop_cond
     * loop_start:
     * addl 1, counter
     * addl counter, sum
     * loop_cond:
     * cmpl 17, counter
     * jl loop_start
     * end_loop:
     */

    /* Which of the following is better and why?
    asm ("movq %1, %0;\n"
         "addq %2, %0\n"
         */
    //asm ("movq %1, %%rax;\n"
    //     "movq %2, %%rbx\n"
    //     "addq %%rax, %%rbx\n"
    //     "movq %%rbx, %0;"
    //     :"=r"(c)        /* output c = %0  */
    //     :"r"(a), "r"(b) /* input a = %1, b = %2*/
    //     :"%rax"         /* clobbered register */
    //    );

    // rbx = counter
    // rax = sum
    //asm (
    //     // pre
    //     "movq $0, %%rbx;\n"
    //     "movq $0, %%rax\n"
    //     "movq %1, %%rcx\n"

    //     // loop
    //     "loop_start:\n"
    //     "addq %%rbx, %%rax\n"
    //     "addq $1, %%rbx\n"

    //     // loop condition
    //     "loop_cond:\n"
    //     "cmpq %%rcx, %%rbx\n"
    //     "jl loop_start\n"

    //     // loop end
    //     "movq %%rax, %0\n"
    //     :"=r"(c)        /* output c = %0  */
    //     :"r"(a) /* input a = %1, b = %2*/
    //     :"%rax"         /* clobbered register */
    //     );    
    /*printf("b = %llu\n", b);*/

    //uint64_t px[2] = {11, 22};
    //uint64_t y = 0;
    //printf("px[0] = %" PRId64 "\n", px[0]);
    //printf("px[1] = %" PRId64 "\n", px[1]);
    //printf("y = %" PRId64 "\n", y);
    //asm (
    //     "movq %1, %%rbx;\n"
    //     "movq 8(%%rbx), %%rax\n"
    //     "movq %%rax, %0\n"
    //     :"=r"(y)        /* output c = %0  */
    //     :"r"(px) /* input a = %1, b = %2*/
    //     :"%rax"         /* clobbered register */
    //     );    
    //printf("px[0] = %" PRId64 "\n", px[0]);
    //printf("px[1] = %" PRId64 "\n", px[1]);
    //printf("y = %" PRId64 "\n", y);

void run() 
{
    uint64_t size = 4;
    uint64_t pos[4] = {11, 22, 33, 2};
    uint64_t vel[4] = {1, 0, 0, 0};
    uint64_t out[4] = {0, 0, 0, 0};
    asm (
        // pre
         "movq %1, %%rsi\n" /* position array */
         "movq %2, %%rbx;\n" /* velocity array */

         "movq $0, %%rcx\n" /* counter */
         "movq %3, %%rdx\n"  /* size */
         "movq %0, %%rax\n" /* position array */

         //"loop_start:\n"
         //
         "movq (%%rsi, %%rcx, 8), %%r8\n"
         "addq %%r8, (%%rbx, %%rcx, 8)\n"
         "movq (%%rbx, %%rcx, 8), %%r8\n"
         //"addq %%r8, (%%rax, %%rcx, 8)\n" /* problem here --- how do I access elements of %0? */

         //"addq $1, %%rcx\n" /* todo change to incq */

         // loop condition
         //"cmpq %%rdx, %%rcx\n"
         //"jl loop_start\n"

         // end_condition
         "movq %%rax, %0\n"

         :"=g"(out)         /* output c = %0  */
         :"r"(pos), "r"(vel), "r"(size) /* %1 %2 %3*/
         :"%rax"         /* clobbered register */
         );    
    printf("out[0] = %" PRId64 "\n", out[0]);
    printf("out[1] = %" PRId64 "\n", out[1]);
    printf("out[2] = %" PRId64 "\n", out[2]);


}

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
    run();
    return 0;
}
