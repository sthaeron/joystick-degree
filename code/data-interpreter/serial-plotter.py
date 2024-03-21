# serial-plotter.py

import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

x_data = []
y_data = []

# plot animation function
def animate(i, x_data, y_data, ser):
    #ser.reset_input_buffer()
    line = ser.readline().strip()
    data = line.split(b',')

    x = float(data[0])
    y = float(data[1])

    x_data.append(x)
    y_data.append(y)

    x_data = x_data[-100:]
    y_data = y_data[-100:]

    ax.clear()
    ax.plot(x_data, y_data)

    # Format plot
    ax.set_ylim([0, 5000])
    ax.set_title("Live Reading Joystick")
    ax.set_ylabel("X ADC Value")

fig, ax = plt.subplots()

ser = serial.Serial("/dev/tty.usbserial-A50285BI", 115200)  # change COM# if necessary
#time.sleep(2)
print(ser.name)

# run the animation and show the figure
ani = animation.FuncAnimation(
    fig, animate, frames=100, fargs=(x_data, y_data, ser), interval=100
)
plt.show()

# after the window is closed, close the serial line
ser.close()
print("Serial line closed")
