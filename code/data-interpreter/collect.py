import serial
ser = serial.Serial('/dev/ttyUSB0', 115200)
print(ser.name)
while 1:
    print(ser.readline())
