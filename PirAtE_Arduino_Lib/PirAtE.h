/* ##########################################################################################
 * PirAtE.h
 * ##########################################################################################
 * Pirate implements remote Access to Experiments
 * ##########################################################################################
 * Description:
 * This libary is used in the PirAtE Project 
 * 
 * 
 * 
 * Function Overview:
 * 
 * 
 * 
 * 
 * Limitations:
 * 
 * 
 * 
 * 
 * Instructions:
 * 
 * 
 * Disclaimer Info
 * 
 * 
 * Create by Maximilian Koch
 * ################
 * V1.0 Creation by Maximilian Koch
 * 
  */

#ifndef PirAtE_H
#define PirAtE_H
#include "Arduino.h"
#include "PirAtE_Config.h"

#ifndef PirAtE_Serial_Buffer_Size
#define PirAtE_Serial_Buffer_Size 64
#endif

#define PirAtE_COMTYPE_USB 0
#define PirAtE_COMTYPE_UART 1
#define PirAtE_COMTYPE_SPI 2

#ifndef PirAtE_ComType
#define PirAte_ComType PirAtE_COMTYPE_USB
#endif



#ifndef PirAtE_SendMSGInterVal_micros
#define PirAtE_SendMSGInterVal_micros 10ul
#endif
#ifndef PirAtE_AllowedSendBlockTime_micros
#define PirAtE_AllowedSendBlockTime_micros 1000ul
#endif
#ifndef PirAtE_AllowedReceiveBlockTime_micros
#define PirAtE_AllowedReceiveBlockTime_micros 1000ul
#endif
#ifndef PirAtE_ReceiveMSGInterVal_micros
#define PirAtE_ReceiveMSGInterVal_micros 10ul
#endif

#ifndef PirAtE_Serial_Baudrate
#define PirAtE_Serial_Baudrate 115200
#endif
#ifndef PirAtE_ComType_Serialfunc
#define PirAtE_ComType_Serialfunc Serial
#endif

//Start of Serial PirAtE
#define PirAtE_SERIAL_START 'P'

//End of SerialPrint MSG
#define PirAtE_MSG_DELIMITER_LENGTH 8
byte PirAtE_MSG_DELIMITER[PirAtE_MSG_DELIMITER_LENGTH] = {0xff,'P','i','r','A','t','E','\n'};

//End of Chararray
#define PirAtE_CHARARRAY_END_LENGTH 1
#define PirAtE_CHARARRAY_END '\0'

//Request
#define PirAtE_REQUEST_DATA_LENGTH 1
#define PirAtE_REQUEST_DATA 'R'

//Debug
#define PirAtE_DEBUG_MSG_LENGTH 1
#define PirAtE_DEBUG_MSG 'M'

//Seperator
#define PirAtE_TRANSMIT_SEPERATOR_LENGTH 1
#define PirAtE_TRANSMIT_SEPERATOR '$'

//SEND MSG INFO
#define PirAtE_TRANSMIT_SENDMSG_INFO_LENGTH 1
#define PirAtE_TRANSMIT_SENDMSG_INFO 'T'

//RECIEVE MSG INFO
#define PirAtE_TRANSMIT_RECIEVEMSG_INFO_LENGTH 1
#define PirAtE_TRANSMIT_RECIEVEMSG_INFO 't'

//NO Data
#define PirAtE_NO_DATA_LENGTH 1
#define PirAtE_NO_DATA 0x29

//ID of DATA
#define PirAtE_MSG_DATAID_LENGTH 1
//Value Offset 0x30
#define PirAtE_MSG_DATAID_OFFSET ((byte) '0')


//Datatype Declaration
#define PirAtE_MSG_DATATYPE_LENGTH 1

//Int,Long (Unsigned,Signed)
#define PirAtE_MSG_DATATYPE_INT 'I'
#define PirAtE_MSG_DATATYPE_INT_LENGTH sizeof(int)
#define PirAtE_MSG_DATATYPE_UINT 'U'
#define PirAtE_MSG_DATATYPE_UINT_LENGTH sizeof(unsigned int)
#define PirAtE_MSG_DATATYPE_LONG 'L'
#define PirAtE_MSG_DATATYPE_LONG_LENGTH sizeof(long)
#define PirAtE_MSG_DATATYPE_ULONG 'u'
#define PirAtE_MSG_DATATYPE_ULONG_LENGTH sizeof(unsigned long)

//Float,Double
#define PirAtE_MSG_DATATYPE_FLOAT 'F'
#define PirAtE_MSG_DATATYPE_FLOAT_LENGTH sizeof(float)
#define PirAtE_MSG_DATATYPE_DOUBLE 'D'
#define PirAtE_MSG_DATATYPE_DOUBLE_LENGTH sizeof(double)

//Byte
#define PirAtE_MSG_DATATYPE_BYTE 'B'
#define PirAtE_MSG_DATATYPE_BYTE_LENGTH sizeof(byte)
//Word
#define PirAtE_MSG_DATATYPE_WORD 'W'
#define PirAtE_MSG_DATATYPE_WORD_LENGTH sizeof(word)

//Bool '0' or '1'
#define PirAtE_MSG_DATATYPE_BOOL 'b'
#define PirAtE_MSG_DATATYPE_BOOL_LENGTH sizeof(byte)
//Char 1 Length
#define PirAtE_MSG_DATATYPE_CHAR 'C'
#define PirAtE_MSG_DATATYPE_CHAR_LENGTH sizeof(char)
//String,CharArray
#define PirAtE_MSG_DATATYPE_STRING 'S'
#define PirAtE_MSG_DATATYPE_STRING_MAXLENGTH (PirAtE_MSG_DATA_MAXLENGTH-PirAtE_CHARARRAY_END_LENGTH)

//Offset of actual Data to DataMsg Start
#define PirAtE_MSG_DATA_OVERHEAD (PirAtE_MSG_DATAID_LENGTH + PirAtE_MSG_DATATYPE_LENGTH)
//MaxData Length
#define PirAtE_MSG_DATA_MAXLENGTH (PirAtE_Serial_Buffer_Size - PirAtE_MSG_DATA_OVERHEAD - PirAtE_MSG_DELIMITER_LENGTH)

#ifndef PirAtE_SendMsg_Amount
#define PirAtE_SendMsg_Amount 5
#endif

#define PirAtE_MSG_SENDMODE_AUTO 1
#define PirAtE_MSG_SENDMODE_MANUEL 0

byte* PirAtE_DATA_SEND_ADRESSES[PirAtE_SendMsg_Amount];
byte PirAtE_DATA_SEND_DATASIZE[PirAtE_SendMsg_Amount];
byte PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SendMsg_Amount];
byte PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_SendMsg_Amount/8 + (PirAtE_SendMsg_Amount%8?1:0)];
byte PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_SendMsg_Amount/8 + (PirAtE_SendMsg_Amount%8?1:0)];
int PirAtE_DEFINED_SEND_MSGS = 0;
int PirAtE_SEND_MSG_Index = 0;


#define PirAtE_START_COM()\
{\
  PirAtE_ComType_Serialfunc.begin(PirAtE_Serial_Baudrate);\
  delay(100);\
  PirAtE_ComType_Serialfunc.write(PirAtE_SERIAL_START);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_INT);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_INT_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_UINT);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_UINT_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_LONG);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_LONG_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_ULONG);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_ULONG_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_FLOAT);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_FLOAT_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_DOUBLE);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_DOUBLE_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_BYTE);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_BYTE_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_WORD);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_WORD_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_BOOL);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_BOOL_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_CHAR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_CHAR_LENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_STRING);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DATATYPE_STRING_MAXLENGTH);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
  delay(1000);\
}

#define PirAtE_SEND_DEBUG_MAKRO(Msg)\
{\
  PirAtE_ComType_Serialfunc.write(PirAtE_DEBUG_MSG);\
  PirAtE_ComType_Serialfunc.print(Msg);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
}

#define PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_KEY)\
{\
  PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY/8] |= 1 << (PirAtE_MSG_KEY%8);\
}

#define PirAtE_ADD_NEW_SENDMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)\
PirAtE_DEFINED_SEND_MSGS;\
{\
  PirAtE_SET_SENDMSG(PirAtE_DEFINED_SEND_MSGS, Global_VariableAdress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)\
  PirAtE_SEND_SENDMSG_INFO(PirAtE_DEFINED_SEND_MSGS, Data_Name, PirAtE_MSG_DATATYPE)\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
  PirAtE_DEFINED_SEND_MSGS++;\
}

#define PirAtE_SET_SENDMSG(PirAtE_MSG_ID, Global_VariableAdress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE)\
{\
  if(PirAtE_MSG_ID >= PirAtE_SendMsg_Amount)\
  {\
    PirAtE_SEND_DEBUG_MAKRO("ERROR: <PirAtE_SendMsg_Amount> PirAtE_SendMsg_Amount is already reached")\
  }\
  PirAtE_DATA_SEND_ADRESSES[PirAtE_MSG_ID] = (byte*) Global_VariableAdress;\
  PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_MSG_ID/8] &= ~((byte)(1 << (PirAtE_MSG_ID%8)));\
  PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_MSG_ID/8] |= PirAtE_MSG_SENDMODE << (PirAtE_MSG_ID%8);\
  PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID/8] &= ~((byte)(1 << (PirAtE_MSG_ID%8)));\
  PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID/8] |= PirAtE_MSG_SENDMODE << (PirAtE_MSG_ID%8);\
  switch (PirAtE_MSG_DATATYPE)\
  {\
    case PirAtE_MSG_DATATYPE_INT:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_UINT:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_LONG:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_ULONG:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_FLOAT:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_DOUBLE:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_BYTE:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_WORD:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_BOOL:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_CHAR:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_STRING:\
      PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING;\
      PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;\
      break;\
  }\
}

#define PirAtE_SEND_SENDMSG_INFO(PirAtE_MSG_ID, Data_Name, PirAtE_MSG_DATATYPE)\
{\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SENDMSG_INFO);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_ID + PirAtE_MSG_DATAID_OFFSET);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(Data_Name);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID]);\
}

#define PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAdress, StringBufferLength, PirAtE_MSG_SENDMODE)\
PirAtE_DEFINED_SEND_MSGS;\
{\
  PirAtE_SET_SENDMSG(PirAtE_DEFINED_SEND_MSGS, Global_VariableAdress, PirAtE_MSG_DATATYPE_STRING, PirAtE_MSG_SENDMODE)\
  if(StringBufferLength-PirAtE_CHARARRAY_END_LENGTH > PirAtE_MSG_DATATYPE_STRING_MAXLENGTH)\
  {\
    PirAtE_SEND_DEBUG_MAKRO("ERROR: %s is longer than PirAtE_MSG_DATATYPE_STRING_MAXLENGTH bytes",Data_Name)\
    PirAtE_DATA_SEND_DATASIZE[PirAtE_DEFINED_SEND_MSGS] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;\
  }\
  else\
  {\
    PirAtE_DATA_SEND_DATASIZE[PirAtE_DEFINED_SEND_MSGS] = StringBufferLength-PirAtE_CHARARRAY_END_LENGTH;\
  }\
  PirAtE_SEND_SENDMSG_INFO(PirAtE_DEFINED_SEND_MSGS, Data_Name, PirAtE_MSG_DATATYPE)\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
  PirAtE_DEFINED_SEND_MSGS++;\
}

#define PirAtE_SENDMSGS_MAKRO()\
{\
  unsigned long PirAtE_endTime = micros() + PirAtE_AllowedSendBlockTime_micros;\
  unsigned long PirAtE_nextMsgTime = micros();\
  int startIndex = PirAtE_SEND_MSG_Index;\
  int tmpStringSize = 0;\
  do\
  {\
    if(micros() > PirAtE_nextMsgTime)\
    {\
      if((PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_SEND_MSG_Index/8] & PirAtE_MSG_SENDMODE_AUTO << ((PirAtE_SEND_MSG_Index%8))||PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_SEND_MSG_Index/8] & 1 << (PirAtE_SEND_MSG_Index%8)))\
      {\
        if(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING && tmpStringSize == 0)\
        {\
            while(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index][tmpStringSize]!=PirAtE_CHARARRAY_END && tmpStringSize <= PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index])\
            {\
              tmpStringSize++;\
            }\
            if(PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]+1 == tmpStringSize)\
            {\
              PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index][tmpStringSize-1]= PirAtE_CHARARRAY_END;\
            }\
            else if(tmpStringSize == 0)\
            {\
              tmpStringSize = 1;\
              PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index][0]= PirAtE_CHARARRAY_END;\
            }\
        }\
        if(PirAtE_ComType_Serialfunc.availableForWrite() >= PirAtE_MSG_DELIMITER_LENGTH+PirAtE_MSG_DATA_OVERHEAD+PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]||(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING && PirAtE_ComType_Serialfunc.availableForWrite() >= PirAtE_MSG_DELIMITER_LENGTH+PirAtE_MSG_DATA_OVERHEAD+tmpStringSize))\
        {\
          PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index]);\
          PirAtE_ComType_Serialfunc.write(PirAtE_SEND_MSG_Index+PirAtE_MSG_DATAID_OFFSET);\
          if(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING)\
          {\
            PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index], tmpStringSize);\
            tmpStringSize = 0;\
          }\
          else\
          {\
            PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index], PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]);\            
          }\
          PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
          PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_SEND_MSG_Index/8] &= ~((byte)(1 << (PirAtE_SEND_MSG_Index%8)));\
          PirAtE_SEND_MSG_Index++;\
          PirAtE_SEND_MSG_Index%=PirAtE_SendMsg_Amount;\
          PirAtE_nextMsgTime = micros() + PirAtE_SendMSGInterVal_micros;\
        }\
      }\
      else\
      {\
        PirAtE_SEND_MSG_Index++;\
        PirAtE_SEND_MSG_Index%=PirAtE_SendMsg_Amount;\
      }\
    }\
    else\
    {\
      if(micros() < PirAtE_nextMsgTime - PirAtE_SendMSGInterVal_micros)\
      {\
        PirAtE_nextMsgTime = micros() + PirAtE_SendMSGInterVal_micros;\
      }\
    }\
  }while (micros() < PirAtE_endTime && micros() > PirAtE_endTime - PirAtE_AllowedSendBlockTime_micros && startIndex != PirAtE_SEND_MSG_Index);\
}


#ifndef PirAtE_ReceiveMsg_Amount
#define PirAtE_ReceiveMsg_Amount 5
#endif

byte* PirAtE_DATA_RECEIVE_ADRESSES[PirAtE_ReceiveMsg_Amount];
byte PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_ReceiveMsg_Amount];
byte PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_ReceiveMsg_Amount];
byte PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_ReceiveMsg_Amount/8 + (PirAtE_ReceiveMsg_Amount%8?1:0)];
byte PirAtE_DATA_RECEIVE_BUFFER[PirAtE_Serial_Buffer_Size];
int PirAtE_DEFINED_RECEIVE_MSGS = 0;


#define PirAtE_ADD_NEW_RECIEVEMSG(Data_Name, Global_VariableAdress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value)\
PirAtE_DEFINED_RECEIVE_MSGS;\
{\
  PirAtE_SET_RECEIVEMSG(PirAtE_DEFINED_RECEIVE_MSGS, Global_VariableAdress, PirAtE_MSG_DATATYPE)\
  PirAtE_SEND_RECEIVEMSG_INFO(PirAtE_DEFINED_RECEIVE_MSGS, Data_Name, PirAtE_MSG_DATATYPE)\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(Default_Value);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(Max_Value);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(Min_Value);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
  PirAtE_DEFINED_RECEIVE_MSGS++;\
}

#define PirAtE_SET_RECEIVEMSG(PirAtE_MSG_ID, Global_VariableAdress,PirAtE_MSG_DATATYPE)\
{\
  if(PirAtE_MSG_ID >= PirAtE_ReceiveMsg_Amount)\
  {\
    PirAtE_SEND_DEBUG_MAKRO("ERROR: <PirAtE_ReceiveMsg_Amount> PirAtE_ReceiveMsg_Amount is already reached")\
  }\
  PirAtE_DATA_RECEIVE_ADRESSES[PirAtE_MSG_ID] = (byte*) Global_VariableAdress;\
  PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID/8] &= ~((byte)(1 << (PirAtE_MSG_ID%8)));\
  switch (PirAtE_MSG_DATATYPE)\
  {\
    case PirAtE_MSG_DATATYPE_INT:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_UINT:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_LONG:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_ULONG:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_FLOAT:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_DOUBLE:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_BYTE:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_WORD:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_BOOL:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_CHAR:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR_LENGTH;\
      break;\
    case PirAtE_MSG_DATATYPE_STRING:\
      PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING;\
      PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;\
      break;\
  }\
}

#define PirAtE_SEND_RECEIVEMSG_INFO(PirAtE_MSG_ID, Data_Name, PirAtE_MSG_DATATYPE)\
{\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_RECIEVEMSG_INFO);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_ID + PirAtE_MSG_DATAID_OFFSET);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(Data_Name);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.write(PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID]);\
}

#define PirAtE_ADD_NEW_STRING_SENDMSG(Data_Name, Global_VariableAdress, StringBufferLength)\
PirAtE_DEFINED_RECEIVE_MSGS;\
{\
  PirAtE_SET_RECEIVEMSG(PirAtE_DEFINED_RECEIVE_MSGS, Global_VariableAdress, PirAtE_MSG_DATATYPE_STRING)\
  if(StringBufferLength-PirAtE_CHARARRAY_END_LENGTH > PirAtE_MSG_DATATYPE_STRING_MAXLENGTH)\
  {\
    PirAtE_SEND_DEBUG_MAKRO("ERROR: %s is longer than PirAtE_MSG_DATATYPE_STRING_MAXLENGTH bytes",Data_Name)\
    PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;\
  }\
  else\
  {\
    PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS] = StringBufferLength-PirAtE_CHARARRAY_END_LENGTH;\
  }\
  PirAtE_SEND_RECEIVEMSG_INFO(PirAtE_DEFINED_RECEIVE_MSGS, Data_Name, PirAtE_MSG_DATATYPE)\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print('-');\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print(PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS]);\
  PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);\
  PirAtE_ComType_Serialfunc.print('-');\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
  PirAtE_DEFINED_RECEIVE_MSGS++;\
}

#define PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_KEY)\
(PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY/8] & 1 << (PirAtE_MSG_KEY%8))

#define PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_KEY)\
{\
    PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY/8] &= ~((byte)(1 << (PirAtE_MSG_KEY%8)));\
}

#define PirAte_RECIEVEMSGS_MAKRO()\
{\
  int receiveCount = 0;\
  byte noData = 0;\
  unsigned long PirAtE_endTime = micros() + PirAtE_AllowedReceiveBlockTime_micros;\
  unsigned long PirAtE_nextMsgTime = micros();\
  do\
  {\
    if(micros() > PirAtE_nextMsgTime)\
    {\
      if(PirAtE_ComType_Serialfunc.available()>0)\
      {\
        int bytes = PirAtE_ComType_Serialfunc.readBytes(PirAtE_DATA_RECEIVE_BUFFER,PirAtE_ComType_Serialfunc.available());\
        if(PirAtE_DATA_RECEIVE_BUFFER[0] == PirAtE_NO_DATA)\
        {\
          noData=1;\
        }\
        else\
        {\
          if(bytes > 0 && PirAtE_DATA_RECEIVE_BUFFER[0] - PirAtE_MSG_DATAID_OFFSET < PirAtE_ReceiveMsg_Amount)\
          {\
            int msgID = PirAtE_DATA_RECEIVE_BUFFER[0] - PirAtE_MSG_DATAID_OFFSET;\
            if(PirAtE_DATA_RECEIVE_DATATYPE_MASK[msgID] == PirAtE_MSG_DATATYPE_STRING)\
            {\
              PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[msgID/8] |= 1 << (msgID%8);\
              receiveCount++;\
              for (int j = 0; j < bytes-PirAtE_MSG_DATAID_LENGTH;j++)\
              {\
                PirAtE_DATA_RECEIVE_ADRESSES[msgID][j] = PirAtE_DATA_RECEIVE_BUFFER[j+1];\
                if((PirAtE_DATA_RECEIVE_BUFFER[j+1] == PirAtE_CHARARRAY_END))\
                {\
                  break;\
                }\
                if( j == PirAtE_DATA_RECEIVE_DATASIZE[msgID] || j == bytes-PirAtE_MSG_DATAID_LENGTH-1)\
                {\
                  PirAtE_DATA_RECEIVE_ADRESSES[msgID][j] = PirAtE_CHARARRAY_END;\
                  break;\
                }\
              }\
            }\
            else if(bytes-PirAtE_MSG_DATAID_LENGTH == PirAtE_DATA_RECEIVE_DATASIZE[msgID])\
            {\
              PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[msgID/8] |= 1 << (msgID%8);\
              receiveCount++;\
              for (int j = 0; j < PirAtE_DATA_RECEIVE_DATASIZE[msgID];j++)\
              {\
                PirAtE_DATA_RECEIVE_ADRESSES[msgID][j] = PirAtE_DATA_RECEIVE_BUFFER[j+1];\
              }\
            }\
          }\
        }\
      }\
      while (PirAtE_ComType_Serialfunc.read()!=-1);\
      if(PirAtE_ComType_Serialfunc.availableForWrite() > PirAtE_MSG_DELIMITER_LENGTH+PirAtE_REQUEST_DATA_LENGTH)\
      {\
        PirAtE_ComType_Serialfunc.write(PirAtE_REQUEST_DATA);\
        PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
      }\
      PirAtE_nextMsgTime = micros() + PirAtE_ReceiveMSGInterVal_micros;\
    }\
    else\
    {\
      if(micros() < PirAtE_nextMsgTime - PirAtE_ReceiveMSGInterVal_micros)\
      {\
        PirAtE_nextMsgTime = micros() + PirAtE_ReceiveMSGInterVal_micros;\
      }\
    }\
  }while (micros() < PirAtE_endTime && micros() > PirAtE_endTime - PirAtE_AllowedReceiveBlockTime_micros &&receiveCount < PirAtE_ReceiveMsg_Amount && noData == 0);\
}

#endif
