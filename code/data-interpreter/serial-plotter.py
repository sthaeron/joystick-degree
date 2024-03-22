# serial-plotter.py

import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def animate(i, xs:list, ys:list, ser):
    ser.reset_input_buffer()
    ser.readline()
    line = ser.readline().strip()
    data = line.split(b',')

    xs.append(float(data[0]))
    ys.append(float(data[1]))

    xs = xs[-100:]
    ys = ys[-100:]

    ax.clear()
    ax.plot(xs, ys)

    ax.set_ylim([-200, 4200])
    ax.set_title("Live Serial Plot")
    ax.set_xlabel("Time (ms)")
    ax.set_ylabel("X ADC Value")

# constant variables
port = "/dev/tty.usbserial-A50285BI"
baudrate = 115200
fig, ax = plt.subplots()

# Configure serial port
ser = serial.Serial(port, baudrate)
time.sleep(2)
print(f"Reading serial port: {ser.name}\n")

# Run animation and show plot
ani = animation.FuncAnimation(
    fig, animate, frames=100, fargs=([], [], ser), interval=100
)
plt.show()

ser.close()
print("Serial port closed")
