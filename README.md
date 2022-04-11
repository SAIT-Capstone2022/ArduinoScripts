# MoistureSensorTest
This is the first test program we created to test the moisture sensor.

This test uses an analog water level sensor attatched to Analog pin 0. It includes code to format the serial output to CSV. It will likely require a python script to automate the process of writing the data to CSV, and sending it to a server accessed by our web page.
The arduino is coded to poll every 5 seconds, and if there is a change in +/- 20 (approx. 5%) between readings, it will write to the serial monitor.
During the testing, it was identified that the sensor will read a maximum of ~376, which is vastly different from what the datasheet suggest (0-1023).
