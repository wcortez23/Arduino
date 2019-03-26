
//Force/Displacement Apparatus  
//The rasberry pi (master) will call this script which operates on an arduino nano (slave), using A tkinter gui written in python3. 


#include <HX711.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <sample_cfg.h>       //nanpy firmware????? confirm this 


//___________________________________STEPPER DECLARATIONS____________________      
AccelStepper stepper(1, 6, 7);                    //(1 stepper, step di-pin 6, direction di-pin 7) 
const int MaxSpeed = 480;                         //tune this parameter (should be around 3,840 pulses/sec) 
const int MaxAcceleration = 2800;                 //tune this parameter 
const int StepsPerRevolution = 4000;              //stepper driver dip switch setting (16 microsteps = 3200pulse/rev)
const int LeadScrew = 8;                          //the lead screw linear travel is 8mm/revolution
const int MoveDisp = 4000;                        //use this for testing the stepper control 
double StepPerMM = StepsPerRevolution*Lead
Screw;  //calculates linear displacement in steps 
int Direction;                                    //direction (+) = up, direction (-)= down 


//___________________________________LOAD CELL DECLARATIONS__________________
#include "HX711.h"                                //Do I need to call this again??
#define calibration_factor -215                   //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3                                   //di-pin 3 in arduino nano
#define CLK  4                                    //di-pin 4 in arduino nano 
HX711 scale;



//___________________________________SERIAL DECLARATIONS ____________________




//____________________________________GUI DECLARATIONS _______________________





//____________________________________EXTRA DECLARATIONS______________________





void setup() {

  //SERIAL COMMS SETUP 
  //enter baud rate that the GUI will be using 


  //STEPPER MOTOR SETUP 
  stepper.setMaxSpeed(MaxSpeed);
  stepper.setAcceleration(MaxAcceleration);
  stepper.setCurrentPosition(0);
  stepper.move(MoveDisp);


  //LOAD CELL SETUP 
  scale.begin(DOUT, CLK);                 //begins reading data and clock signals
  scale.set_scale(calibration_factor);    //uses calibration_factor to set scale value
  scale.tare();                           //tares the load reading 

}

void loop()     //_________________________MAIN LOOP______________________________
{
  delay();                //base this time off of how long it takes the gui to send a serial read
                          // figure out how to read a serial input from the gui here 
  if (some serial input) //assuming this is how to do a serial.read() from gui?????????
  {
    while (jogUP == 1)    //_______________GUI JOG UP_________________________
    {
      CollectData();
      if(TopLimitSw > 0)
      {
        serial.println(" Top limit reached!")
        Stop();
        break();
      }
      Status = "Up";
      stepper.move(MoveDisp); 
      stepper.run();
      CollectData();
      
      if(jogUP == 0)
      
      {
        break;   
      }
    }

    while (jogDOWN == 1)    //____________GUI JOG DOWN_______________________
    {
      CollectData();
      
      if (Load >= maxforce)
      {
        Stop();
        break();
      }
      
      Status = "Down";
      stepper.move(-MoveDisp);
      stepper.run();
      CollectData;
      
      if(jogDOWN == 0)
      {
        break;
      }
    }

    if (tare == 1)  //___________________GUI TARE____________________________
    {
      tare();       //not sure how this one will work out 
    }

    if (Home == 1)  //___________________GUI HOME (DOES NOT EXIST)___________ 
    {
      Status = "Home";  //not sure how this one will work out 
      GoHome();
    }

    if (testRUN == 1) //_________________GUI BEGIN TEST______________________ 
    {
      Status = "Testing";
      testRUN();
    }
    
  }

}     //end of main loop 


  
//______________________________________FUNCTION ASSIGNMENTS____________________

int get_gui_data();       //not done with this. determine how to do serial.read 
{

}

int send_gui_data();      //not done with this. determine how to do serial.write 
{
  //write load data that can be displayed on gui interface. To be determined 
}


int CollectData();
{
  Load = //determine where the processed data in grams will be stored, pull from there
  Disp = stepper.currentPosition() / StepPerMM;       //converts steps into mm of travel 
  TopLimSwitchState = analogRead(TopLimSw);           //you haven't programmed this yet 
}

int PrintSerial();        //figure out how to print data to .txt or .csv file!!! 
{
Serial.print(millis());       //print milliseconds since program started
Serial.print(',');            //print comma between next column 
Serial.print(Load, 6);        //print load as a float with 6 sig-figs
Serial.print(',');            //print comma between next column 
Serial.print(Disp, 6);        //print displacement as float with 6 sig-figs 
//Serial.print(',');
//Serial.println(Status);
}

int Stop();
{
  stepper.stop();
  Status = "Stopped";
  delay(1000)           //stalling delay of 1 second after stepper has stopped
}

int GoHome();           //decide if you need this. It's a "would be nice"
{
  //would require setting top limit switch as a "zero point" but the limit switch being enabled
  //will need to be bypassed for the stepper to begin moving again. To be determined 
}

int testRUN();
{ //determine if this needs a different name than the gui function... 

  Direction = -1
  while(true)
  {
    CollectData();
    if(TopLimSw > 0)    //still don't know what to do with these...
    {

    }
    
    if (BottLimSw >0)   //still don't know what to do with these...
    {
      Serial.print("Bottom limit reached, ABORT!!");
      Stop();
      break; 
    }
    
    if (Load >= maxforce)
    {
      Serial.print("Max Load Reached!")
      delay();      //user specified "dwell time"???? ------> follow up!! 
    }

    if (Stop() == true)     //will this even work?? how will I bail if asked to?? 
    {
      Stop();
      break();
    }

    CollectData();    //here's the interesting part... 
    PrintSerial();    //prints collected data to serial port, from here we either write that to a file 
                      //using a python script or we have the arduino do it... decisions... 
    stepper.move(MoveDisp * Direction);     //tells the stepper to move up in the positive direction, 
                                            //do we want it to go home?? otherwise it will only go as far
                                            //as "MoveDisp" is set to, which is one rev...
    stepper.run();
  }

}
