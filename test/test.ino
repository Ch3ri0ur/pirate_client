#include "PirAtE.h"

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#define PirAtE_SendMsg_Amount 11
#define PirAtE_ReceiveMsg_Amount 11

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int value;
char control;
int inty;
unsigned int uinty;
long longy;
unsigned long ulongy;
float floaty;
double doubley;
//byte bytey;
// word wordy;
// byte booly;
char chary;
char stringy[15] = "arduino\0";
int rvalue;
char rcontrol;
int rinty;
unsigned int ruinty;
long rlongy;
unsigned long rulongy;
float rfloaty;
double rdoubley;
//byte rbytey;
// word rwordy;
// byte rbooly;
char rchary;
char rstringy[15] = "returnoino\0";

void setup()
{
  PirAtE_DEFINE_SENDMSG_MAKRO(0, PirAtE_MSG_DATATYPE_INT, &inty);
  PirAtE_DEFINE_SENDMSG_MAKRO(1, PirAtE_MSG_DATATYPE_UINT, &uinty);
  PirAtE_DEFINE_SENDMSG_MAKRO(2, PirAtE_MSG_DATATYPE_LONG, &longy);
  PirAtE_DEFINE_SENDMSG_MAKRO(3, PirAtE_MSG_DATATYPE_ULONG, &ulongy);
  PirAtE_DEFINE_SENDMSG_MAKRO(4, PirAtE_MSG_DATATYPE_FLOAT, &floaty);
  PirAtE_DEFINE_SENDMSG_MAKRO(5, PirAtE_MSG_DATATYPE_DOUBLE, &doubley);
  // PirAtE_DEFINE_SENDMSG_MAKRO(6, PirAtE_MSG_DATATYPE_BYTE, &bytey);
  // PirAtE_DEFINE_SENDMSG_MAKRO(7, PirAtE_MSG_DATATYPE_WORD, &wordy);
  // PirAtE_DEFINE_SENDMSG_MAKRO(8, PirAtE_MSG_DATATYPE_BOOL, &booly);
  PirAtE_DEFINE_SENDMSG_MAKRO(9, PirAtE_MSG_DATATYPE_CHAR, &chary);
  PirAtE_DEFINE_SENDMSG_MAKRO(10, PirAtE_MSG_DATATYPE_STRING, &stringy);

  PirAtE_DEFINE_RECEIVEMSG_MAKRO(0, PirAtE_MSG_DATATYPE_INT, &rinty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(1, PirAtE_MSG_DATATYPE_UINT, &ruinty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(2, PirAtE_MSG_DATATYPE_LONG, &rlongy);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(3, PirAtE_MSG_DATATYPE_ULONG, &rulongy);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(4, PirAtE_MSG_DATATYPE_FLOAT, &rfloaty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(5, PirAtE_MSG_DATATYPE_DOUBLE, &rdoubley);
  // PirAtE_DEFINE_RECEIVEMSG_MAKRO(6, PirAtE_MSG_DATATYPE_BYTE, &rbytey);
  // PirAtE_DEFINE_RECEIVEMSG_MAKRO(7, PirAtE_MSG_DATATYPE_WORD, &rwordy);
  // PirAtE_DEFINE_RECEIVEMSG_MAKRO(8, PirAtE_MSG_DATATYPE_BOOL, &rbooly);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(9, PirAtE_MSG_DATATYPE_CHAR, &rchary);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(10, PirAtE_MSG_DATATYPE_STRING, &rstringy);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  PirAtE_START_COM();
}
void loop()
{
  delay(100);
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

  inty = distance;
  uinty++;
  longy = duration;
  ulongy++;
  floaty++;
  doubley++;
  bytey++;
  wordy++;
  booly++;
  chary++;
  if (stringy[0] == "a")
  {
    stringy = "pirate";
  }
  else
  {
    stringy = "arduino";
  }
  PirAtE_SEND_DEBUG_MAKRO("Sending now");
  PirAtE_SENDMSGS_MAKRO();
  PirAtE_SEND_DEBUG_MAKRO("Recieving now");
  PirAte_RECIEVEMSGS_MAKRO();
  PirAtE_SEND_DEBUG_MAKRO("Sending test debug message now");
  PirAtE_SEND_DEBUG_MAKRO(inty);
  switch (control)
  {
  case 'w': //moves forward
    PirAtE_SEND_DEBUG_MAKRO("got w");
    // reset delay time so we;re not going to stop after 2 second
    break;
  case 'a': //left;
    PirAtE_SEND_DEBUG_MAKRO("got a");
    // reset delay time so we;re not going to stop after 2 second
    break;
  case 's': //right
    PirAtE_SEND_DEBUG_MAKRO("got s");
    // reset delay time so we;re not going to stop after 2 second
    break;
  case 'd': //backward
    PirAtE_SEND_DEBUG_MAKRO("got d");
    // reset delay time so we;re not going to stop after 2 second
    break;
  }
}

// #define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
// #define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// // defines variables
// long duration; // variable for the duration of sound wave travel
// int distance;  // variable for the distance measurement
// long count;
// unsigned long fuck;
// float fcount;
// byte s[15];

// void setup()
// {
//   count=0;
//   pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
//   pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
//   Serial.begin(115200);     //
//   delay(1000); // Serial Communication is starting with 9600 of baudrate speed
// }

// void loop()
// {
//   fuck = (micros());
//   Serial.write((byte*)&fuck,4);
//   Serial.write((byte*)&fuck,4);
//   Serial.write((byte*)&fuck,4);
//   Serial.write((byte*)&fuck,4);
//   delay(30);
//   // fuck++;
//   }
