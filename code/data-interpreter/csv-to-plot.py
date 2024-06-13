#! /usr/local/bin/env python3
import matplotlib.pyplot as plt
import csv
import sys

file = sys.argv[1]

time = []
x = []
y = []

start = -1
end = 0

with open(file, "r") as csvfile:
    plots = csv.reader(csvfile, delimiter=",")

    for row in plots:
        if start == -1:
            start = 0
            continue
        if start == 0:
            start = int(row[0])
        end = int(row[0]) - start
        time.append(int(row[0]) - start)
        x.append(float(row[1]))
        y.append(float(row[2]))

fig, (xPlot, yPlot) = plt.subplots(2, 1, sharex=True)

fig.set_figheight(4.25)
fig.set_figwidth(7)

xPlot.plot(time, x)
xPlot.set_xlim(0, end)
xPlot.set_ylim(-1.1, 1.1)
xPlot.spines["top"].set_visible(False)
xPlot.spines["right"].set_visible(False)
xPlot.axhline(0, color="grey", linewidth="0.8", linestyle="--")
xPlot.xaxis.set_tick_params(labelbottom=True)
xPlot.set_xlabel("Time (ms)")
xPlot.set_ylabel("X-Axis Value")

yPlot.plot(time, y)
yPlot.set_xlim(0, end)
yPlot.set_ylim(-1.1, 1.1)
yPlot.spines["top"].set_visible(False)
yPlot.spines["right"].set_visible(False)
yPlot.axhline(0, color="grey", linewidth="0.8", linestyle="--")
yPlot.xaxis.set_tick_params(labelbottom=True)
yPlot.set_xlabel("Time (ms)")
yPlot.set_ylabel("Y-Axis Value")

plt.tight_layout()
filepath = file.split('/')
name = filepath[len(filepath)-1].split('.')[0] + ".svg"
print(name)
plt.savefig(name)
