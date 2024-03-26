# serial-plotter.py

import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def animate(i, xs:list, ys:list, zs:list, ser):
    ser.reset_input_buffer()
    ser.readline()
    line = ser.readline().strip()
    data = line.split(b',')

    xs.append(float(data[0]))
    ys.append(float(data[1]))
    zs.append(float(data[2]))

    xs = xs[-100:]
    ys = ys[-100:]
    zs = zs[-100:]

    ax1.clear()
    ax1.plot(xs, ys)

    ax1.set_ylim([-200, 4200])
    ax1.set_xlabel("Time (ms)")
    ax1.set_ylabel("X ADC Value")

    ax2.clear()
    ax2.plot(xs, zs)

    ax2.set_ylim([-200, 4200])
    ax2.set_xlabel("Time (ms)")
    ax2.set_ylabel("Y ADC Value")

# constant variables
port = "/dev/tty.usbserial-A50285BI"
baudrate = 115200
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)


# Configure serial port
ser = serial.Serial(port, baudrate)
time.sleep(2)
print(f"Reading serial port: {ser.name}\n")

# Run animation and show plot
ani = animation.FuncAnimation(
    fig, animate, frames=100, fargs=([], [], [], ser), interval=100
)
plt.show()

ser.close()
print("Serial port closed")
