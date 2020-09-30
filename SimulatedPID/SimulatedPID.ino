#include "Arduino.h"
#include "PirAtE.h"

bool Run = false;

//PID Stuff
float PID = 0;
float P = 0;
float I = 0;
float D = 0;

float kp = 1;

float ki = 0.1;

float kd = 0.001;

float setpoint =  0;

float actualValue = 0;

float oldDif = 0;
unsigned long PIDTime = micros();
void resetPID()
{
  I= 0;
  oldDif = 0;
  PIDTime = micros();
}

float calcPID()
{
  float dif = setpoint - actualValue;
  unsigned long timedif = micros() - PIDTime;
  PIDTime = micros();
  P = kp * dif;
  I = (dif*ki/1000000) * timedif + I;
  D = ((dif - oldDif)*kd*1000000)/timedif;
  oldDif = dif;
  PID = P+I+D;
  return PID;
}


//Model Stuff
float newModelValue = 0;
byte newModelValueKey = 0;

float modelValue = 0;
float speedValue = 0;
float force = 0;
float counterForce = 100;
float forceReduction = 0.1;


unsigned long modelTime = micros();
float SimulatedModel(float controlValue)
{
  unsigned long timedif = micros() - modelTime;
  modelTime = micros();
  modelValue += (speedValue * timedif)/1000000;
  speedValue += controlValue - modelValue*forceReduction - counterForce;
  if(modelValue <0)
    modelValue = 0;
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
  
  PirAtE_ADD_NEW_SENDMSG("Actual Value", &actualValue, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("PID", &PID, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("P", &P, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("I", &I, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
  PirAtE_ADD_NEW_SENDMSG("D", &D, PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_SENDMODE_AUTO);
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
    calcPID();
  }
  else
  {
    resetPID();
  }
  actualValue = SimulatedModel(PID);
  PirAtE_SENDMSGS_MAKRO();
  PirAte_RECEIVEMSGS_MAKRO();
}
