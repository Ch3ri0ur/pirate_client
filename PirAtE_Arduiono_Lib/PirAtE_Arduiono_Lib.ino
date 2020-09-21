#include "PirAtE.h"
#define PirAtE_SendMsg_Amount 2
#define PirAtE_SendMSGInterVal_micros 10ul
#define PirAtE_AllowedSendBlockTime_micros 200ul
#define PirAtE_ReceiveMSGInterVal_micros 10ul
#define PirAtE_AllowedReceiveBlockTime_micros 200ul
#define PirAtE_ReceiveMsg_Amount 1
int data = 0x30;
int data2 = 0x31;
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  PirAtE_START_COM()
  PirAtE_DEFINESENDMSG_MAKRO(0,PirAtE_MSG_DATATYPE_INT, &data)
  PirAtE_DEFINESENDMSG_MAKRO(1,PirAtE_MSG_DATATYPE_INT, &data2)
  PirAtE_DEFINERECEIVEMSG_MAKRO(0,PirAtE_MSG_DATATYPE_INT, &data2)
}

void loop() {
  // put your main code here, to run repeatedly:
  data+=100;
  data2+=1000;
  PirAtE_SENDMSGS_MAKRO()
  PirAte_RECIEVEMSGS_MAKRO()
  delay(1000);
}
