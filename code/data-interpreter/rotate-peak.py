import sys
import csv



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

x_max = -2;
x_min = 2
for i in x:
    if i > x_max: x_max = i
    if i < x_min: x_min = i

y_max = -2;
y_min = 2
for i in y:
    if i > y_max: y_max = i
    if i < y_min: y_min = i

print(f"X max: {x_max}, X min: {x_min}, Y max: {y_max}, Y min: {y_min}")
