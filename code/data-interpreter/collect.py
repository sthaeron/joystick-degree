import serial
import time
import sys
if sys.argv[1] == 's':
    port = '/dev/tty.usbserial-A50285BI'
elif sys.argv[1] == 'k':
    port = '/dev/ttyUSB0'
else:
    print("no correct user specified in arg[1]")
    exit(-1)
filename = sys.argv[2]
baudrate = 115200
ser = serial.Serial(port, baudrate)
print("portname:", ser.port)
outfile = open(filename, "w")
end_time = time.time() + 15
while 1:
    in_line = ser.readline().decode("ascii")
    if in_line == "End of Transmission\r\n":
        print("reached break")
        break
    outfile.write(in_line)
outfile.close()
print("Jolly good, all done!")
