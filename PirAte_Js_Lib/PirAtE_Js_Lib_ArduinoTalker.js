//##MSGTypes## ASCII
//R RequestData
//M Message
//I Int
//U Uint
//L Long
//u Ulong
//F Float
//D Double
//C Char
//S String/Chararray with /0 as end
//B Byte
//b bool

//##DELIMITER##
//0xff P i r A t E \n


//Converter List
Converter = {}
Converter['R'] = {datatypeConverter:null,callback: RequestCallback};
Converter['M'] = {datatypeConverter:null,callback: DebugCallback};
Converter['I'] = {datatypeConverter:null,callback: RequestCallback};
Converter['U'] = {datatypeConverter:null,callback: DebugCallback};


//Bytes till Delimiter
function CastArduMsg(ArduMSg)
{

}

function RequestCallback(Data)
{

}

function DebugCallback(Data)
{

}