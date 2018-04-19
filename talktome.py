# take things in from the command line and
# pass them through
# command to open the port should just be OPEN
# open python program - take the command line arg and take that arg to open port

import serial, time
import tkinter
import os
import sys




portname = sys.argv[1] #print(portname) #set the port name to portname
ser = serial.Serial(portname)  # open serial port
#    print(ser.name)         # check which port was really opened

while True:

    #portname = sys.argv[1] #print(portname) #set the port name to portname
    #ser = serial.Serial(portname)  # open serial port
    check = input("C: ")
    if check == "exit":
        break
    else:
        ser.write(b)
        #ser.write(check.encode())
        print (ser.readline().decode())
