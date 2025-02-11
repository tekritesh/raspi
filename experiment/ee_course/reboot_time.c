#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>  

#define HOST "192.168.4.49"  // Replace with your Raspberry Pi's IP address
#define PASSWORD "root"  // Replace with your actual password
#define REBOOT_CMD "sshpass -p " PASSWORD " ssh pi@" HOST " 'nohup sudo reboot > /dev/null 2>&1 &'"
#define HALT_CMD "sshpass -p " PASSWORD " ssh pi@" HOST " 'nohup sudo halt > /dev/null 2>&1 &'"
#define PING_CMD "ping -c 1 -W 1 " HOST " > /dev/null 2>&1"

uint64_t get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // printf("Time %f", (double)tv.tv_sec + (double)tv.tv_usec*(0.000001));
    return tv.tv_sec*1000000 + tv.tv_usec;
}

int is_host_online() {
    return (system(PING_CMD) == 0);
}

int main(int argc, char *argv[]) {
    printf("Measuring reboot time for %s...\n", HOST);

    // Step 1: Record the start time and issue the reboot command
    double start_time = get_time_in_microseconds();

    if (strcmp(argv[1], "reboot") == 0){
        printf("Issuing reboot command...\n");
        system(REBOOT_CMD);

        printf("Waiting for %s to go offline...\n", HOST);
        while (is_host_online()) {
            usleep(5000);  // Check every 5 milliseconds
        }

        // Step 3: Wait for the host to come back online
        printf("Waiting for %s to come back online...\n", HOST);
        while (!is_host_online()) {
            usleep(5000);
        }
    }

    if (strcmp(argv[1], "halt") == 0){
        printf("Issuing halt command...\n");
        system(HALT_CMD);

        printf("Waiting for %s to go offline...\n", HOST);
        while (is_host_online()) {
        usleep(5000);  // Check every 5 milliseconds
        }
    }
    

    // Step 4: Record the end time and calculate the total time
    uint64_t end_time = get_time_in_microseconds();
    double total_time_seconds = (end_time - start_time) / 1000000.0;

    printf("Time Taken: %.2f seconds\n", total_time_seconds);

    return 0;
}
