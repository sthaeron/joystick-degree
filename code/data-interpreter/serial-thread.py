import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

ser = serial.Serial("/dev/tty.usbserial-A50285BI", 115200)

x_data = []
y_data = []

fig, ax = plt.subplots()
line, = ax.plot([], [], lw=2)
ax.set_xlabel('Time')
ax.set_ylabel('X ADC Value')

def update(frame):
    line.set_data(x_data, y_data)
    ax.relim()
    ax.autoscale_view()
    return line,

def read_serial():
    while True:
        line = ser.readline().strip()  # Read line from serial port
        data = line.split(b',')  # Split data by comma
        if len(data) == 2:  # Ensure correct format
            x_data.append(float(data[0]))
            y_data.append(float(data[1]))

import threading
serial_thread = threading.Thread(target=read_serial)
serial_thread.start()

# Start animation
ani = FuncAnimation(fig, update, frames=None, blit=True, interval=100)
plt.show()
