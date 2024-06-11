import serial
import time
filename = input('Please insert an output file name.')
port = '/dev/ttyUSB0'
baudrate = 115200
ser = serial.Serial(port, baudrate)
print(ser.name)
outfile = open(filename, "w")
end_time = time.time() + 15
while time.time() < end_time:
    outfile.write(ser.readline().decode("utf-8"))
outfile.close()
print("Jolly good, all done!")
