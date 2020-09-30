#define PirAtE_SendMSGInterVal_micros 16000ul
#define PirAtE_AllowedSendBlockTime_micros 2000ul
#define PirAtE_AllowActiveWaitingOnSend false
#define PirAtE_RequestInterVal_micros 1000000ul
#define PirAtE_AllowedReceiveBlockTime_micros 200ul

/*
PirAtE_START_COM()
*/

#define PirAtE_Serial_Buffer_Size 64
#define PirAtE_Serial_Baudrate 115200
#define PirAtE_ComType_Serialfunc Serial

/*
PirAtE_SEND_DEBUG_MAKRO(Msg)
*/
/*
PirAtE_DEFINE_SENDMSG_MAKRO(PirAtE_MSG_ID,PirAtE_MSG_DATATYPE, Global_VariableAddress, PirAtE_MSG_SENDMODE)
*/

// --  PirAtE_MSG_SENDMODE_AUTO 1
// --  PirAtE_MSG_SENDMODE_MANUEL 0

/*
PirAtE_IS_NEW_DATA_TO_SEND(PirAtE_MSG_ID)
*/
/*
PirAtE_SENDMSGS_MAKRO()
*/
/*
PirAtE_DEFINE_RECEIVEMSG_MAKRO(PirAtE_MSG_ID,PirAtE_MSG_DATATYPE, Global_VariableAddress)
*/
/*
PirAte_RECEIVEMSGS_MAKRO()
*/
/*
PirAtE_IS_NEW_DATA_AVAILABLE(PirAtE_MSG_ID)
*/
/*
PirAtE_NEW_DATA_IS_READ(PirAtE_MSG_ID)
*/
//Int,Long (Unsigned,Signed)
//--  PirAtE_MSG_DATATYPE_INT 'I'
//--  PirAtE_MSG_DATATYPE_UINT 'U'
//--  PirAtE_MSG_DATATYPE_LONG 'L'
//--  PirAtE_MSG_DATATYPE_ULONG 'u'

//Float,Double
//--  PirAtE_MSG_DATATYPE_FLOAT 'F'
//--  PirAtE_MSG_DATATYPE_DOUBLE 'D'

//Byte
//--  PirAtE_MSG_DATATYPE_BYTE 'B'
//Word
//--  PirAtE_MSG_DATATYPE_WORD 'W'

//Bool '0' or '1'
//--  PirAtE_MSG_DATATYPE_BOOL 'b'
//Char 1 Length
//--  PirAtE_MSG_DATATYPE_CHAR 'C'
//String,CharArray
//--  PirAtE_MSG_DATATYPE_STRING 'S'
