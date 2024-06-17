import sys
import csv
from numpy import mean
print("Quick how to use:")
print("argv[1] is csv to read")
print("argv[2] is origin for x (like 0), and argv[3] is origin for y (like)")
print("example execute: python3.11 flick_reader.py dreamcast_flick_1.csv 0 0")
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

origin = float(sys.argv[2])
origin_range = 0.3
in_flick = 0
flick_list_list = []
x_flick_list = [[]]
y_flick_list = [[]]
k = 0
for i in x:
    if i < origin - origin_range:
        if in_flick == 0:
            in_flick = 1
            x_flick_list.append([])
        x_flick_list[k].append(i)
    elif i > origin + origin_range:
        if in_flick == 0:
            in_flick = 1
            x_flick_list.append([])
        x_flick_list[k].append(i)
    elif in_flick == 1:
        in_flick = 0
        k = k + 1
k = 0
if sys.argv[3]:
    origin = float(sys.argv[3])
for i in y:
    if i < origin - origin_range:
        if in_flick == 0:
            in_flick = 1
            y_flick_list.append([])
        y_flick_list[k].append(i)
    elif i > origin + origin_range:
        if in_flick == 0:
            in_flick = 1
            y_flick_list.append([])
        y_flick_list[k].append(i)
    elif in_flick == 1:
        in_flick = 0
        k = k + 1


k = 0
min([], default="EMPTY")
x_min_max_mean = [[]]
for i in x_flick_list:
    if i == []:
        continue
    x_min_max_mean[k].append(min(i))
    x_min_max_mean[k].append(max(i))
    x_min_max_mean[k].append(mean(i))
    k = k + 1
    x_min_max_mean.append([])
y_min_max_mean = [[]]
k = 0
for i in y_flick_list:
    if i == []:
        continue
    y_min_max_mean[k].append(min(i))
    y_min_max_mean[k].append(max(i))
    y_min_max_mean[k].append(mean(i))
    k = k + 1
    y_min_max_mean.append([])
k = 0

print("Flick trial x, X min, X max, X mean, Y min, Y max, Y mean")
print("Flick #1, -, -, -, ", y_min_max_mean[0][0], ", ", y_min_max_mean[0][1], ", ", y_min_max_mean[0][2])
print("Flick #2, ", x_min_max_mean[0][0], ", ", x_min_max_mean[0][1], ", ", x_min_max_mean[1][2], ", ", y_min_max_mean[1][0], ", ", y_min_max_mean[1][1], ", ", y_min_max_mean[1][2])
print("Flick #3, ", x_min_max_mean[1][0], ", ", x_min_max_mean[1][1], ", ", x_min_max_mean[1][2], ", ", '-', ", ", '-', ", ", '-')
print("Flick #4, ", x_min_max_mean[2][0], ", ", x_min_max_mean[2][1], ", ", x_min_max_mean[2][2], ", ", y_min_max_mean[2][0], ", ", y_min_max_mean[2][1], ", ", y_min_max_mean[2][2])
print("Flick #5, -, -, -, ", y_min_max_mean[3][0], ", ", y_min_max_mean[3][1], ", ", y_min_max_mean[3][2])
print("Flick #6, ", x_min_max_mean[3][0], ", ", x_min_max_mean[3][1], ", ", x_min_max_mean[3][2], ", ", y_min_max_mean[4][0], ", ", y_min_max_mean[4][1], ", ", y_min_max_mean[4][2])
print("Flick #7, ", x_min_max_mean[4][0], ", ", x_min_max_mean[4][1], ", ", x_min_max_mean[4][2], ", ", '-', ", ", '-', ", ", '-')
print("Flick #8, ", x_min_max_mean[5][0], ", ", x_min_max_mean[5][1], ", ", x_min_max_mean[5][2], ", ", y_min_max_mean[5][0], ", ", y_min_max_mean[5][1], ", ", y_min_max_mean[5][2])
#
# for i in x_min_max_mean:
#     if i == []: continue
#     print("X flick #", str(k) ," min: " + str(i[0]) + ", max: " + str(i[1]) + ", mean: " + str(i[2]))
#     k = k + 1
# print("")
# k = 0
# for i in y_min_max_mean:
#     if i == []: continue
#     print("Y flick #", str(k) ," min: " + str(i[0]) + ", max: " + str(i[1]) + ", mean: " + str(i[2]))
#     k = k + 1
#
