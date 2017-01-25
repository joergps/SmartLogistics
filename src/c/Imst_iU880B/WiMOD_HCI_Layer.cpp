//-----------------------------------------------------------
// LoRaWAN Host Controller Interface Objects
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include "WiMOD_HCI_Layer.h"
#include "crc16.h"

int WiMOD_HCI_SendMessage(TWiMOD_HCI_Message* txMessage) {
  // check parameter
  if (!txMessage) {
    return -1;
  }
  
  // calculate CRC16 over header and payload
  UINT16 crc16 = CRC16_Calc(&txMessage->SapID,
                            txMessage->Length + WIMOD_HCI_MSG_HEADER_SIZE,
                            CRC16_INIT_VALUE);

  return 0;
}
