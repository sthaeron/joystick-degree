# Joystick Degree Project

## Finished Coponents

Contains work on N64 Controller Sensor Rotary Encoder and Potentiometer based joystick sensors (similar to Alps Alpine RJKXV)

Data-Interpreter componenet is a python script that will take data from the HID configured STM32F401C-Discovery and create a graph of it.
Current program code is for STM32F051-Discovery with a TTL device attached.

## Questions we have:

according to `jstest /dev/input/js0` Nintendo Switch Pro Controller sends data for joysticks as values from -32767 and 32767 which is a signed 16 bit integer. Both STM32F0 and STM32F4 Discovery only have 12 bit ADC's. How should we process that analog data as a result?

For the rotary encoder, the code seems to "drift" as the interrupts aren't able to keep up in real time with joystick movement, how could we fix this?



Degree Project by Kristoffer Andersson and Sebastian Thaeron


