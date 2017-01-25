//-----------------------------------------------------------
// LoRaWAN Host Controller Interface Objects
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include "WiMOD_HCI_Layer.h"
#include "crc16.h"
#include "slip.h"

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------
static UINT8  TxBuffer[sizeof( TWiMOD_HCI_Message ) * 2 + 2];

//-----------------------------------------------------------
// Implementation
//-----------------------------------------------------------
int WiMOD_HCI_SendMessage(TWiMOD_HCI_Message* txMessage) {
  // check parameter
  if (!txMessage) {
    return -1;
  }
  
  // calculate CRC16 over header and payload
  UINT16 crc16 = CRC16_Calc(&txMessage->SapID,
                            txMessage->Length + WIMOD_HCI_MSG_HEADER_SIZE,
                            CRC16_INIT_VALUE);
  
  // get 1s complement
  // PSJ: ???
  crc16 = ~crc16;
  
  // attach CRC16 and fix length
  txMessage->Payload[txMessage->Length]     = LOBYTE(crc16);
  txMessage->Payload[txMessage->Length + 1] = HIBYTE(crc16);
  
  // SLIP encoding 
  int txLength = SLIP_EncodeData(TxBuffer,
                                  sizeof(TxBuffer),
                                  &txMessage->SapID,
                                  txMessage->Length + WIMOD_HCI_MSG_HEADER_SIZE + WIMOD_HCI_MSG_FCS_SIZE);
                                  
  if (txLength > 0) {
    // i.e. message is ok
    // TODO: Substituet with
    // int result = SerialDevice_SendData(TxBuffer, txLength);
    int result = 1;
    if (result > 0) {
      // send message worked!
      return 1;
    }
  }

  // ERROR: Slip layer could not encode message
  return 0;
}
