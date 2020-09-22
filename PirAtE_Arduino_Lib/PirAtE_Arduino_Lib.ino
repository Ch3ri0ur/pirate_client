#define PirAtE_SendMsg_Amount 2
#define PirAtE_SendMSGInterVal_micros 10ul
#define PirAtE_AllowedSendBlockTime_micros 200ul
#define PirAtE_ReceiveMSGInterVal_micros 100000ul
#define PirAtE_AllowedReceiveBlockTime_micros 2000000ul
#define PirAtE_ReceiveMsg_Amount 1
#include "PirAtE.h"
int data = 0x30;
int data2 = 0x31;
int data3 = 0x00;
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  PirAtE_START_COM()
  PirAtE_DEFINE_SENDMSG_MAKRO(0,PirAtE_MSG_DATATYPE_INT, &data, PirAtE_MSG_SENDMODE_AUTO)
  PirAtE_DEFINE_SENDMSG_MAKRO(1,PirAtE_MSG_DATATYPE_INT, &data2, PirAtE_MSG_SENDMODE_MANUEL)
  PirAtE_DEFINE_RECEIVEMSG_MAKRO(0,PirAtE_MSG_DATATYPE_INT, &data3)
  PirAtE_SEND_DEBUG_MAKRO("Text")
}

void loop() {
  // put your main code here, to run repeatedly:
  data+=100;
  data2+=1000;
  //PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_ID)
  PirAtE_IS_NEW_DATA_TO_SEND(1)
  PirAtE_SENDMSGS_MAKRO()
  PirAte_RECIEVEMSGS_MAKRO()
  //if(PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_ID))
  if(PirAtE_IS_NEW_DATA_AVAILABLE(0))
  {
    PirAtE_SEND_DEBUG_MAKRO("DataRead")
    data = data3;
    //PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_ID)
    PirAtE_NEW_DATA_IS_READ(0);
  }
  
  delay(1000);
}
