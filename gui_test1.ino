//simple test that allows you to enable the on board LED of the arduino Nano 
//from the raspberry pi gui written in python3 (arduinoGUI_test.py)
//run the gui in python3 and it should toggle the led on the nano. 
//make sure the baud rates on both devices are the same!! 
//make sure the gui is talking to the nano over the right serial port!!
//current usb serial port is '/dev/ttyUSB0' 

char serialData;        //character value that is being sent from pi 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    serialData = Serial.read();   //if pi data is available, store it here
    Serial.print(serialData);     //print stored pi data 
  }

  if(serialData == '1')
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if(serialData == '0')
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
  
