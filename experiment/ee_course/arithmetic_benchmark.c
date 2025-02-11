#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>

#define ITERATIONS 1000000000  // 1 billion iterations

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <integer|float>\n", argv[0]);
        return 1;
    }
    
    int a = 1, b = 2, c = 0;
    clock_t start, end;
    double cpu_time_used;

    if(strcmp(argv[1], "integer") == 0){
        printf("Benchmarking integer arithmetic...\n");
    }

    if(strcmp(argv[1], "float") == 0){
        printf("Benchmarking float arithmetic...\n");

        a = (float)a;
        b = (float)b;
        c = (float)c;
        a = 1.1;
        b = 2.5;
    }
    
    

    // Addition benchmark
    start = clock();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a + b;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Addition: %.2f million operations per second\n", (ITERATIONS / cpu_time_used) / 1e6);

    // Subtraction benchmark
    start = clock();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a - b;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Subtraction: %.2f million operations per second\n", (ITERATIONS / cpu_time_used) / 1e6);

    // Multiplication benchmark
    start = clock();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a * b;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Multiplication: %.2f million operations per second\n", (ITERATIONS / cpu_time_used) / 1e6);

    // Division benchmark
    start = clock();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a / (b + 1);  // Avoid division by zero
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Division: %.2f million operations per second\n", (ITERATIONS / cpu_time_used) / 1e6);

    printf("Benchmark completed!\n");
    return 0;
}
