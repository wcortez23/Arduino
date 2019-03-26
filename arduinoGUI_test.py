import serial
from tkinter import *


#use this as an example of controlling arduino code from tkinter gui using serial write
#must have 'gui_test1.ino' arduino file downloaded to arduino nano
#make sure the serial port and baud rates are matching!! 

arduinoData = serial.Serial('/dev/ttyUSB0', 9600)
def led_on():
    arduinoData.write(b'1') #write(b'1') as a byte, unicode strings don't work
    
def led_off():
    arduinoData.write(b'0')


root = Tk() #defining gui window (same as your other gui's)

button1 = Button(root, text='on', command= led_on)
button2 = Button(root, text='off', command= led_off)

button1.grid(row=0, column=1)   #jog up  
button2.grid(row=1, column=1) 
    
input("Press enter to exit")

root.mainloop()