// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //
 
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
 
// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
long count;
unsigned long fuck;
float fcount;
byte s[15];
 
void setup()
{
  count=0;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  Serial.begin(115200);     //
  delay(1000); // Serial Communication is starting with 9600 of baudrate speed
}
 
void loop()
{  
  fuck = (micros());
  Serial.write((byte*)&fuck,4);
  Serial.write((byte*)&fuck,4);
  Serial.write((byte*)&fuck,4);
  Serial.write((byte*)&fuck,4);
  delay(30);
  // fuck++;
  }

 
