
## 1. Title Page:

##### Assingment 2 : Raspberrypi 4 Exploration
##### Author(s): Ritesh Tekriwal
##### Email: rtekri@uw.edu
##### Date of submission : Feb 12, 2025


## 2. Abstract:
This Assignment is about exploring the capabilities of the Raspberry Pi 4 i.e the software, features, options and potential limitations. In this Assignment,we are going to characterize the target board hardware and software by using the C programming language.


## 3. Introduction:

Raspberry pi is a mini portable computer that needs an Operating System to work. This work is about how we characterise the board to understand it's capabilities and potential. 

#### 3.1 Equipment Required 
1. Raspberry Pi board with Installed Firmware
2. Power supply compatible with the Raspberry Pi model
5. Wireless router (plus Ethernet ports) connected to the internet

## 4 Characterization Questions
### 4.1. What SoC is on the target board? What version and manufacturer of the SoC?

To get the SOC of the target board, first we need to get info like versiona and Revision ID.

```
cat /proc/cpuinfo 

```

<img to be added>

This returns the Revison ID ie **d03115** which when crossreferenced on the [website](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)  tells us that the it **Version 1.5** manufactured by **Sony UK** 



### 4.2. What features are present on the board/SoC?
This can be divded into the following groups: 

#### Performance & GPU
SoC: Broadcom BCM2711
CPU: Quad-core Cortex-A72 (ARM v8, 64-bit, 1.5 GHz)
    Cores:4
    Clock Speed: ~1.5GHz ( max 1.8Ghz, min 0.6Ghz)
    Threads per Core : 1
    Intruction Set: AArch64
GPU: Broadcom VideoCore VI
    Clock Speed: ~500MHz
Graphics support: OpenGL ES 3.1, 4K decoding (H.265), dual-display

#### Memory(RAM)
Type: LPDDR4-3200 SDRAM 
Memory Speed: 3200 MT/s (MegaTransfers per second)
Memory Bus Width: 32-bit
Shared Memory: CPU & GPU share RAM (adjustable via firmware)
Available Sizes: 2GB, 4GB, and 8GB models


#### Storage
MicroSD slot (for OS & storage)
USB boot support (boot from SSD/HDD via USB 3.0)

#### Display & Graphics
Dual micro-HDMI ports (supports two 4K displays @ 60Hz)
Supports H.265 (HEVC) 4Kp60 decode, H.264 1080p60 encode/decode
OpenGL ES 3.1 support

#### Connectivity
Wi-Fi: 802.11ac (dual-band 2.4GHz / 5GHz)
Bluetooth: 5.0 (BLE)
Gigabit Ethernet (true 1 Gbps speed)
USB Ports:
    2 × USB 3.0 
    2 × USB 2.0
GPIO: 40-pin 

#### Power
Power input: USB-C (5V/3A recommended)


### 4.3. What size caches are present in the Raspberry Pi?

```
lscpu

```
<img with cpu_info>

L1d cache:128 KiB
L1i cache:192 KiB
L2 cache:1 MiB

### 4.4. What is the pin layout on this specific version of the target board?

```
pinout 

```
<img pin_out>

### 4.5. How does the board boot? What is the process?



### 4.6. What software is available to enhance the pins? Test the software?


### 4.7. How much memory is available on the board?


### 4.8. What is the maximum memory configuration?


### 4.9. How many different types of memory are on the board?


### 4.10. What is the performance of the memory?


### 4.11. What is the name and release version of the Operating System used on the target board?

```
cat /etc/os-release

```
<img os_release>

### 4.12. What is the compiler name and version?

```
gcc --version

```
<img compiler_version>

### 4.13. How long does it take for a context switch?
### 4.14. What is involved in adding an on-switch to the Raspberry Pi?
### 4.15. What is the interrupt latency for the board? E.g., from an interrupt to the first instruction executed
in the service routine?
### 4.16. How much time does it take to copy 1 KB, 1 MB, and 1GB in bytes, half words, and words in RAM?
### 4.17. How much time does it take to copy 1 KB, 1 MB, and 1GB in bytes, half words, and words on the
filing system?
6
### 4.18. How long does it take between reboot and an active board? Is it deterministic?
### 4.19. How long does it take to halt the board? Is it deterministic?
### 4.20. Is the board reliable? If so, how reliable? Code examples?
### 4.21. Find and run some benchmarks?
### 4.22. Determine the speed of integer arithmetic with a benchmark.
### 4.23. Determine the rate of floating-point arithmetic with a benchmark.
### 4.24. Write a multithreaded example application that illustrates the producer-consumer algorithm with
protected data running on multiple processors.
### 4.25. What are the operating temperature ranges?
### 4.26. What is the power consumption without load and with load?
### 4.27. What would be a useful stress test to determine reliability?
### 4.28. Does temperature affect performance?
### 4.29. Determine how much energy is required to run a benchmark. E.g., use temperature as a rough guide.
### 4.30. How deterministic is the board? How real-time? Code examples?


## 5. Results:

#### Fig1


#### Fig2


#### Fig3



## 6. Discussion:


## 7. Conclusion:
• Summarize the main findings
• Emphasize the significance of the results

## 8. References:
- [Wikipedia](https://www.wikipedia.org/)
- [RaspberryPi](https://www.raspberrypi.com/)
- [StackOverFlow](https://stackoverflow.com/)
- [ChatGPT](https://chatgpt.com/)

## 9. Acknowledgments:


## 10. Appendices:


## 11. Figures and Tables:

