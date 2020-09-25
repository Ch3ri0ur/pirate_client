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
byte rstringkey = 0;

void setup()
{
  PirAtE_START_COM();
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)
  PirAtE_ADD_NEW_SENDMSG("inty", &inty, PirAtE_MSG_DATATYPE_INT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("uinty", &uinty, PirAtE_MSG_DATATYPE_UINT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("longy", &longy, PirAtE_MSG_DATATYPE_LONG, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("ulongy", &ulongy, PirAtE_MSG_DATATYPE_ULONG, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("floaty", &floaty, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("doubley", &doubley, PirAtE_MSG_DATATYPE_DOUBLE, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("bytey", &bytey, PirAtE_MSG_DATATYPE_BYTE, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("wordy", &wordy, PirAtE_MSG_DATATYPE_WORD, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("booly", &booly, PirAtE_MSG_DATATYPE_BOOL, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("chary", &chary, PirAtE_MSG_DATATYPE_CHAR, PirAtE_MSG_SENDMODE_AUTO);
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, StringBufferLength, PirAtE_MSG_SENDMODE)
  PirAtE_ADD_NEW_STRING_SENDMSG("stringy", &stringy, 32, PirAtE_MSG_SENDMODE_AUTO);

  // key = PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  PirAtE_ADD_NEW_RECEIVEMSG("rinty", &rinty, PirAtE_MSG_DATATYPE_INT,0,32767,-32768);
  PirAtE_ADD_NEW_RECEIVEMSG("ruinty", &ruinty, PirAtE_MSG_DATATYPE_UINT,1,65535,0);
  PirAtE_ADD_NEW_RECEIVEMSG("rlongy", &rlongy, PirAtE_MSG_DATATYPE_LONG,0,2147483647,-2147483647);
  PirAtE_ADD_NEW_RECEIVEMSG("rulongy", &rulongy, PirAtE_MSG_DATATYPE_ULONG,4,4294967295U,0);
  PirAtE_ADD_NEW_RECEIVEMSG("rfloaty", &rfloaty, PirAtE_MSG_DATATYPE_FLOAT,0,3.1e9,-3.1E9);
  PirAtE_ADD_NEW_RECEIVEMSG("rdoubley", &rdoubley, PirAtE_MSG_DATATYPE_DOUBLE,0,3.1e9,-3.1e9);
  PirAtE_ADD_NEW_RECEIVEMSG("rbytey", &rbytey, PirAtE_MSG_DATATYPE_BYTE,0,255,0);
  PirAtE_ADD_NEW_RECEIVEMSG("rwordy", &rwordy, PirAtE_MSG_DATATYPE_WORD,0,65535,0);
  PirAtE_ADD_NEW_RECEIVEMSG("rbooly", &rbooly, PirAtE_MSG_DATATYPE_BOOL,0,1,0);
  PirAtE_ADD_NEW_RECEIVEMSG("rchary", &rchary, PirAtE_MSG_DATATYPE_CHAR,0,255,0);
  // key = PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength)
  rstringkey = PirAtE_ADD_NEW_STRING_RECEIVEMSG("rstringy", &rstringy, 32);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT

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
  if(PirAtE_IS_NEW_DATA_AVAILABLE(rstringkey))
  {
    strcpy(stringy, rstringy);
    PirAtE_NEW_DATA_IS_READ(rstringkey)
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
