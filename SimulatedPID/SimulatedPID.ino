#define PirAtE_SendMsg_Amount 6
#define PirAtE_ReceiveMsg_Amount 7

#include "Arduino.h"
#include "PirAtE.h"

bool Run = true;

//PID Stuff
float PID = 0;
float P = 0;
float I = 0;
float D = 0;

float kp = 0.1;

float ki = 0.5;

float kd = 0.001;

float setpoint = 100;

float actualValue = 0;

float oldDif = 0;
float maxPID = 500;
float minPID = 0;

unsigned long PIDTime = micros();
void resetPID()
{
  I = 0;
  oldDif = 0;
  PIDTime = micros();
}

float calcPID()
{
  float dif = setpoint - actualValue;
  unsigned long timedif = micros() - PIDTime;
  PIDTime = micros();
  P = kp * dif;
  I = (dif * ki / 1000000) * timedif + I;
  if (I > maxPID)
  {
    I = maxPID;
  }
  if (I < minPID)
  {
    I = minPID;
  }
  if(ki == 0)
  {
    I=0;
  }
  if (timedif == 0)
    timedif = 1;
  D = ((dif - oldDif) * kd * 1000000) / timedif;
  oldDif = dif;
  PID = P + I + D;
  if (PID > maxPID)
  {
    PID = maxPID;
  }
  if (PID < minPID)
  {
    PID = minPID;
  }
  return PID;
}

//Model Stuff
float newModelValue = 0;
byte newModelValueKey = 0;

float modelValue = 0;
float speedValue = 0;
float force = 0;
float counterForce = 100;
float friction = 0.01;
float forceReduction = 1;
float slowdown = 1;

unsigned long modelTime = micros();
float SimulatedModel(float controlValue)
{
  unsigned long timedif = (micros() - modelTime);
  modelTime = micros();
  modelValue += (speedValue * timedif) * slowdown / 1000000;
  speedValue += (controlValue - modelValue * forceReduction - counterForce - speedValue * friction) * timedif * slowdown / 1000000;
  if (modelValue < 0)
  {
    modelValue = 0;
    if(speedValue<0)
      speedValue=0;
  }
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
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE)
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale)
  // key = PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE)
  // key = PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE, StringBufferLength)
  PirAtE_ADD_NEW_SENDMSG("Actual Value", &actualValue, PirAtE_MSG_DATATYPE_FLOAT, "Height in [cm]");
  PirAtE_ADD_NEW_SENDMSG("Target Value", &setpoint, PirAtE_MSG_DATATYPE_FLOAT, "Height in [cm]");
  PirAtE_ADD_NEW_SENDMSG("PID", &PID, PirAtE_MSG_DATATYPE_FLOAT, "PID Values");
  PirAtE_ADD_NEW_SENDMSG("P", &P, PirAtE_MSG_DATATYPE_FLOAT, "PID Values");
  PirAtE_ADD_NEW_SENDMSG("I", &I, PirAtE_MSG_DATATYPE_FLOAT, "PID Values");
  PirAtE_ADD_NEW_SENDMSG("D", &D, PirAtE_MSG_DATATYPE_FLOAT, "PID Values");

  
  // key = PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)
  // key = PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength)
  PirAtE_ADD_NEW_RECEIVEMSG("Run", &Run, PirAtE_MSG_DATATYPE_BOOL, Run, 1, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("Setpoint", &setpoint, PirAtE_MSG_DATATYPE_FLOAT, setpoint, 1000, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("kp", &kp, PirAtE_MSG_DATATYPE_FLOAT, kp, 5, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("ki", &ki, PirAtE_MSG_DATATYPE_FLOAT, ki, 2, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("kd", &kd, PirAtE_MSG_DATATYPE_FLOAT, kd, 1, 0);
  newModelValueKey = PirAtE_ADD_NEW_RECEIVEMSG("Set Model Value", &newModelValue, PirAtE_MSG_DATATYPE_FLOAT, 0, 1000, 0);
  PirAtE_ADD_NEW_RECEIVEMSG("Slow down", &slowdown, PirAtE_MSG_DATATYPE_FLOAT, slowdown, 1, 0);
  delay(1000);
  PirAtE_SEND_DEBUG_MAKRO("All Setup");
}

void loop()
{
  if (Run)
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
