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
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print(distance);
  Serial.print(",");
  Serial.print(distance/2);  
  Serial.print(",");
  Serial.print(distance+5);
  Serial.print(",");
  Serial.println(distance-5);
  delay(100);
  char control = 0;
  while(Serial.available() > 0){
    String input = Serial.readStringUntil('T');
    Serial.println("I" + input);
    if(input == "foo"){
      //do stuff...
    }
  }
  if (Serial.available())
  {
    control = Serial.read(); //reads serial input
  }
   switch (control)
  {
    case '0':     //moves forward
      Serial.println(F("Forward"));
      // reset delay time so we;re not going to stop after 2 second
      break;
    case '1':      //left
      Serial.println(F("Left"));
      // reset delay time so we;re not going to stop after 2 second
      break;
    case '2':      //right
      Serial.println(F("Right"));
      // reset delay time so we;re not going to stop after 2 second
      break;
    case '3':     //backward
      Serial.println(F("Backward"));
      // reset delay time so we;re not going to stop after 2 second
      break;
  }    
}
