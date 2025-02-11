#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

uint64_t get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void benchmark_memory_copy(const char *label, void *src, void *dest, size_t size, size_t element_size) {
    uint64_t start_time, end_time;
    
    start_time = get_time_in_microseconds();
    for (size_t i = 0; i < size / element_size; i++) {
        memcpy((char *)dest + i * element_size, (char *)src + i * element_size, element_size);
    }
    end_time = get_time_in_microseconds();

    printf("%s - Size: %lu bytes, Element size: %lu bytes, Time: %lu microseconds\n",
           label, size, element_size, end_time - start_time);
}

int main() {
    size_t sizes[] = {1 * KB, 1 * MB, 1 * GB};
    const char *labels[] = {"1 KB", "1 MB", "1 GB"};
    
    void *src = malloc(1 * GB);
    void *dest = malloc(1 * GB);
    if (!src || !dest) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
    }

    // Fill source buffer with dummy data
    memset(src, 0xAA, 1 * GB);

    for (int i = 0; i < 3; i++) {
        size_t size = sizes[i];
        printf("Benchmark for %s:\n", labels[i]);
        
        benchmark_memory_copy("Byte copy (8-bit)", src, dest, size, 1);
        benchmark_memory_copy("Half-word copy (16-bit)", src, dest, size, 2);
        benchmark_memory_copy("Word copy (32-bit)", src, dest, size, 4);
        
        printf("\n");
    }

    free(src);
    free(dest);
    return 0;
}
