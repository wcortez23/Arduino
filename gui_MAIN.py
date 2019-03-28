from tkinter import *
import serial

root = Tk()   #creates root window header for gui
root.geometry('350x200')    #horizontal x vertical box dimensions

####################ARDUINO SERIAL COMMUNICATIONS###############
#DATA TO ARDUINO SERIAL PORT (SERIAL PORT, BAUD RATE)
arduinoData = serial.Serial('/dev/ttyUSB0', 9600) 

########################################## FUNCTION DEFENITIONS ###########################################
force_entry = StringVar           #user input to gui -> write out to arduino! 
velocity_entry = StringVar        #not sure what to do with these guys

def jogUP():                      #write to arduino 
    arduinoData.write(b'3')       #write(b'1') as a byte, unicode strings don't work
    
def jogDOWN():                    #write to arduino 
    arduinoData.write(b'2')
    
def tare():                       #write this to the arduino, NOT DONE -->write to variable
    print("load cell has been set to zero load")
    
def testRUN():                    #write to arduino 
    arduinoData.write(b'1')       #write(b'1') as a byte
    
def testSTOP():                   #write to arduino
    arduinoData.write(b'0')       #write(b'1') as a byte, should stop motor 

def maxforce():                   #write to arduino, NOT DONE --> write to variable
    global force_entry
    force = force_entry.get()     #write this value to a variable??
    print(force, "Newton threshold value set")
    
def velocity():                   #how to determine this? pick from list? should be very restricted
    global velocity_entry
    speed = velocity_entry.get()
    print(speed, "Speed setpoint set")
    
def load():                       #read this value from serial data output from arduino??? 
    '''poll load cell data here
        read it out to the gui from arduino via serial arduinoData.read()???
        plot it to csv file
        compare it to maxforce() user input
        have this poll in parallel thread?'''
    

########################################### GUI DEFENITIONS ################################################

#WIDGET INITIALIZING
header = Label(root, text="Force/Displacement Test Bench", bg="black", fg="white")
button1 = Button(root, text = "Jog Up (+Z)", fg="black", command=jogUP)     #creates button widgets and defines frame location, text, color, functon
button2 = Button(root, text = "Jog Down (-Z)", fg="black", command=jogDOWN)
button3 = Button(root, text = "Tare", fg="blue", command=tare)
button4 = Button(root, text = "Run Test", fg="green", command=testRUN)
button5 = Button(root, text = "Stop Test", fg="red", command=testSTOP)
force_label = Label(root, text = "Force (N)")    
force_entry = Entry(root, width=5)   
force_button = Button(root, text="Enter Force", command=maxforce)
speed_label = Label(root, text = "MM/sec")
speed_entry = Entry(root, width=5)
speed_button = Button(root, text="Enter Speed ", command=velocity)

#WIDGET LAYOUT 
header.grid(row=0, columnspan=4)
button1.grid(row=2, sticky=W)   #jog up  
button2.grid(row=3, sticky=W)   #jog down
button3.grid(row=2, column=2, sticky=W)    #tare
button4.grid(row=5, column=0, sticky=W)    #run test
button5.grid(row=6, column=0, sticky=W)    #stop test
force_label.grid(row=2, column=4, sticky=W)   
force_entry.grid(row=2, column=4, sticky=E)     
force_button.grid(row=3, column=4, sticky=E)
speed_label.grid(row=6, column=4, sticky=W)
speed_entry.grid(row=6, column=4, sticky=E)
speed_button.grid(row=7, column=4, sticky=E) 


root.mainloop()
 