
## 1. Title Page:

##### Assingment 3 : Raspberrypi 4 Project
##### Author(s): Ritesh Tekriwal
##### Email: rtekri@uw.edu
##### Date of submission : March 11, 2025


## 2. Problem Statement/Objective:
**"Park Off"**

Finding a parking spot in downtown of any city is a major issue and especially with Return to Office policies, this can even intensified.  Moreover, if you live in downtown and prefer to walk, unruly weather is quite an annoyance. Here is an attempt to use Traffic Cams to find parking spots and street wise weather updates in near real time. 

## 3. Introduction:

[Seattle Gov](https://www.seattle.gov/) has an extensive array of Traffic Cameras spread across the city that update the image and sometimes videos every minute. 

<img src="../img/assignment_3/seattle_gov.png" width="400">


The cameras are located on all major jucntions and crossings and have a decent picture as you can see 

<img src="../img/assignment_3/sample.png" width="200"> 
<img src="../img/assignment_3/sample2.png" width="200">


This project aims at querying this data, make a cache, and then run some object detection model on these images to find cars parked by the curbs.

A stretch goal is to detect the weather conditions by these images and get a near real time update if it is convinient to walk down a few blocks.

Finally, this could all be overlaid as a custom layer on Open Street Maps. 


## 4. Project Outline and Goals:
- Pipeline deployed on Raspberry Pi that downloads these Traffic Images near realtime and caches locally
- Overlay Traffic Cam Position with the GIS Parking Data
- Car detection to see if Cars are parked in the above location
- Identify Rainy or Not Rainy Weather 
- Open Source Python Package for others to join in 

## 5. Constrains:
- Every Traffic Cam updates 1 min
- Glare often spoils the picture quality
 

## 6. Problem Breakdown:


Success/Failures

- Rpi doesnt support many bluetooth devices as headset head unit. It more often picks it up as an Audio Sink [Link](https://forums.raspberrypi.com/viewtopic.php?t=295590)


#### 5 Equipment Required 
1. Raspberry Pi board with Installed Firmware
2. Power supply compatible with the Raspberry Pi model
3. Wireless router (plus Ethernet ports) connected to the internet



## 6 Steps

#### 4.1 Testing Speaker APIs

#### 4.2 Testing Dyson APIs

#### 4.3 Testing BLE Microphone

#### 4.4 Streaming BLE Microphone

#### 4.5 Testing Setup on PC

#### 4.6 Measure Latency to Play Chirp

#### 4.7 Measure Frequency in Run time for the unit chirp signal

https://www.medicalnewstoday.com/articles/251489#Unpleasant-sounds-are-between-2-000-to-5-000-Hz-frequency-range






#### 4. Deploy on Rpi

## 5. Results:

#### Fig1


#### Fig2


#### Fig3


## 6. Discussion:

#### Applicability to Mass/Limited Production


## 7. Conclusion:
• Summarize the main findings
• Emphasize the significance of the results

## 8. References:
- [Wikipedia](https://www.wikipedia.org/)
- [RaspberryPi](https://www.raspberrypi.com/)
- [StackOverFlow](https://stackoverflow.com/)

## 9. Acknowledgments:


## 10. Appendices:


## 11. Figures and Tables:

