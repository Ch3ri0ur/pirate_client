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
  PirAtE_START();
  // key = PirAtE_ADD_SEND_VAR(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE)
  // key = PirAtE_ADD_SEND_VAR(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale)
  // key = PirAtE_ADD_SEND_VAR(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_SEND_STRING(Data_Name, Global_VariableAddress)
  // key = PirAtE_ADD_SEND_STRING(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_SEND_STRING(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE, StringBufferLength)
  PirAtE_ADD_SEND_VAR("data1", &data, PirAtE_DATATYPE_INT);
  data2Key = PirAtE_ADD_SEND_VAR("data2", &data2, PirAtE_DATATYPE_INT, PirAte_DEFAULT_SCALE_NAME, PirAtE_MSG_SENDMODE_MANUEL);
  // key = PirAtE_ADD_RECV_VAR(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  // key = PirAtE_ADD_RECV_STRING(Data_Name, Global_VariableAddress, StringBufferLength)
  data3Key = PirAtE_ADD_RECV_VAR("data3", &data3, PirAtE_DATATYPE_INT, 0, 200, 0);
  PirAtE_ADD_RECV_VAR("data4", &data4, PirAtE_DATATYPE_INT, 0, 200, 0);
  delay(1000);
  PirAtE_DEBUG("Text");
}

void loop()
{
  // put your main code here, to run repeatedly:
  //PirAtE_SET_SEND_FLAG(PirAtE_MSG_ID)
  PirAtE_SET_SEND_FLAG(data2Key);
  PirAtE_SEND();
  PirAtE_RECV();
  //if(PirAtE_GET_RECV_FLAG(PirAtE_MSG_ID))
  if (PirAtE_GET_RECV_FLAG(data3Key))
  {
    PirAtE_DEBUG("DataRead");
    data = data3;
    //PirAtE_DATA_IS_READ(PirAtE_MSG_ID)
    PirAtE_RST_RECV_FLAG(data3Key);
  }
  data2 = data4;
  //PirAtE_DEBUG("Loop");
  delay(20);
}
