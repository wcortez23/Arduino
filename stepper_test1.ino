

// STEPPER DECLARATIONS 

#include <AccelStepper.h>
AccelStepper stepper(1, 6, 7);
const int MaxSpeed = 480;        //tune this parameter (should be around 3,840 pulses/sec) 
const int MaxAcceleration = 2800;       // tune this parameter 
const int StepsPerRevolution = 4000;       //stepper driver dip switch setting (16 microsteps = 3200pulse/rev)
const int LeadScrew = 8;        //the lead screw linear travel is 8mm/revolution
const int MoveDisp = 4000;       //use this for testing the stepper control 
double StepPerMM = StepsPerRevolution*LeadScrew;        // calculates linear displacement in steps 
int Direction; 

// STEPPER SETUP 
void setup() {
  //Serial.begin(9600);       //initialize serial monitor for data sampling
  
  stepper.setMaxSpeed(MaxSpeed);
  stepper.setAcceleration(MaxAcceleration);
  stepper.setCurrentPosition(0);
  stepper.move(MoveDisp);
  
}

//MAIN LOOP 
void loop() {
  stepper.run();        //will run stepper at specified max speed setpoint 
  stepper.moveTo(MoveDisp);       //will run stepper to specified step count 
  //Serial.println(MoveDisp);       //does not work, figure out how to count the displacement 
}
