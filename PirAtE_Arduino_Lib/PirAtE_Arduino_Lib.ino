#include "PirAtE.h"

int data = 0x30;
int data2 = 0x31;
byte data2Key;
int data3 = 0x00;
byte data3Key;
int data4 = 0x00;

void setup()
{
  // put your setup code here, to run once:
  PirAtE_START_COM();
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE)
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale)
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE, StringBufferLength)
  PirAtE_ADD_NEW_SENDMSG("data1", &data, PirAtE_MSG_DATATYPE_INT);
  data2Key = PirAtE_ADD_NEW_SENDMSG("data2", &data2, PirAtE_MSG_DATATYPE_INT, PirAte_DEFAULT_SCALE_NAME, PirAtE_MSG_SENDMODE_MANUEL);
  // key = PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  // key = PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength)
  data3Key = PirAtE_ADD_NEW_RECEIVEMSG("data3", &data3, PirAtE_MSG_DATATYPE_INT, 0, 200, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("data4", &data4, PirAtE_MSG_DATATYPE_INT, 0, 200, 0);
  delay(1000);
  PirAtE_SEND_DEBUG_MAKRO("Text");
}

void loop()
{
  // put your main code here, to run repeatedly:
  //PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_ID)
  PirAtE_IS_NEW_DATA_TO_SEND(data2Key);
  PirAtE_SENDMSGS_MAKRO();
  PirAte_RECEIVEMSGS_MAKRO();
  //if(PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_ID))
  if (PirAtE_IS_NEW_DATA_AVAILABLE(data3Key))
  {
    PirAtE_SEND_DEBUG_MAKRO("DataRead");
    data = data3;
    //PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_ID)
    PirAtE_NEW_DATA_IS_READ(data3Key);
  }
  data2 = data4;
  PirAtE_SEND_DEBUG_MAKRO("Loop");
  delay(20);
}
