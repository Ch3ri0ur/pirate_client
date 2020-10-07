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

//todo pirate off
//#define PirAtE_COM_OFF
//#define PirAtE_DEBUG_DISABLED
//#define PirAtE_IS_NEW_DATA_AVAILABLE_Default_Flag_Value 1


#ifndef PirAtE_Serial_Buffer_Size
#define PirAtE_Serial_Buffer_Size 64
#endif

//Not implemented yet
#define PirAtE_COMTYPE_USB 0
#define PirAtE_COMTYPE_UART 1
#define PirAtE_COMTYPE_SPI 2

//Not implemented yet
#ifndef PirAtE_ComType
#define PirAte_ComType PirAtE_COMTYPE_USB
#endif



#ifndef PirAtE_SendMSGInterVal_micros
#define PirAtE_SendMSGInterVal_micros 10ul
#endif
#ifndef PirAtE_AllowedSendBlockTime_micros
#define PirAtE_AllowedSendBlockTime_micros 1000ul
#endif
#ifndef PirAtE_AllowActiveWaitingOnSend
#define PirAtE_AllowActiveWaitingOnSend false
#endif



#ifndef PirAtE_RequestInterVal_micros
#define PirAtE_RequestInterVal_micros 100ul
#endif

#ifndef PirAtE_AllowedReceiveBlockTime_micros
#define PirAtE_AllowedReceiveBlockTime_micros 1000ul
#endif

#ifndef PirAtE_Serial_Baudrate
#define PirAtE_Serial_Baudrate 115200
#endif
#ifndef PirAtE_ComType_Serialfunc
#define PirAtE_ComType_Serialfunc Serial
#endif

//uart 10bit per byte
#define PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS (10*1000000/PirAtE_Serial_Baudrate)

//Start of Serial PirAtE
#define PirAtE_SERIAL_START_LENGTH 8
byte PirAtE_SERIAL_START[PirAtE_SERIAL_START_LENGTH] = {0xee, 'P', 'i', 'r', 'A', 't', 'E', '\n'};

//PirAtE Datatype Info
#define PirAtE_DATATYPE_INFO 'P'

//End of SerialPrint MSG
#define PirAtE_MSG_DELIMITER_LENGTH 8
byte PirAtE_MSG_DELIMITER[PirAtE_MSG_DELIMITER_LENGTH] = {0xff, 'P', 'i', 'r', 'A', 't', 'E', '\n'};

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

//RECEIVE MSG INFO
#define PirAtE_TRANSMIT_RECEIVEMSG_INFO_LENGTH 1
#define PirAtE_TRANSMIT_RECEIVEMSG_INFO 't'

//NO Data
#define PirAtE_NO_DATA_LENGTH 1
#define PirAtE_NO_DATA 0x29

//ID of DATA
#define PirAtE_MSG_DATAID_LENGTH 1
//Value Offset 0x30
#define PirAtE_MSG_DATAID_OFFSET ((byte)'0')

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
#define PirAtE_MSG_DATATYPE_BOOL_LENGTH sizeof(bool)
//Char 1 Length
#define PirAtE_MSG_DATATYPE_CHAR 'C'
#define PirAtE_MSG_DATATYPE_CHAR_LENGTH sizeof(char)
//String,CharArray
#define PirAtE_MSG_DATATYPE_STRING 'S'
#define PirAtE_MSG_DATATYPE_STRING_MAXLENGTH (PirAtE_MSG_DATA_MAXLENGTH - PirAtE_CHARARRAY_END_LENGTH)
#define PirAtE_RECEIVE_DATATYPE_STRING_MAXLENGTH (PirAtE_Serial_Buffer_Size - PirAtE_CHARARRAY_END_LENGTH - PirAtE_MSG_DATAID_LENGTH)

#define PirAte_DEFAULT_SCALE_NAME "y"

//Offset of actual Data to DataMsg Start
#define PirAtE_MSG_DATA_OVERHEAD (PirAtE_MSG_DATAID_LENGTH + PirAtE_MSG_DATATYPE_LENGTH)
//MaxData Length
#define PirAtE_MSG_DATA_MAXLENGTH (PirAtE_Serial_Buffer_Size - PirAtE_MSG_DATA_OVERHEAD - PirAtE_MSG_DELIMITER_LENGTH)


#define PirAtE_MSG_SENDMODE_AUTO 1
#define PirAtE_MSG_SENDMODE_MANUEL 0

//todo Serial buffer size übertragen
#ifdef PirAtE_COM_OFF
  #define PirAtE_START_COM() PirAtE_ComType_Serialfunc.begin(PirAtE_Serial_Baudrate);
#else
  #define PirAtE_START_COM()                                                                      \
    {                                                                                             \
      PirAtE_ComType_Serialfunc.begin(PirAtE_Serial_Baudrate);                                    \
      delay(100);                                                                                 \
      PirAtE_ComType_Serialfunc.write(PirAtE_SERIAL_START, PirAtE_SERIAL_START_LENGTH);           \
      delay(100);                                                                                 \
      PirAtE_ComType_Serialfunc.write(PirAtE_DATATYPE_INFO);                                      \
      PirAtE_ComType_Serialfunc.print(PirAtE_Serial_Buffer_Size);                                 \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_INT, PirAtE_MSG_DATATYPE_INT_LENGTH);          \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_UINT, PirAtE_MSG_DATATYPE_UINT_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_LONG, PirAtE_MSG_DATATYPE_LONG_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_ULONG, PirAtE_MSG_DATATYPE_ULONG_LENGTH);      \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_FLOAT, PirAtE_MSG_DATATYPE_FLOAT_LENGTH);      \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_DOUBLE, PirAtE_MSG_DATATYPE_DOUBLE_LENGTH);    \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_BYTE, PirAtE_MSG_DATATYPE_BYTE_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_WORD, PirAtE_MSG_DATATYPE_WORD_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_BOOL, PirAtE_MSG_DATATYPE_BOOL_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_CHAR, PirAtE_MSG_DATATYPE_CHAR_LENGTH);        \
      PirAtE_SEND_DATATYPEINFO(PirAtE_MSG_DATATYPE_STRING, PirAtE_MSG_DATATYPE_STRING_MAXLENGTH); \
      PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);         \
      delay(1000);                                                                                \
    }

    void PirAtE_SEND_DATATYPEINFO(char datatype, int dataSize)
    {
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
      PirAtE_ComType_Serialfunc.write(datatype);
      PirAtE_ComType_Serialfunc.print(dataSize);
    }
#endif

//When Debug Disabled the Debug Send gets replaced to an empty Call
#ifdef PirAtE_DEBUG_DISABLED
  //Only used when Debug is off
  #define PirAtE_SEND_DEBUG_MAKRO(...) {}
#else
  //When Pirate COM is off only use default println for the content
  #ifdef PirAtE_COM_OFF
    //Only used when Debug active but PirAtE Protocol is off
    #define PirAtE_SEND_DEBUG_MAKRO(...)                                                    \
      {                                                                                     \
        PirAtE_ComType_Serialfunc.println(__VA_ARGS__);                                     \
      }
  #else
    //Used on Default (Pirate Protocol and Debug not Disabled)
    #define PirAtE_SEND_DEBUG_MAKRO(...)                                                    \
      {                                                                                     \
        PirAtE_ComType_Serialfunc.write(PirAtE_DEBUG_MSG);                                  \
        PirAtE_ComType_Serialfunc.print(__VA_ARGS__);                                       \
        PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH); \
      }
  #endif
#endif


//TODO Name Change to Observe Variable
#ifdef PirAtE_COM_OFF
 #define PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_KEY) {}
 #define PirAtE_ADD_NEW_SENDMSG(...) 0;
 #define PirAtE_ADD_NEW_STRING_SENDMSG(...) 0;
 #define PirAtE_SENDMSGS_MAKRO() {}
#else 
  #ifndef PirAtE_SendMsg_Amount
  #define PirAtE_SendMsg_Amount 5
  #endif
  byte *PirAtE_DATA_SEND_ADDRESSES[PirAtE_SendMsg_Amount];
  byte PirAtE_DATA_SEND_DATASIZE[PirAtE_SendMsg_Amount];
  byte PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SendMsg_Amount];
  byte PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_SendMsg_Amount / 8 + (PirAtE_SendMsg_Amount % 8 ? 1 : 0)];
  byte PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_SendMsg_Amount / 8 + (PirAtE_SendMsg_Amount % 8 ? 1 : 0)];
  int PirAtE_DEFINED_SEND_MSGS = 0;
  int PirAtE_SEND_MSG_Index = 0;

  #define PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_KEY)                                            \
    {                                                                                           \
      PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY / 8] |= 1 << (PirAtE_MSG_KEY % 8); \
    }
      
  #define PirAtE_GET_SENDMSG_MACRO(_1,_2,_3,_4,_5,NAME,...) NAME
  #define PirAtE_ADD_NEW_SENDMSG(...) PirAtE_GET_SENDMSG_MACRO(__VA_ARGS__,PirAtE_ADD_NEW_SENDMSG5, PirAtE_ADD_NEW_SENDMSG4, PirAtE_ADD_NEW_SENDMSG3, , )(__VA_ARGS__)
  
  #define PirAtE_ADD_NEW_SENDMSG3(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE)                                               \
    PirAtE_ADD_NEW_SENDMSG5(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAte_DEFAULT_SCALE_NAME, PirAtE_MSG_SENDMODE_AUTO) 
  
  #define PirAtE_ADD_NEW_SENDMSG4(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale)                     \
    PirAtE_ADD_NEW_SENDMSG5(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale, PirAtE_MSG_SENDMODE_AUTO) 
  
  #define PirAtE_ADD_NEW_SENDMSG5(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_Scale, PirAtE_MSG_SENDMODE)  \
  PirAtE_DEFINED_SEND_MSGS;                                                                                                   \
    {                                                                                                                         \
      PirAtE_SET_SENDMSG(PirAtE_DEFINED_SEND_MSGS, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE);         \
      PirAtE_SEND_SENDMSG_INFO(PirAtE_DEFINED_SEND_MSGS, Data_Name, PirAtE_MSG_DATATYPE, PirAtE_Scale);                       \
      PirAtE_DEFINED_SEND_MSGS++;                                                                                             \
    }
  
  void PirAtE_CONFIGURE_SEND(byte PirAtE_MSG_ID, byte *Global_VariableAddress, byte PirAtE_MSG_SENDMODE)
  {
    if (PirAtE_MSG_ID >= PirAtE_SendMsg_Amount)
    {
      PirAtE_SEND_DEBUG_MAKRO("ERROR: PirAtE_SendMsg_Amount is already reached")
    }
    PirAtE_DATA_SEND_ADDRESSES[PirAtE_MSG_ID] = (byte *)Global_VariableAddress;
    PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_MSG_ID / 8] &= ~((byte)(1 << (PirAtE_MSG_ID % 8)));
    PirAtE_DATA_SEND_SENDMODE_MASK[PirAtE_MSG_ID / 8] |= PirAtE_MSG_SENDMODE << (PirAtE_MSG_ID % 8);
    PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID / 8] &= ~((byte)(1 << (PirAtE_MSG_ID % 8)));
    PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID / 8] |= PirAtE_MSG_SENDMODE << (PirAtE_MSG_ID % 8);
  }
  
  #define PirAtE_SET_SENDMSG(PirAtE_MSG_ID, Global_VariableAddress, PirAtE_MSG_DATATYPE, PirAtE_MSG_SENDMODE) \
    {                                                                                                         \
      PirAtE_CONFIGURE_SEND(PirAtE_MSG_ID, (byte *)Global_VariableAddress, PirAtE_MSG_SENDMODE);              \
      switch (PirAtE_MSG_DATATYPE)                                                                            \
      {                                                                                                       \
      case PirAtE_MSG_DATATYPE_INT:                                                                           \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT;                              \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT_LENGTH;                            \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_UINT:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_LONG:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_ULONG:                                                                         \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG;                            \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG_LENGTH;                          \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_FLOAT:                                                                         \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT;                            \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT_LENGTH;                          \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_DOUBLE:                                                                        \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE;                           \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE_LENGTH;                         \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_BYTE:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_WORD:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_BOOL:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_CHAR:                                                                          \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR;                             \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR_LENGTH;                           \
        break;                                                                                                \
      case PirAtE_MSG_DATATYPE_STRING:                                                                        \
        PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING;                           \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;                      \
        break;                                                                                                \
      }                                                                                                       \
    }
  
  void PirAtE_SEND_SENDMSG_INFO(byte PirAtE_MSG_ID, char *Data_Name, byte PirAtE_MSG_DATATYPE, char *PirAtE_Scale)
  {
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SENDMSG_INFO);
    PirAtE_ComType_Serialfunc.write(PirAtE_MSG_ID + PirAtE_MSG_DATAID_OFFSET);
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
    PirAtE_ComType_Serialfunc.print(Data_Name);
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
    PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_MSG_ID]);
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
    PirAtE_ComType_Serialfunc.print(PirAtE_Scale);
    PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);
  }
  
  
  #define PirAtE_GET_STRING_SENDMSG_MACRO(_1,_2,_3,_4,NAME,...) NAME
  #define PirAtE_ADD_NEW_STRING_SENDMSG(...) PirAtE_GET_STRING_SENDMSG_MACRO(__VA_ARGS__,PirAtE_ADD_NEW_STRING_SENDMSG4, PirAtE_ADD_NEW_STRING_SENDMSG3, PirAtE_ADD_NEW_STRING_SENDMSG2, )(__VA_ARGS__)
  
  #define PirAtE_ADD_NEW_STRING_SENDMSG2(Data_Name, Global_VariableAddress)                                                           \
    PirAtE_ADD_NEW_STRING_SENDMSG4(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE_AUTO, PirAtE_MSG_DATATYPE_STRING_MAXLENGTH) 
    
  #define PirAtE_ADD_NEW_STRING_SENDMSG3(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE)                                \
    PirAtE_ADD_NEW_STRING_SENDMSG4(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE, PirAtE_MSG_DATATYPE_STRING_MAXLENGTH) 
  
  #define PirAtE_ADD_NEW_STRING_SENDMSG4(Data_Name, Global_VariableAddress, PirAtE_MSG_SENDMODE, StringBufferLength)         \
    PirAtE_DEFINED_SEND_MSGS;                                                                                                \
    {                                                                                                                        \
      PirAtE_SET_SENDMSG(PirAtE_DEFINED_SEND_MSGS, Global_VariableAddress, PirAtE_MSG_DATATYPE_STRING, PirAtE_MSG_SENDMODE); \
      if (StringBufferLength - PirAtE_CHARARRAY_END_LENGTH > PirAtE_MSG_DATATYPE_STRING_MAXLENGTH)                           \
      {                                                                                                                      \
        PirAtE_SEND_DEBUG_MAKRO("ERROR: SendString exceeds PirAtE_MSG_DATATYPE_STRING_MAXLENGTH");                           \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_DEFINED_SEND_MSGS] = PirAtE_MSG_DATATYPE_STRING_MAXLENGTH;                          \
      }                                                                                                                      \
      else                                                                                                                   \
      {                                                                                                                      \
        PirAtE_DATA_SEND_DATASIZE[PirAtE_DEFINED_SEND_MSGS] = StringBufferLength - PirAtE_CHARARRAY_END_LENGTH;              \
      }                                                                                                                      \
      PirAtE_SEND_SENDMSG_INFO(PirAtE_DEFINED_SEND_MSGS, Data_Name, PirAtE_MSG_DATATYPE_STRING, PirAte_DEFAULT_SCALE_NAME);  \
      PirAtE_DEFINED_SEND_MSGS++;                                                                                            \
    }
  
  
  unsigned long PirAtE_Time_of_next_Msg_Cycle = 0;
  
  //todo multi msg in 1 send with on delimiter
  #define PirAtE_SENDMODEOFMSGISAUTO(msgID) (PirAtE_DATA_SEND_SENDMODE_MASK[msgID / 8] & PirAtE_MSG_SENDMODE_AUTO << (msgID % 8))
  #define PirAtE_ISNEWDATATOSEND(msgID) (PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[msgID / 8] & 1 << (msgID % 8))
  #define PirAtE_REMOVENEWDATATOSEND(msgID) PirAtE_DATA_SEND_NEWDATA_AVAILABLE_MASK[msgID / 8] &= ~((byte)(1 << (msgID % 8)));

  #define PirAtE_SENDMSGS_MAKRO()                                                                                                                                              \
    {                                                                                                                                                                          \
      unsigned long PirAtE_endTime = micros() + PirAtE_AllowedSendBlockTime_micros;                                                                                            \
      int startIndex = PirAtE_SEND_MSG_Index;                                                                                                                                  \
      byte msgSend = 0;                                                                                                                                                        \
      int tmpMsgSize = 0;                                                                                                                                                      \
      do                                                                                                                                                                       \
      {                                                                                                                                                                        \
        if (PirAtE_SEND_MSG_Index != 0 || micros() > PirAtE_Time_of_next_Msg_Cycle)                                                                                            \
        {                                                                                                                                                                      \
          if (PirAtE_SENDMODEOFMSGISAUTO(PirAtE_SEND_MSG_Index)|| PirAtE_ISNEWDATATOSEND(PirAtE_SEND_MSG_Index))                                                               \
          {                                                                                                                                                                    \
            if(tmpMsgSize == 0)                                                                                                                                                \
            {                                                                                                                                                                  \
              if (PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING)                                                                         \
              {                                                                                                                                                                \
                while (PirAtE_DATA_SEND_ADDRESSES[PirAtE_SEND_MSG_Index][tmpMsgSize] != PirAtE_CHARARRAY_END && tmpMsgSize <= PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index])\
                {                                                                                                                                                              \
                  tmpMsgSize++;                                                                                                                                                \
                }                                                                                                                                                              \
                if (PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index] + 1 == tmpMsgSize)                                                                                        \
                {                                                                                                                                                              \
                  PirAtE_DATA_SEND_ADDRESSES[PirAtE_SEND_MSG_Index][tmpMsgSize - 1] = PirAtE_CHARARRAY_END;                                                                    \
                }                                                                                                                                                              \
                else if (tmpMsgSize == 0)                                                                                                                                      \
                {                                                                                                                                                              \
                  tmpMsgSize = 1;                                                                                                                                              \
                  PirAtE_DATA_SEND_ADDRESSES[PirAtE_SEND_MSG_Index][0] = PirAtE_CHARARRAY_END;                                                                                 \
                }                                                                                                                                                              \
              }                                                                                                                                                                \
              else                                                                                                                                                             \
              {                                                                                                                                                                \
                tmpMsgSize = PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index];                                                                                                 \
              }                                                                                                                                                                \
            }                                                                                                                                                                  \
            if (PirAtE_ComType_Serialfunc.availableForWrite() >= PirAtE_MSG_DELIMITER_LENGTH + PirAtE_MSG_DATA_OVERHEAD + tmpMsgSize)                                          \
            {                                                                                                                                                                  \
              PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index]);                                                                          \
              PirAtE_ComType_Serialfunc.write(PirAtE_SEND_MSG_Index + PirAtE_MSG_DATAID_OFFSET);                                                                               \
              PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_ADDRESSES[PirAtE_SEND_MSG_Index], tmpMsgSize);                                                                  \
              tmpMsgSize = 0;                                                                                                                                                  \
              msgSend++;                                                                                                                                                       \
              PirAtE_REMOVENEWDATATOSEND(PirAtE_SEND_MSG_Index);                                                                                                               \
              PirAtE_SEND_MSG_Index++;                                                                                                                                         \
              PirAtE_SEND_MSG_Index %= PirAtE_DEFINED_SEND_MSGS;                                                                                                               \
              PirAtE_Time_of_next_Msg_Cycle = micros() + PirAtE_SendMSGInterVal_micros;                                                                                        \
            }                                                                                                                                                                  \
            else                                                                                                                                                               \
            {                                                                                                                                                                  \
              {                                                                                                                                                                \
              if(!PirAtE_AllowActiveWaitingOnSend)                                                                                                                             \
                break;                                                                                                                                                         \
              }                                                                                                                                                                \
            }                                                                                                                                                                  \
          }                                                                                                                                                                    \
          else                                                                                                                                                                 \
          {                                                                                                                                                                    \
            PirAtE_SEND_MSG_Index++;                                                                                                                                           \
            PirAtE_SEND_MSG_Index %= PirAtE_DEFINED_SEND_MSGS;                                                                                                                 \
          }                                                                                                                                                                    \
        }                                                                                                                                                                      \
        else                                                                                                                                                                   \
        {                                                                                                                                                                      \
          if (PirAtE_SEND_MSG_Index != 0 && micros() < PirAtE_Time_of_next_Msg_Cycle - PirAtE_SendMSGInterVal_micros)                                                          \
          {                                                                                                                                                                    \
            PirAtE_Time_of_next_Msg_Cycle = micros() + PirAtE_SendMSGInterVal_micros;                                                                                          \
          }                                                                                                                                                                    \
          break;                                                                                                                                                               \
        }                                                                                                                                                                      \
      } while (micros() < PirAtE_endTime && micros() > PirAtE_endTime - PirAtE_AllowedSendBlockTime_micros && startIndex != PirAtE_SEND_MSG_Index);                            \
      if(msgSend>0)                                                                                                                                                            \
      {                                                                                                                                                                        \
        PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);                                                                                    \
      }                                                                                                                                                                        \
    }
#endif

//TODO Name Change to Control Variable
#ifdef PirAtE_COM_OFF
  #define PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value) 0;
  #define PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength) 0;
  #ifndef PirAtE_IS_NEW_DATA_AVAILABLE_Default_Flag_Value
  #define PirAtE_IS_NEW_DATA_AVAILABLE_Default_Flag_Value 0
  #endif
  #define PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_KEY) PirAtE_IS_NEW_DATA_AVAILABLE_Default_Flag_Value
  #define PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_KEY) {}
  #define PirAte_RECEIVEMSGS_MAKRO() {}
#else
  
  #ifndef PirAtE_ReceiveMsg_Amount
  #define PirAtE_ReceiveMsg_Amount 5
  #endif
  
  byte *PirAtE_DATA_RECEIVE_ADDRESSES[PirAtE_ReceiveMsg_Amount];
  byte PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_ReceiveMsg_Amount];
  byte PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_ReceiveMsg_Amount];
  byte PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_ReceiveMsg_Amount / 8 + (PirAtE_ReceiveMsg_Amount % 8 ? 1 : 0)];
  int PirAtE_DEFINED_RECEIVE_MSGS = 0;
  
  #define PirAtE_ADD_NEW_RECEIVEMSG(Data_Name, Global_VariableAddress, PirAtE_MSG_DATATYPE, Default_Value, Max_Value, Min_Value) \
    PirAtE_DEFINED_RECEIVE_MSGS;                                                                                                 \
    {                                                                                                                            \
      PirAtE_SET_RECEIVEMSG(PirAtE_DEFINED_RECEIVE_MSGS, Global_VariableAddress, PirAtE_MSG_DATATYPE);                           \
      PirAtE_SEND_RECEIVEMSG_INFO(PirAtE_DEFINED_RECEIVE_MSGS, Data_Name, PirAtE_MSG_DATATYPE);                                  \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                \
      PirAtE_ComType_Serialfunc.print(Default_Value);                                                                            \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                \
      PirAtE_ComType_Serialfunc.print(Max_Value);                                                                                \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                \
      PirAtE_ComType_Serialfunc.print(Min_Value);                                                                                \
      PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);                                        \
      PirAtE_DEFINED_RECEIVE_MSGS++;                                                                                             \
    }
  
  void PirAtE_CONFIGURE_RECEIVE(byte PirAtE_MSG_ID, byte *Global_VariableAddress)
  {
    if (PirAtE_MSG_ID >= PirAtE_ReceiveMsg_Amount)
    {
      PirAtE_SEND_DEBUG_MAKRO("ERROR: PirAtE_ReceiveMsg_Amount is already reached");
    }
    PirAtE_DATA_RECEIVE_ADDRESSES[PirAtE_MSG_ID] = (byte *)Global_VariableAddress;
    PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_ID / 8] &= ~((byte)(1 << (PirAtE_MSG_ID % 8)));
  }
  
  #define PirAtE_SET_RECEIVEMSG(PirAtE_MSG_ID, Global_VariableAddress, PirAtE_MSG_DATATYPE)     \
    {                                                                                           \
      PirAtE_CONFIGURE_RECEIVE(PirAtE_MSG_ID, (byte *)Global_VariableAddress);                  \
      switch (PirAtE_MSG_DATATYPE)                                                              \
      {                                                                                         \
      case PirAtE_MSG_DATATYPE_INT:                                                             \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT;             \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_INT_LENGTH;           \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_UINT:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_UINT_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_LONG:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_LONG_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_ULONG:                                                           \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG;           \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_ULONG_LENGTH;         \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_FLOAT:                                                           \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT;           \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_FLOAT_LENGTH;         \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_DOUBLE:                                                          \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE;          \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_DOUBLE_LENGTH;        \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_BYTE:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BYTE_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_WORD:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_WORD_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_BOOL:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_BOOL_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_CHAR:                                                            \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR;            \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_CHAR_LENGTH;          \
        break;                                                                                  \
      case PirAtE_MSG_DATATYPE_STRING:                                                          \
        PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID] = PirAtE_MSG_DATATYPE_STRING;          \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_MSG_ID] = PirAtE_RECEIVE_DATATYPE_STRING_MAXLENGTH; \
        break;                                                                                  \
      }                                                                                         \
    }
  
  void PirAtE_SEND_RECEIVEMSG_INFO(byte PirAtE_MSG_ID, char *Data_Name, byte PirAtE_MSG_DATATYPE)
  {
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_RECEIVEMSG_INFO);
    PirAtE_ComType_Serialfunc.write(PirAtE_MSG_ID + PirAtE_MSG_DATAID_OFFSET);
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
    PirAtE_ComType_Serialfunc.print(Data_Name);
    PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);
    PirAtE_ComType_Serialfunc.write(PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_MSG_ID]);
  }
  
  #define PirAtE_ADD_NEW_STRING_RECEIVEMSG(Data_Name, Global_VariableAddress, StringBufferLength)                                                                                                             \
    PirAtE_DEFINED_RECEIVE_MSGS;                                                                                                                                                                              \
    {                                                                                                                                                                                                         \
      PirAtE_SET_RECEIVEMSG(PirAtE_DEFINED_RECEIVE_MSGS, Global_VariableAddress, PirAtE_MSG_DATATYPE_STRING)                                                                                                  \
      if (StringBufferLength - PirAtE_CHARARRAY_END_LENGTH > PirAtE_RECEIVE_DATATYPE_STRING_MAXLENGTH)                                                                                                        \
      {                                                                                                                                                                                                       \
        PirAtE_SEND_DEBUG_MAKRO("ERROR: ReceiveString exceeds PirAtE_RECEIVE_DATATYPE_STRING_MAXLENGTH");                                                                                                     \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS] = PirAtE_RECEIVE_DATATYPE_STRING_MAXLENGTH;                                                                                                 \
      }                                                                                                                                                                                                       \
      else                                                                                                                                                                                                    \
      {                                                                                                                                                                                                       \
        PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS] = StringBufferLength - PirAtE_CHARARRAY_END_LENGTH;                                                                                         \
      }                                                                                                                                                                                                       \
      PirAtE_SEND_RECEIVEMSG_INFO(PirAtE_DEFINED_RECEIVE_MSGS, Data_Name, PirAtE_MSG_DATATYPE_STRING);                                                                                                        \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                                                                                             \
      PirAtE_ComType_Serialfunc.print(0);                                                                                                                                                                     \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                                                                                             \
      PirAtE_ComType_Serialfunc.print(PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_DEFINED_RECEIVE_MSGS]);                                                                                                             \
      PirAtE_ComType_Serialfunc.write(PirAtE_TRANSMIT_SEPERATOR);                                                                                                                                             \
      PirAtE_ComType_Serialfunc.print(0);                                                                                                                                                                     \
      PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);                                                                                                                     \
      PirAtE_DEFINED_RECEIVE_MSGS++;                                                                                                                                                                          \
    }
  
  #define PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_KEY) \
    (PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY / 8] & 1 << (PirAtE_MSG_KEY % 8))
  
  #define PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_KEY)                                                             \
    {                                                                                                         \
      PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[PirAtE_MSG_KEY / 8] &= ~((byte)(1 << (PirAtE_MSG_KEY % 8))); \
    }
  
  unsigned long PirAtE_Time_of_next_Request = 0;
  unsigned long PirAtE_ReceiveTimeout = 0;
  byte PirAtE_IncompleteData = 0;
  byte PirAte_NoData = 0;
  
  #define PirAte_RECEIVEMSGS_MAKRO()                                                                                                                                                                    \
    {                                                                                                                                                                                                   \
      unsigned long PirAtE_endTime = micros() + PirAtE_AllowedReceiveBlockTime_micros;                                                                                                                  \
      int receivedByte = -1;                                                                                                                                                                            \
      int receivedBytesCount = 0;                                                                                                                                                                       \
      int msgID = -1;                                                                                                                                                                                   \
      while (PirAtE_ComType_Serialfunc.available() > 0 && micros() < PirAtE_endTime && micros() > PirAtE_endTime - PirAtE_AllowedReceiveBlockTime_micros)                                               \
      {                                                                                                                                                                                                 \
        msgID = PirAtE_ComType_Serialfunc.peek();                                                                                                                                                       \
        if (msgID == PirAtE_NO_DATA)                                                                                                                                                                    \
        {                                                                                                                                                                                               \
          PirAtE_ComType_Serialfunc.read();                                                                                                                                                             \
          PirAte_NoData = 1;                                                                                                                                                                            \
          PirAtE_Time_of_next_Request = micros() + PirAtE_RequestInterVal_micros;                                                                                                                       \
        }                                                                                                                                                                                               \
        else                                                                                                                                                                                            \
        {                                                                                                                                                                                               \
          msgID -= PirAtE_MSG_DATAID_OFFSET;                                                                                                                                                            \
          PirAte_NoData = 0;                                                                                                                                                                            \
          receivedBytesCount = 0;                                                                                                                                                                       \
          if (msgID >= 0 && msgID < PirAtE_DEFINED_RECEIVE_MSGS)                                                                                                                                        \
          {                                                                                                                                                                                             \
            if (PirAtE_DATA_RECEIVE_DATATYPE_MASK[msgID] == PirAtE_MSG_DATATYPE_STRING)                                                                                                                 \
            {                                                                                                                                                                                           \
              PirAtE_ComType_Serialfunc.read();                                                                                                                                                         \
              while (receivedBytesCount <= PirAtE_DATA_RECEIVE_DATASIZE[msgID])                                                                                                                         \
              {                                                                                                                                                                                         \
                PirAtE_ReceiveTimeout = micros() + PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS;                                                                                                           \
                do                                                                                                                                                                                      \
                {                                                                                                                                                                                       \
                  receivedByte = PirAtE_ComType_Serialfunc.read();                                                                                                                                      \
                  if (micros() < PirAtE_ReceiveTimeout - PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS)                                                                                                     \
                  {                                                                                                                                                                                     \
                    PirAtE_ReceiveTimeout = micros() + PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS;                                                                                                       \
                  }                                                                                                                                                                                     \
                } while (receivedByte == -1 && micros() < PirAtE_ReceiveTimeout);                                                                                                                       \
                if (receivedByte == -1)                                                                                                                                                                 \
                {                                                                                                                                                                                       \
                  PirAtE_DATA_RECEIVE_ADDRESSES[msgID][receivedBytesCount] = PirAtE_CHARARRAY_END;                                                                                                      \
                  break;                                                                                                                                                                                \
                }                                                                                                                                                                                       \
                else                                                                                                                                                                                    \
                {                                                                                                                                                                                       \
                  PirAtE_DATA_RECEIVE_ADDRESSES[msgID][receivedBytesCount] = (byte)receivedByte;                                                                                                        \
                  receivedBytesCount++;                                                                                                                                                                 \
                  if ((byte)receivedByte == PirAtE_CHARARRAY_END)                                                                                                                                       \
                  {                                                                                                                                                                                     \
                    PirAtE_ReceiveTimeout = micros() + PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS;                                                                                                       \
                    break;                                                                                                                                                                              \
                  }                                                                                                                                                                                     \
                  else if (receivedBytesCount == PirAtE_DATA_RECEIVE_DATASIZE[msgID] + PirAtE_CHARARRAY_END_LENGTH)                                                                                     \
                  {                                                                                                                                                                                     \
                    PirAtE_DATA_RECEIVE_ADDRESSES[msgID][receivedBytesCount - 1] = PirAtE_CHARARRAY_END;                                                                                                \
                    while (PirAtE_ComType_Serialfunc.read() != -1)                                                                                                                                      \
                      ;                                                                                                                                                                                 \
                    break;                                                                                                                                                                              \
                  }                                                                                                                                                                                     \
                }                                                                                                                                                                                       \
              }                                                                                                                                                                                         \
            }                                                                                                                                                                                           \
            else                                                                                                                                                                                        \
            {                                                                                                                                                                                           \
              if (PirAtE_DATA_RECEIVE_DATASIZE[msgID] + PirAtE_MSG_DATAID_LENGTH <= PirAtE_ComType_Serialfunc.available())                                                                              \
              {                                                                                                                                                                                         \
                PirAtE_ComType_Serialfunc.read();                                                                                                                                                       \
                receivedBytesCount = PirAtE_ComType_Serialfunc.readBytes(PirAtE_DATA_RECEIVE_ADDRESSES[msgID], PirAtE_DATA_RECEIVE_DATASIZE[msgID]);                                                    \
                PirAtE_IncompleteData = 0;                                                                                                                                                              \
                PirAtE_ReceiveTimeout = micros() + PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS;                                                                                                           \
              }                                                                                                                                                                                         \
              else                                                                                                                                                                                      \
              {                                                                                                                                                                                         \
                if(PirAtE_IncompleteData)                                                                                                                                                               \
                {                                                                                                                                                                                       \
                  if(micros() > PirAtE_ReceiveTimeout)                                                                                                                                                  \
                  {                                                                                                                                                                                     \
                    while (PirAtE_ComType_Serialfunc.read() != -1)                                                                                                                                      \
                    ;                                                                                                                                                                                   \
                    PirAtE_IncompleteData = 0;                                                                                                                                                          \
                  }                                                                                                                                                                                     \
                  else if(micros() < PirAtE_ReceiveTimeout - PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS * PirAtE_DATA_RECEIVE_DATASIZE[msgID])                                                           \
                  {                                                                                                                                                                                     \
                    PirAtE_ReceiveTimeout = micros() + (PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS * PirAtE_DATA_RECEIVE_DATASIZE[msgID]);                                                               \
                  }                                                                                                                                                                                     \
                }                                                                                                                                                                                       \
                else                                                                                                                                                                                    \
                {                                                                                                                                                                                       \
                  PirAtE_ReceiveTimeout = micros() + PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS * PirAtE_DATA_RECEIVE_DATASIZE[msgID];                                                                   \
                  PirAtE_IncompleteData = 1;                                                                                                                                                            \
                }                                                                                                                                                                                       \
              }                                                                                                                                                                                         \
            }                                                                                                                                                                                           \
          }                                                                                                                                                                                             \
          else                                                                                                                                                                                          \
          {                                                                                                                                                                                             \
            while (PirAtE_ComType_Serialfunc.read() != -1)                                                                                                                                              \
              ;                                                                                                                                                                                         \
          }                                                                                                                                                                                             \
          if (receivedBytesCount > 0)                                                                                                                                                                   \
          {                                                                                                                                                                                             \
            PirAtE_DATA_RECEIVE_NEWDATA_AVAILABLE_MASK[msgID / 8] |= 1 << (msgID % 8);                                                                                                                  \
          }                                                                                                                                                                                             \
        }                                                                                                                                                                                               \
      }                                                                                                                                                                                                 \
      if(!PirAtE_IncompleteData)                                                                                                                                                                        \
      {                                                                                                                                                                                                 \
        if (((!PirAte_NoData &&  micros() > PirAtE_ReceiveTimeout) || micros() > PirAtE_Time_of_next_Request)&& PirAtE_ComType_Serialfunc.available() == 0)                                             \
        {                                                                                                                                                                                               \
          if (PirAtE_ComType_Serialfunc.availableForWrite() > PirAtE_MSG_DELIMITER_LENGTH + PirAtE_REQUEST_DATA_LENGTH)                                                                                 \
          {                                                                                                                                                                                             \
            PirAtE_ComType_Serialfunc.write(PirAtE_REQUEST_DATA);                                                                                                                                       \
            PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);                                                                                                         \
            PirAtE_Time_of_next_Request = micros() + PirAtE_RequestInterVal_micros;                                                                                                                     \
            PirAte_NoData = 1;                                                                                                                                                                          \
          }                                                                                                                                                                                             \
        }                                                                                                                                                                                               \
        else                                                                                                                                                                                            \
        {                                                                                                                                                                                               \
          if (micros() < PirAtE_Time_of_next_Request - PirAtE_RequestInterVal_micros)                                                                                                                   \
          {                                                                                                                                                                                             \
            PirAtE_Time_of_next_Request = micros() + PirAtE_RequestInterVal_micros;                                                                                                                     \
          }                                                                                                                                                                                             \
          if(micros() < PirAtE_ReceiveTimeout - PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS)                                                                                                              \
          {                                                                                                                                                                                             \
            PirAtE_ReceiveTimeout = micros() + (PirAtE_RECEIVE_PAYLOADBYTE_TIMEOUT_MICROS);                                                                                                             \
          }                                                                                                                                                                                             \
        }                                                                                                                                                                                               \
      }                                                                                                                                                                                                 \
    }
  #endif
#endif
