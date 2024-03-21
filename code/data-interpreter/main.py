import serial
import matplotlib.pyplot as plt

x_data = []
y_data = []
baudrate = 115200

#     ser = serial.Serial(port, baudrate)
#     while True:
# def create_plot():
#     plt.plot(x_data, y_data)
#     plt.xlabel("Time (ms)")
#     plt.ylabel("ADC Value")
#     plt.title("Live Serial Plot")
#     plt.grid(True)
#     plt.pause(0.001)
#
# def update_plot():
#     plt.cla()
#     plt.plot(x_data, y_data)
#     plt.pause(0.01)
#
# def read_serial(port):
#         try:
#             if ser.in_waiting > 0:
#                 line = ser.readline().strip()
#                 if line:
#                     data = line.split(b',')
#                     x = float(data[0])
#                     y = float(data[1])
#                     x_data.append(x)
#                     y_data.append(y)
#                     drawnow(update_plot)
#         except KeyboardInterrupt:
#                 ser.close()
#                 break

def simple_read(port):
    ser = serial.Serial(port, baudrate)
    plt.close("all")
    plt.figure()
    plt.ion()
    plt.show()
    while 1:
        try:
            ser.reset_input_buffer()
            ser.readline()
            line = ser.readline().strip()
            data = line.split(b',')
            x = float(data[0])
            y = float(data[1])
            x_data.append(x)
            y_data.append(y)
            plt.cla()
            plt.plot(x_data, y_data)
            plt.pause(0.00000000000001)
        except KeyboardInterrupt:
            ser.close()
            break


if __name__ == "__main__":
    simple_read("/dev/tty.usbserial-A50285BI")
