//-----------------------------------------------------------
// LoRaWAN Host Controller Interface
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------


//-----------------------------------------------------------
// Includes
//-----------------------------------------------------------
#include <stdio.h>
#include "WiMOD_LoRaWAN_API.h"
#include "WiMOD_HCI_Layer.h"

//-----------------------------------------------------------
// Variables
//-----------------------------------------------------------
TWiMOD_HCI_Message TxMessage;

//-----------------------------------------------------------
// Implementation
//-----------------------------------------------------------
int WiMOD_LoRaWAN_SendPing() {
  printf("Ping started...");
  // Init header
  TxMessage.SapID	  = DEVMGMT_SAP_ID;
  TxMessage.MsgID	  = DEVMGMT_MSG_PING_REQ;
  TxMessage.Length	= 0;
  
  // Send message
  int result = WiMOD_HCI_SendMessage(&TxMessage);

  printf("done with result '%d'.\n", result);
  return result;
}
