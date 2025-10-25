# Joystick Degree Project
The following repo contains all the code, data, and figures for the degree project **Investigating the problem of joystick drift within video game controllers**. The abstract and report for this degree project can be found on the [KTH DiVA Portal](https://kth.diva-portal.org/smash/record.jsf?aq2=%5B%5B%5D%5D&c=30&af=%5B%5D&searchType=LIST_LATEST&sortOrder2=title_sort_asc&query=&language=sv&pid=diva2%3A1937531&aq=%5B%5B%5D%5D&sf=all&aqe=%5B%5D&sortOrder=author_sort_asc&onlyFullText=false&noOfRows=50&dswid=-1800).

## Components
An STM32F401C-Discovery board was used to collect data from the joysticks of video game controllers. The C code written for this board can be found at the following CubeMX projects: 
- [joystick-stm32f4-cubeMX](code/joystick-stm32f4-cubeMX) for controllers with potentiometer-based joystick sensors, similar to Alps Alpine RJKXV.
- [dreamcast-stm32f4-cubeMX](code/dreamcast-stm32f4-cubeMX) for the Dreamcast controller, which uses joysticks with HALL-effect sensors.
- [n64-stm32f4-cubeMX](code/n64-stm32f4-cubeMX) for the N64 controller, which uses a joystick with rotary encoder sensors. A separate PCB was developed to interface with the N64 joystick.
A set of Python scripts was developed to help collect data into CSV files, create graphs, and make calculations. These scripts can be found at [data-interpreter](code/data-interpreter).

## Contributors
Degree Project by Sebastian Thaeron and Kristoffer Andersson.
