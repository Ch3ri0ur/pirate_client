#include "PirAtE.h"

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration = 0; // variable for the duration of sound wave travel
int distance = 0;  // variable for the distance measurement
int value = 0;
char control = 'u';
int inty = 0;
unsigned int uinty = 0;
long longy = 0;
unsigned long ulongy = 0;
float floaty = 0.5;
double doubley = 0.5;
byte bytey = 0x00;
word wordy = 0;
byte booly = 0;
char chary = 'f';
char stringy[64] = "arduino";
int rvalue;
char rcontrol;
int rinty;
unsigned int ruinty;
long rlongy;
unsigned long rulongy;
float rfloaty;
double rdoubley;
byte rbytey;
word rwordy;
byte rbooly;
char rchary;
char rstringy[64] = "returnoino";

void setup()
{
  PirAtE_DEFINE_SENDMSG_MAKRO(0, PirAtE_MSG_DATATYPE_INT, &inty, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(1, PirAtE_MSG_DATATYPE_UINT, &uinty, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(2, PirAtE_MSG_DATATYPE_LONG, &longy, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(3, PirAtE_MSG_DATATYPE_ULONG, &ulongy, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(4, PirAtE_MSG_DATATYPE_FLOAT, &floaty, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(5, PirAtE_MSG_DATATYPE_DOUBLE, &doubley, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(6, PirAtE_MSG_DATATYPE_BYTE, &bytey, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(7, PirAtE_MSG_DATATYPE_WORD, &wordy, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(8, PirAtE_MSG_DATATYPE_BOOL, &booly, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(9, PirAtE_MSG_DATATYPE_CHAR, &chary, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_DEFINE_SENDMSG_MAKRO(10, PirAtE_MSG_DATATYPE_STRING, &stringy, PirAtE_MSG_SENDMODE_AUTO);

  PirAtE_DEFINE_RECEIVEMSG_MAKRO(0, PirAtE_MSG_DATATYPE_INT, &rinty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(1, PirAtE_MSG_DATATYPE_UINT, &ruinty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(2, PirAtE_MSG_DATATYPE_LONG, &rlongy);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(3, PirAtE_MSG_DATATYPE_ULONG, &rulongy);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(4, PirAtE_MSG_DATATYPE_FLOAT, &rfloaty);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(5, PirAtE_MSG_DATATYPE_DOUBLE, &rdoubley);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(6, PirAtE_MSG_DATATYPE_BYTE, &rbytey);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(7, PirAtE_MSG_DATATYPE_WORD, &rwordy);
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(8, PirAtE_MSG_DATATYPE_BOOL, &rbooly);
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
  if(PirAtE_IS_NEW_DATA_AVAILABLE(10))
  {
    strcpy(stringy, rstringy);
    PirAtE_NEW_DATA_IS_READ(10)
    PirAtE_SEND_DEBUG_MAKRO("New Data 0");
  }
  inty = rinty;
  uinty = ruinty;
  longy = rlongy;
  ulongy = rulongy;
  floaty = rfloaty;
  doubley = rdoubley;
  bytey = rbytey;
  wordy = rwordy;
  booly = rbooly;
  chary = rchary;
  
  PirAtE_SEND_DEBUG_MAKRO("Sending now");
  delay(100);
  PirAtE_SENDMSGS_MAKRO();
  PirAtE_SEND_DEBUG_MAKRO("Recieving now");
  delay(100);
  PirAte_RECIEVEMSGS_MAKRO();
  PirAtE_SEND_DEBUG_MAKRO("Sending test debug message now");
  delay(100);
  PirAtE_SEND_DEBUG_MAKRO(inty);
  delay(100);
  PirAtE_SEND_DEBUG_MAKRO(rinty);
  PirAtE_SEND_DEBUG_MAKRO(ruinty);
  PirAtE_SEND_DEBUG_MAKRO(rlongy);
  PirAtE_SEND_DEBUG_MAKRO(rulongy);
  PirAtE_SEND_DEBUG_MAKRO(rfloaty);
  PirAtE_SEND_DEBUG_MAKRO(rdoubley);
  PirAtE_SEND_DEBUG_MAKRO(rbytey);
  PirAtE_SEND_DEBUG_MAKRO(rwordy);
  PirAtE_SEND_DEBUG_MAKRO(rbooly);
  PirAtE_SEND_DEBUG_MAKRO(rchary);
  PirAtE_SEND_DEBUG_MAKRO(rstringy);
}
//   switch (control)
//   {
//   case 'w': //moves forward
//     PirAtE_SEND_DEBUG_MAKRO("got w");
//     // reset delay time so we;re not going to stop after 2 second
//     break;
//   case 'a': //left;
//     PirAtE_SEND_DEBUG_MAKRO("got a");
//     // reset delay time so we;re not going to stop after 2 second
//     break;
//   case 's': //right
//     PirAtE_SEND_DEBUG_MAKRO("got s");
//     // reset delay time so we;re not going to stop after 2 second
//     break;
//   case 'd': //backward
//     PirAtE_SEND_DEBUG_MAKRO("got d");
//     // reset delay time so we;re not going to stop after 2 second
//     break;
//   }

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
