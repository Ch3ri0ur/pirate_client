#include "PirAtE.h"

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
unsigned long duration = 0; // variable for the duration of sound wave travel
unsigned long distance = 0;  // variable for the distance measurement
unsigned long count = 0;
char stringy[53]= "qwertzu";//iopuasdfghjlkqwertzuiopuasdfghjlasdf123456789";
int value = 0;
char control = 'u';

void setup()
{
  PirAtE_START_COM();
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)
  PirAtE_ADD_NEW_SENDMSG("duration", &duration, PirAtE_MSG_DATATYPE_ULONG, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("distance", &distance, PirAtE_MSG_DATATYPE_ULONG, PirAtE_MSG_SENDMODE_AUTO);

  // key = PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  PirAtE_ADD_NEW_RECEIVEMSG("value", &value, PirAtE_MSG_DATATYPE_INT, 0, 32767, -32768);
  PirAtE_ADD_NEW_RECEIVEMSG("control", &control, PirAtE_MSG_DATATYPE_CHAR, 'u', 255, 0);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
}
void loop()
{
  delay(16);
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
  PirAtE_SENDMSGS_MAKRO();
  PirAte_RECEIVEMSGS_MAKRO();
  switch (control)
  {
  case 'd': //backward
    PirAtE_SEND_DEBUG_MAKRO("got d");
    PirAtE_SEND_DEBUG_MAKRO(duration);
    PirAtE_SEND_DEBUG_MAKRO(distance);
    PirAtE_SEND_DEBUG_MAKRO(value);
    PirAtE_SEND_DEBUG_MAKRO(control);
    control = 'u';
    // reset delay time so we;re not going to stop after 2 second
    break;
  }
}
