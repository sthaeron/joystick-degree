#! /usr/local/bin/env python3
import matplotlib.pyplot as plt
import csv
import sys

file = sys.argv[1]

time = []
x = []
y = []

start = 0

with open(file, "r") as csvfile:
    plots = csv.reader(csvfile, delimiter = ",")

    for row in plots:
        if start == 0: start = int(row[0])
        time.append(int(row[0]) - start)
        x.append(float(row[1]))
        y.append(float(row[2]))

fig, (xPlot, yPlot) = plt.subplots(2, 1, sharex=True)

xPlot.plot(time, x)
xPlot.set_xlabel("Time (ms)")
xPlot.set_ylabel("X-Axis Value")

yPlot.plot(time, y)
yPlot.set_xlabel("Time (ms)")
yPlot.set_ylabel("Y-Axis Value")

plt.show()
