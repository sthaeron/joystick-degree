import matplotlib.pyplot as plt
import csv
import sys

file = sys.argv[1]

time = []
x = []
y = []

xDiff = []
yDiff = []

xMax = -2
xMin = 2
yMax = -2
yMin = 2

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

for i in range(1, len(x)):
    diff = abs(x[i] - x[i-1])
    if diff > xMax: xMax = diff
    if diff < xMin and diff > 0: xMin = diff
    xDiff.append(diff)

for i in range(1, len(y)):
    diff = abs(y[i] - y[i-1])
    if diff > yMax: yMax = diff
    if diff < yMin and diff > 0: yMin = diff
    yDiff.append(diff)

print(f"Max Diff in x: {xMax}")
print(f"Min Diff in x: {xMin}")
print(f"Average Diff in x: {sum(xDiff)/len(xDiff)}")
print(f"Max Diff in y: {yMax}")
print(f"Min Diff in y: {yMin}")
print(f"Average Diff in y: {sum(yDiff)/len(yDiff)}")
