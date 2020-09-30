#include "Arduino.h"
#include "PirAtE.h"

bool Run = false;

//PID Stuff
float PID = 0;

float kp = 1;

float ki = 0;

float kd = 0;

float setpoint =  0;

float actualValue = 0;


float oldI= 0;
float oldDif = 0;
unsigned long PIDTime = micros();
void resetPID()
{
  oldI= 0;
  oldDif = 0;
  PIDTime = micros();
}

float calcPID()
{
  float dif = setpoint - actualValue;
  unsigned long timedif = micros() - PIDTime;
  PIDTime = micros();
  PID = kp * dif;
  oldI = (dif*ki/1000000) * timedif + oldI;
  PID += oldI;
  PID += ((dif - oldDif)*kd*1000000)/timedif;
  oldDif = dif;
  return PID;
}


//Model Stuff
float newModelValue = 0;
byte newModelValueKey = 0;

float modelMode = 0;

float modelValue = 0;
float modelValues[5] = {0,0,0,0,0};
float SimulatedModel(float controlValue)
{
  modelValue += modelValues[0];
  for(int i = 0; i < 5-1; i++)
  {
    modelValues[i]=modelValues[i+1];
  }
  modelValues[4] = controlValue;
  return modelValue;
}
void SetModelValue()
{
  modelValue = newModelValue;
}




void setup()
{
  // Starting PirAtE
  PirAtE_START_COM();
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, StringBufferLength, PirAtE_MSG_SENDMODE)
  PirAtE_ADD_NEW_SENDMSG("PID", &PID, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("Actual Value", &actualValue, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  // key = PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  // key = PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength)
  PirAtE_ADD_NEW_RECEIVEMSG("Run", &Run, PirAtE_MSG_DATATYPE_BOOL, 0, 1, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("Setpoint", &setpoint, PirAtE_MSG_DATATYPE_FLOAT, 0, 200, -200);
  PirAtE_ADD_NEW_RECEIVEMSG("kp", &kp, PirAtE_MSG_DATATYPE_FLOAT, 0, 20, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("ki", &ki, PirAtE_MSG_DATATYPE_FLOAT, 0, 20, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("kd", &kd, PirAtE_MSG_DATATYPE_FLOAT, 0, 20, 0);
  newModelValueKey = PirAtE_ADD_NEW_RECEIVEMSG("Set Model Value", &newModelValue, PirAtE_MSG_DATATYPE_FLOAT, 0, 200, -200);
  delay(1000);
  PirAtE_SEND_DEBUG_MAKRO("All Setup");
}

void loop()
{
  if(Run)
  {
    //if(PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_ID))
    if (PirAtE_IS_NEW_DATA_AVAILABLE(newModelValueKey))
    {
      PirAtE_SEND_DEBUG_MAKRO("Modelvalue Updated");
      SetModelValue();
      //PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_ID)
      PirAtE_NEW_DATA_IS_READ(newModelValueKey);
    }
    actualValue = SimulatedModel(calcPID());
  }
  PirAtE_SENDMSGS_MAKRO();
  PirAte_RECEIVEMSGS_MAKRO();
}
