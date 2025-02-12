#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)


//func calculate time
uint64_t get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void copy_file(const char *src_filename, const char *dest_filename, size_t buffer_size) {
    FILE *src = fopen(src_filename, "rb");
    FILE *dest = fopen(dest_filename, "wb");
    if (!src || !dest) {
        perror("Failed to open file");
        exit(1);
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate buffer");
        fclose(src);
        fclose(dest);
        exit(1);
    }

    uint64_t start_time = get_time_in_microseconds();
    size_t bytes;
    while ((bytes = fread(buffer, 1, buffer_size, src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    uint64_t end_time = get_time_in_microseconds();

    printf("File copy with buffer size %lu bytes took %lu microseconds\n", buffer_size, end_time - start_time);

    free(buffer);
    fclose(src);
    fclose(dest);
}

int main() {
    printf("Benchmarking file copy times:\n");
    copy_file("test_1KB.bin", "copy_1KB.bin", 1);         // Byte copy (1 byte buffer)
    copy_file("test_1MB.bin", "copy_1MB.bin", 2);         // Half-word copy (2-byte buffer)
    copy_file("test_1GB.bin", "copy_1GB.bin", 4);         // Word copy (4-byte buffer)

    return 0;
}
