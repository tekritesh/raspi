#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 4  // Number of CPU stress threads
#define LOG_FILE "system_monitor.log"  // Log file path

// Function to read CPU temperature
float get_cpu_temperature() {
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (fp == NULL) {
        perror("Failed to read temperature");
        return -1;
    }
    int temp_millideg;
    fscanf(fp, "%d", &temp_millideg);
    fclose(fp);
    return temp_millideg / 1000.0;  // Convert to degrees Celsius
}

// Function to read CPU voltage
float get_cpu_voltage() {
    FILE *fp = popen("vcgencmd measure_volts core", "r");
    if (fp == NULL) {
        perror("Failed to read voltage");
        return -1;
    }
    float voltage;
    fscanf(fp, "volt=%fV", &voltage);
    pclose(fp);
    return voltage;
}

// Function to read CPU frequency
int get_cpu_frequency() {
    FILE *fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
    if (fp == NULL) {
        perror("Failed to read CPU frequency");
        return -1;
    }
    int freq;
    fscanf(fp, "%d", &freq);
    fclose(fp);
    return freq / 1000;  // Convert to MHz
}

// Function to get the current timestamp
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Function to log system info and prime number to the file
void log_system_data(FILE *log_file, const char *timestamp, float temp, float voltage, int frequency, long prime) {
    fprintf(log_file, "%s, %.2f°C, %.2fV, %d MHz, Prime: %ld\n", timestamp, temp, voltage, frequency, prime);
    fflush(log_file);  // Ensure immediate write to the log file
}

// Prime number calculation function
void *calculate_primes(void *arg) {
    FILE *log_file = (FILE *)arg;  // Log file passed to the thread
    long num = 2;

    while (1) {
        bool is_prime = true;
        for (long i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            // Get system info and log the prime number
            char timestamp[20];
            get_timestamp(timestamp, sizeof(timestamp));

            float temp = get_cpu_temperature();
            float voltage = get_cpu_voltage();
            int frequency = get_cpu_frequency();

            log_system_data(log_file, timestamp, temp, voltage, frequency, num);

            // Print prime to console
            // printf("Prime found: %ld\n", num);
        }

        num++;
    }

    return NULL;
}

// Monitoring function (to run in a separate thread)
void monitor_system() {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    while (1) {
        float temp = get_cpu_temperature();
        float voltage = get_cpu_voltage();
        int frequency = get_cpu_frequency();

        char timestamp[20];
        get_timestamp(timestamp, sizeof(timestamp));

        // Print to console
        printf("\n--- System Monitoring ---\n");
        printf("Timestamp: %s\n", timestamp);
        printf("CPU Temperature: %.2f°C\n", temp);
        printf("CPU Voltage: %.2fV\n", voltage);
        printf("CPU Frequency: %d MHz\n", frequency);
        printf("-------------------------\n");

        // Log system data
        fprintf(log_file, "%s, %.2f°C, %.2fV, %d MHz, Prime: None\n", timestamp, temp, voltage, frequency);
        fflush(log_file);  // Ensure data is written immediately

        sleep(5);  // Update every 5 seconds
    }

    fclose(log_file);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t monitor_thread;

    // Open the log file in append mode
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return -1;
    }

    // Create threads for stress test
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculate_primes, log_file);  // Pass log file to each thread
    }

    // Create a separate thread for monitoring and logging
    pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitor_system, NULL);

    // Wait for all threads to complete (they never will in this case)
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_join(monitor_thread, NULL);

    fclose(log_file);  // Close the log file when done

    return 0;
}
