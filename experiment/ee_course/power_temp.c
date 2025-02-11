#include <stdio.h>
#include <stdlib.h>

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

int main() {
    float temperature = get_cpu_temperature();
    float voltage = get_cpu_voltage();

    if (temperature >= 0 && voltage >= 0) {
        printf("CPU Temperature: %.2f°C\n", temperature);
        printf("CPU Voltage: %.2fV\n", voltage);
    } else {
        printf("Failed to retrieve system information.\n");
    }

    return 0;
}
