#! /usr/local/bin/env python3
import matplotlib.pyplot as plt 
import csv 

time = []
x = []
y = []

with open("joystick-test.csv", "r") as csvfile:
    plots = csv.reader(csvfile, delimiter = ",")

    for row in plots:
        time.append(int(row[0]))
        x.append(float(row[1]))
        y.append(float(row[2]))

(xPlot, yPlot) = plt.subplots(2, 1, sharex=True)

xPlot.plot(time, x)
xPlot.set_ylim([-1, 1])
xPlot.xlabel("Time (ms)") 
xPlot.set_ylabel("Y ADC Value")

yPlot.plot(time, y)
xPlot.set_ylim([-1, 1])
yPlot.xlabel("Time (ms)") 
yPlot.set_ylabel("Y ADC Value")

plt.show()
