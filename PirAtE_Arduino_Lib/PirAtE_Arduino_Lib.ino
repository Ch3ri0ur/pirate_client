#include "PirAtE.h"
int data = 0x30;
int data2 = 0x31;
byte data2Key;
int data3 = 0x00;
byte data3Key;
void setup() {
  // put your setup code here, to run once:
  PirAtE_START_COM()
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAdress, StringBufferLength, PirAtE_MSG_SENDMODE)
  PirAtE_ADD_NEW_SENDMSG("data1", &data, PirAtE_MSG_DATATYPE_INT, PirAtE_MSG_SENDMODE_AUTO)
  PirAtE_ADD_NEW_SENDMSG("data2", &data2, PirAtE_MSG_DATATYPE_INT, PirAtE_MSG_SENDMODE_MANUEL)
  // key = PirAtE_ADD_NEW_RECIEVEMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  PirAtE_ADD_NEW_RECIEVEMSG("data3", &data3, PirAtE_MSG_DATATYPE_INT, 0, 200, 0)
  delay(1000);
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
