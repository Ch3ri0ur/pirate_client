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

//End of SerialPrint MSG
#define PirAtE_MSG_DELIMITER_LENGTH 8
byte PirAtE_MSG_DELIMITER[PirAtE_MSG_DELIMITER_LENGTH] = {0xff,'P','i','r','A','t','E','\n'};

//End of Chararray
#define PirAtE_CHARARRAY_END_LENGTH 1
#define PirAtE_CHARARRAY_END '\0'

//Request
#define PirAtE_REQUEST_DATA_LENGTH 1
#define PirAtE_REQUEST_DATA 0x29

//Debug
#define PirAtE_DEBUG_MSG_LENGTH 1
#define PirAtE_DEBUG_MSG 0x28

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

byte* PirAtE_DATA_SEND_ADRESSES[PirAtE_SendMsg_Amount];
byte PirAtE_DATA_SEND_DATASIZE[PirAtE_SendMsg_Amount];
byte PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SendMsg_Amount];
int PirAtE_SEND_MSG_Index = 0;


#define PirAtE_START_COM()\
{\
  PirAtE_ComType_Serialfunc.begin(PirAtE_Serial_Baudrate);\
}

#define PirAtE_SEND_DEBUG_MAKRO(Msg)\
{\
  PirAtE_ComType_Serialfunc.write(PirAtE_DEBUG_MSG);\
  PirAtE_ComType_Serialfunc.print(Msg);\
  PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
}
  
#define PirAtE_DEFINE_SENDMSG_MAKRO(PirAtE_MSG_ID,PirAtE_MSG_DATATYPE, Global_VariableAdress)\
{\
  PirAtE_DATA_SEND_ADRESSES[PirAtE_MSG_ID] = (byte*) Global_VariableAdress;\
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

#define PirAtE_SENDMSGS_MAKRO()\
{\
  unsigned long PirAtE_endTime = micros() + PirAtE_AllowedSendBlockTime_micros;\
  unsigned long PirAtE_nextMsgTime = micros();\
  int startIndex = PirAtE_SEND_MSG_Index;\
  do\
  {\
    if(micros() > PirAtE_nextMsgTime)\
    {\
      if(PirAtE_ComType_Serialfunc.availableForWrite() > PirAtE_MSG_DELIMITER_LENGTH+PirAtE_MSG_DATA_OVERHEAD+PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index])\
      {\
        PirAtE_ComType_Serialfunc.write(PirAtE_SEND_MSG_Index+PirAtE_MSG_DATAID_OFFSET);\
        PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index]);\
        if(PirAtE_DATA_SEND_DATATYPE_MASK[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING)\
        {\
          PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]=0;\
          while(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index][PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]]!=PirAtE_CHARARRAY_END && PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index] <= PirAtE_MSG_DATATYPE_STRING_MAXLENGTH)\
          {\
            PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]++;\
          }\
          if(PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index] == PirAtE_MSG_DATATYPE_STRING_MAXLENGTH || PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]== 0)\
          {\
            PirAtE_ComType_Serialfunc.write(PirAtE_CHARARRAY_END);\
          }\
          else \
          {\
            PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index], PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]);\
          }\
        }\
        else \
        {\
          PirAtE_ComType_Serialfunc.write(PirAtE_DATA_SEND_ADRESSES[PirAtE_SEND_MSG_Index], PirAtE_DATA_SEND_DATASIZE[PirAtE_SEND_MSG_Index]);\
        }\
        PirAtE_ComType_Serialfunc.write(PirAtE_MSG_DELIMITER, PirAtE_MSG_DELIMITER_LENGTH);\
        PirAtE_SEND_MSG_Index++;\
        PirAtE_SEND_MSG_Index%=PirAtE_SendMsg_Amount;\
        PirAtE_nextMsgTime = micros() + PirAtE_SendMSGInterVal_micros;\
      }\
    }\
    else\
    {\
      if(micros() < PirAtE_nextMsgTime - PirAtE_SendMSGInterVal_micros)\
      {\
        PirAtE_nextMsgTime = micros() + PirAtE_SendMSGInterVal_micros;\
      }\
    }\
  }while (micros() < PirAtE_endTime && startIndex != PirAtE_SEND_MSG_Index);\
}


#ifndef PirAtE_ReceiveMsg_Amount
#define PirAtE_ReceiveMsg_Amount 5
#endif

byte* PirAtE_DATA_RECEIVE_ADRESSES[PirAtE_ReceiveMsg_Amount];
byte PirAtE_DATA_RECEIVE_DATASIZE[PirAtE_ReceiveMsg_Amount];
byte PirAtE_DATA_RECEIVE_DATATYPE_MASK[PirAtE_ReceiveMsg_Amount];
byte PirAtE_RECEIVE_DATA_MASK[PirAtE_ReceiveMsg_Amount/8 + (PirAtE_ReceiveMsg_Amount%8?1:0)];
byte PirAtE_DATA_RECEIVE_BUFFER[PirAtE_Serial_Buffer_Size];

#define PirAtE_DEFINE_RECEIVEMSG_MAKRO(PirAtE_MSG_ID,PirAtE_MSG_DATATYPE, Global_VariableAdress)\
{\
  PirAtE_DATA_RECEIVE_ADRESSES[PirAtE_MSG_ID] = (byte*) Global_VariableAdress;\
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



#define PirAte_RECIEVEMSGS_MAKRO()\
{\
  int receiveCount = 0;\
  unsigned long PirAtE_endTime = micros() + PirAtE_AllowedReceiveBlockTime_micros;\
  unsigned long PirAtE_nextMsgTime = micros();\
  do\
  {\
    if(micros() > PirAtE_nextMsgTime)\
    {\
      if(PirAtE_ComType_Serialfunc.available()>0)\
      {\
        int bytes = PirAtE_ComType_Serialfunc.readBytes(PirAtE_DATA_RECEIVE_BUFFER,PirAtE_ComType_Serialfunc.available());\
        if(bytes > 0 && PirAtE_DATA_RECEIVE_BUFFER[0] - PirAtE_MSG_DATAID_OFFSET < PirAtE_ReceiveMsg_Amount)\
        {\
          int msgID = PirAtE_DATA_RECEIVE_BUFFER[0] - PirAtE_MSG_DATAID_OFFSET;\
          if(bytes <= PirAtE_MSG_DATAID_LENGTH+PirAtE_DATA_RECEIVE_DATASIZE[msgID])\
          {\
            receiveCount++;\
            if(PirAtE_DATA_RECEIVE_DATATYPE_MASK[msgID] == PirAtE_MSG_DATATYPE_STRING)\
            {\
              for (int j = 0; j < PirAtE_DATA_RECEIVE_DATASIZE[msgID];j++)\
              {\
                PirAtE_DATA_RECEIVE_ADRESSES[msgID][j] = PirAtE_DATA_RECEIVE_DATASIZE[j+1];\
                if(j == bytes||(PirAtE_DATA_RECEIVE_DATASIZE[j+1]== PirAtE_CHARARRAY_END && PirAtE_DATA_RECEIVE_DATATYPE_MASK[msgID] == PirAtE_MSG_DATATYPE_STRING))\
                {\
                  break;\
                }\
              }\
            }\
            else\
            {\
              for (int j = 0; j < PirAtE_DATA_RECEIVE_DATASIZE[msgID];j++)\
              {\
                PirAtE_DATA_RECEIVE_ADRESSES[msgID][j] = PirAtE_DATA_RECEIVE_DATASIZE[j+1];\
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
  }while (micros() < PirAtE_endTime && receiveCount < PirAtE_ReceiveMsg_Amount);\
}

#endif
