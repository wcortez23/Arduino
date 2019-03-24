# Arduino
# Python3 
Python3 Control of Arduino Data Logger


The reason for controlling an arduino script through an rpi is that the pi GPIO has proven to be finnicky for time 
sensetive I/O control. Arduino has extensive libraries and can manage clock sensetive I/O , which is a requirement. 

Attempting to get load cell data from an HX711 load cell amplifier in Arduino, while controlling a single NEMA23
stepper motor on a stage uisng arduinos accelstepper library. 

Design intent is a load/displacement machine that plots load (kg) vs displacement (of stepper) as it drives into a sample. 
Need to plot data to a csv file. 

I started writing a Tkinter gui in python3 to show the general layout of the process. 
