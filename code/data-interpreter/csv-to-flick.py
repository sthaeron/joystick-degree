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

in_flick = False
x_flick_list = [[]]
y_flick_list = [[]]

flick_count = 0

origin = 0
origin_range = 0.3

for i in range(len(time)): 
    if (x[i] > (origin + origin_range) or x[i] < (origin - origin_range)) or (y[i] > (origin + origin_range) or y[i] < (origin - origin_range)):
        if in_flick == False:
            in_flick = True
            x_flick_list.append([])
            y_flick_list.append([])
            flick_count += 1
    elif in_flick == True:
        in_flick = False

    if in_flick == True:
        x_flick_list[flick_count-1].append(x[i])
        y_flick_list[flick_count-1].append(y[i])

for i in range(flick_count):
    print(f"Flick {i+1}: x: {sum(x_flick_list[i])/len(x_flick_list[i])} y: {sum(y_flick_list[i])/len(y_flick_list[i])}")
