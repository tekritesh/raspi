#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

#define NUM_ITERATIONS 100000

//func to get time
uint64_t get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// Switching b/w parent and child process by passing a buffer
int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[1];
    uint64_t start_time, end_time, total_time;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            read(pipe1[0], buffer, 1);  // Receive token from parent
            write(pipe2[1], buffer, 1); // Send token back to parent
        }
    } else {
        // Parent process
        buffer[0] = 'x';  // Token to send
        start_time = get_time_in_microseconds();

        for (int i = 0; i < NUM_ITERATIONS; i++) {
            write(pipe1[1], buffer, 1); // Send token to child
            read(pipe2[0], buffer, 1);  // Receive token from child
        }

        end_time = get_time_in_microseconds();
        total_time = end_time - start_time;
        
        printf("Total time for %d context switches: %lu microseconds\n", NUM_ITERATIONS, total_time);
        printf("Average time per context switch: %.2f microseconds\n", total_time / (2.0 * NUM_ITERATIONS));
    }

    return 0;
}
