// Define Input Connections
#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 9
#define CH5 10
#define CH6 11

//motor pins
#define in1A 3
#define in2A 5
#define in1B 6
#define in2B 9

//Motor direction
int MotorDirA = 1;
int MotorDirB = 1;
 
// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;
 
// Boolean to represent switch value
bool ch6Value; 

//Flags and variables for the program
int deadZone = 50;
int maxSpeed = 255;
int minSpeed = 0;

 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void forwards(int speed){
  //check for directional input

  //Start motors forwards
  analogWrite(in1A, speed);
  analogWrite(in2A, speed); 

  //Stop motors backwards
  analogWrite(in1B, 0);
  analogWrite(in2B, 0); 

  delay(1);

}

void backwards(int speed){
 
 //Map the speed to the range 0-255 for reverse
 int newSpeed = map(speed, 0, 255, 255, 0);
 Serial.println(newSpeed);
 if (newSpeed > 255) newSpeed = 255;
  analogWrite(in1B, newSpeed);
  analogWrite(in2B, newSpeed); 

 //Stop motors forwards
  analogWrite(in1A, 0);
  analogWrite(in2A, 0); 
  delay(1);

}

int directionalInputCheck(){
  
}

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  //Motor pins
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

}
void getChannelValues(){
  // Get values for each channel and store in variables
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readSwitch(CH6, false);
}
 
 void stopAllMotorOutput(){
  analogWrite(in1A, 0);
  analogWrite(in2A, 0); 
  analogWrite(in1B, 0);
  analogWrite(in2B, 0); 
  delay(1);
 }
void loop() {
  
  // Read the values of each channel
  getChannelValues();

  //Map the values to the range 0-255 for the motor outputs
  int ch3ValueMap = map(ch3Value, -100, 100, 0, 255);
  int ch1ValueMap = map(ch1Value, -100, 100, 0, 255);

 //Check to see if the stick is in the dead zone
  if(ch3Value > 0 && ch3Value > deadZone){
    forwards(ch3ValueMap);
  }
  else if(ch3Value < 0 && ch3Value < -deadZone){
    backwards(ch3ValueMap);
  }
  else{
    stopAllMotorOutput();
  }

}