#! /usr/local/bin/env python3
import matplotlib.pyplot as plt 
import csv 
import sys

controller = sys.argv[1]
file = sys.argv[2]

time = []
x = []
y = []

with open(file, "r") as csvfile:
    plots = csv.reader(csvfile, delimiter = ",")

    for row in plots:
        time.append(int(row[0]))
        x.append(float(row[1]))
        y.append(float(row[2]))

fig, (xPlot, yPlot) = plt.subplots(2, 1, sharex=True)

xPlot.plot(time, x)
xPlot.set_xlabel("Time (ms)") 
xPlot.set_ylabel("Y ADC Value")

yPlot.plot(time, y)
yPlot.set_xlabel("Time (ms)") 
yPlot.set_ylabel("Y ADC Value")

plt.show()
