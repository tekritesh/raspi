#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <linux/gpio.h>

#define GPIO_PIN 17  

//func to get time
double get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec +  ((double)tv.tv_usec)*(0.000001) ;
}

int main() {
    char gpio_path[64];
    int gpio_fd;
    struct gpioevent_request req;
    struct gpioevent_data event;
    double start_time, end_time, latency;

    // Configure the GPIO as an input with rising-edge detection
    snprintf(gpio_path, sizeof(gpio_path), "/dev/gpiochip0");
    gpio_fd = open(gpio_path, O_RDONLY);
    if (gpio_fd < 0) {
        perror("Failed to open GPIO device");
        exit(1);
    }

    req.lineoffset = GPIO_PIN;
    req.handleflags = GPIOHANDLE_REQUEST_INPUT;
    req.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
    snprintf(req.consumer_label, sizeof(req.consumer_label), "LatencyTester");

    if (ioctl(gpio_fd, GPIO_GET_LINEEVENT_IOCTL, &req) < 0) {
        perror("Failed to configure GPIO event");
        close(gpio_fd);
        exit(1);
    }

    printf("Waiting for interrupt on GPIO %d...\n", GPIO_PIN);
    start_time = get_time_in_microseconds();
    printf("StartTime: %f seconds\n", start_time);

    // Wait for the first interrupt event
    if (read(req.fd, &event, sizeof(event)) != sizeof(event)) {
        perror("Failed to read GPIO event");
        close(req.fd);
        close(gpio_fd);
        exit(1);
    }

    end_time = get_time_in_microseconds();
    printf("EndTime: %f seconds\n", end_time);
    latency = end_time - start_time;

    printf("Interrupt latency: %f seconds\n", latency);

    close(req.fd);
    close(gpio_fd);

    return 0;
}
