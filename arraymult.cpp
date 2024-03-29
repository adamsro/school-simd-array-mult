#include "simd.h"

#define NUM_TRIALS	10

#if !defined(NUM)
#define NUM 1024
#endif

#define GNUPLOT 1

#define PRINT_SIMD 0
#define PRINT_NOSIMD 0
#define PRINT_DIFFERENCE 1

float A[NUM];
float B[NUM];
float C[NUM];

float Ranf(float, float);
int Ranf(int, int);

int main(int argc, char *argv[ ]) {

    double prec = omp_get_wtick();
    //fprintf( stderr, "Clock precision = %g\n", prec );

    for (int i = 0; i < NUM; i++) {
        A[i] = Ranf(-10.f, 10.f);
        B[i] = Ranf(-10.f, 10.f);
    }

    /****************************
     * SIMD test block
     * **************************/
    double time0 = Timer();
    for (int t = 0; t < NUM_TRIALS; t++) {
        SimdMul(A, B, C, NUM);
    }
    double time1 = Timer();

    double dts = (time1 - time0) / (float) NUM_TRIALS;
    if (PRINT_SIMD == 1) {
        if(GNUPLOT == 0) {
            printf("Average SIMD Elapsed time = %g\n", dts);
            printf("SIMD speed = %8.3f MFLOPS\n", ((float) NUM / dts) / 1000000.f);
        } else {
            // x-axis: #-of-elements y-axis: MFLOPS, do not need elapsed time
            printf("%d %8.3f\n", NUM, ((float) NUM / dts) / 1000000.f);
        }
    }

    /****************************
     * non SIMD test block
     * **************************/
    double time2 = Timer();
    for (int t = 0; t < NUM_TRIALS; t++) {
        NonSimdMul(A, B, C, NUM);
    }
    double time3 = Timer();

    double dtn = (time3 - time2) / (float) NUM_TRIALS;
    if(PRINT_NOSIMD == 1) { 
        if(GNUPLOT == 0) {
            printf("Average Non-SIMD Elapsed time = %g\n", dtn);
            printf("Non-SIMD speed = %8.3f MFLOPS\n", ((float) NUM / dtn) / 1000000.f);
            //printf("Speed-up = %g\n", dtn / dts);
        } else {
            // x-axis: #-of-elements y-axis: MFLOPS, do not need elapsed time
            printf("%d %8.3f\n", NUM, ((float) NUM / dtn) / 1000000.f);
        }
    }

    if(PRINT_DIFFERENCE == 1) {
        printf("%d %g\n", NUM, ((float) NUM / dtn) / (dtn/dts));
    }
    return 0;
}

float Ranf(float low, float high) {
    float r = (float) rand(); // 0 - RAND_MAX
    return ( low + r * (high - low) / (float) RAND_MAX);
}

int Ranf(int ilow, int ihigh) {
    float low = (float) ilow;
    float high = (float) ihigh + 0.9999f;
    return (int) (Ranf(low, high));
}
