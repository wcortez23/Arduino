//batch test to see if the motor and load cell will overload the nano
//make an if statement to be toggled by serial read from GUI. 
//when serial data is read from pi, run the loop. 
//should:step motor and collect step counts, log force data and plot both to serial monitor. 
//verify both by touching load cell along the way to see how the data fluctuates. 
//CURRENT STATE: WHEN PLOTTING DATA TO SERIAL MONITOR, STEPPER IS VERY SLOW
//NEED TO FIGURE OUT WHY THIS IS HAPPENING.. 

#include <HX711.h>
#include <AccelStepper.h>


//______________serial data from python3 gui_____________
char serialData;        //character value that is being sent from pi 
 
//______________stepper declarations____________________
AccelStepper stepper(1, 6, 7);                    //(1 stepper, step di-pin 6, direction di-pin 7) 
const int MaxSpeed = 480;                         //tune this parameter (should be around 3,840 pulses/sec) 
const int MaxAcceleration = 2800;                 //tune this parameter 
const int StepsPerRevolution = 4000;              //stepper driver dip switch setting (16 microsteps = 3200pulse/rev)
const int LeadScrew = 8;                          //the lead screw linear travel is 8mm/revolution
const int MoveDisp = 4000;                        //use this for testing the stepper control 
double StepPerMM = StepsPerRevolution*LeadScrew;  //calculates linear displacement in steps 
int Direction;                                    //direction (+) = up, direction (-)= down 
long Disp = 0;                                   //displacement measured in mm 
float Time = 0;                                   //clock time in millis(); start when collecting data

//______________load cell declarations____________________
#define calibration_factor -215                   //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3                                   //di-pin 3 in arduino nano
#define CLK  4                                    //di-pin 4 in arduino nano
float Load = 0;                                   //sensed load in grams
float MaxLoad = 1000;                             //load threshold in grams  
HX711 scale;

//___________________setup (runs once)____________________
void setup() 
{
  //SERIAL SETUP 
  Serial.begin(9600);
  
  //STEPPER SETUP 
  stepper.setMaxSpeed(MaxSpeed);
  stepper.setAcceleration(MaxAcceleration);
  stepper.setCurrentPosition(0);
  stepper.move(MoveDisp);

  //LOAD CELL SETUP
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}

//____________________main loop (runs continuously)________

void loop() 
{
  if (Serial.available() > 0)           //if gui serial data is available, enter main loop! 
  {
    serialData = Serial.read();         //store serial read into serialDtata register
    Serial.println(serialData);         //probably don't need this? just returns value
  }
  
   //________________________jogUP___________________________
   //using the moveTo() function takes you back to a predetermined spot and is not
   //allowing the jog function to move freely, basically goes back to where it left off from.
   //figure out how to set current position to zero so that it actually does 10mm
   
  if(serialData == '3')               //if serialData = '2', step in (+z) axis  
  {
    stepper.moveTo(MoveDisp);          //drive motor in 10mm increments
    stepper.run();
    if(serialData != '3')
    {
      stepper.setCurrentPosition(0);    //if you stop reading data, reset position, stop
      Stop();
    }
  }
    //_______________________jogDOWN___________________________
    //figure out the clockwise/ccw rotation so that it is consistent and doesn't 
    //just go off of the previous state it was in. maybe setCurrentPosition(0) before
    //having it run off in a direction would give it a defined starting point... 
    
  if(serialData == '2')               //if serialData = '2', step in (+z) axis  
  {
    stepper.moveTo(-MoveDisp);           //drive motor in 10mm increments
    stepper.run();
    if(serialData == false)
    {
      stepper.setCurrentPosition(0);    //if you stop reading data, reset position, stop
      Stop();
    }
  }
  
  //_________________________testRUN________________________
  
  if(serialData == '1')                 //if serialData = '1', that mean's we're in business!! 
  {
    collectData();                      //start polling time, load, disp
    dataPRINT();                        //plot to serial monitor (problematic!!)
    stepper.moveTo(MoveDisp);           //currently only goes 10mm for testing 
    stepper.run();
    testRUN();
  }
  
  //_________________________STOP____________________________
  
  if(serialData == '0')                 //if serialData = '0', still good, but we bailed!  
  {
    Stop();                             //hit the brakes and stop the motor
  }

}

//_____________________variable defenitions________________

int Stop()
{
  stepper.stop();                       //send a stop command to stepper motor 
  Serial.println("STOPPING ON PURPOSE");
  serialData = false; 
}

int testRUN()                    //comparator worked in a while loop, try again!  
{
  if (Load >= MaxLoad)           //this comparison is slow as shit! bogs down the stepper movement. 
  {
    //dataPRINT();
    stepper.move(MoveDisp * -Direction);
    stepper.run(); 
  }
}

int collectData()                //collect load and displacement data here 
{
  Load = scale.get_units();      //collect scaled load value, might need to condition this
  Disp = stepper.currentPosition() / StepPerMM;     //count steps and divide by steps per mm (NOT SURE IF THIS IS SLOWING US DOWN)
  Time = millis();                ///see if you need to collect time data here?? millis()?? 
}

int dataPRINT()                 //print load and displacement data to serial (add delay)
{
  Serial.print(Time);           //print milliseconds since program start  
  Serial.print(',');
  Serial.print(Load, 6);       //print load with 6 sig figs 
  Serial.print(',');
  Serial.print(Disp, 3);       //print displacement with 3 sig figs
  Serial.println();

  //some thoughts on serial communication... while one is talking to the serial monitor
  //the other cannot write to it as well.. therefore the comms needs to be timed somehow.
  //add delay after data is printed?, make gui delay even longer (2-3 seconds)
  //gui should wait for data to finish writing before reading and 
  //attempting to write data to a csv file.. we'll test this here... 
}                      



//_______________________END OF PROGRAM_________________________
