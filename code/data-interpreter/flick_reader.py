import sys
import csv
from numpy import mean

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

origin = 0
origin_range = 0.4
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
for i in x_min_max_mean:
    if i == []: continue
    print("X flick #", str(k) ," min: " + str(i[0]) + ", max: " + str(i[1]) + ", mean: " + str(i[2]))
    k = k + 1
print("")
k = 0
for i in y_min_max_mean:
    if i == []: continue
    print("Y flick #", str(k) ," min: " + str(i[0]) + ", max: " + str(i[1]) + ", mean: " + str(i[2]))
    k = k + 1

