import serial
import time
filename = input('Please insert an output file name: \n')
port = '/dev/tty.usbserial-A50285BI'
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
