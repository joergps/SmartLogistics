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
// Forward declarations
//-----------------------------------------------------------
// HCI Message Receiver callback
static void WiMOD_LoRaWAN_Process_DevMgmt_Message(TWiMOD_HCI_Message* rxMessage);

static void WiMOD_LoRaWAN_Process_LoRaWAN_Message(TWiMOD_HCI_Message* rxMessage);

static TWiMOD_HCI_Message* WiMOD_LoRaWAN_Process_RxMessage(TWiMOD_HCI_Message* rxMessage);

//-----------------------------------------------------------
// Variables
//-----------------------------------------------------------

// reserve one TxMessage
TWiMOD_HCI_Message TxMessage;

// reserve one RxMessage
TWiMOD_HCI_Message RxMessage;

//-----------------------------------------------------------
// Implementation
//-----------------------------------------------------------
void WiMOD_LoRaWAN_Close() {
  WiMOD_HCI_Close();
}

bool WiMOD_LoRaWAN_Init(const char* comPort) {
  // init HCI layer
  return WiMOD_HCI_Init(comPort, // comPort
                  WiMOD_LoRaWAN_Process_RxMessage, // receiver callback
                  &RxMessage); // rx message
}

void WiMOD_LoRaWAN_Process() {
  // call HCI process
  WiMOD_HCI_Process();
}

// Handle received Device Management SAP messages
static void WiMOD_LoRaWAN_Process_DevMgmt_Message(TWiMOD_HCI_Message* rxMessage) {
  switch(rxMessage->MsgID) {
    case DEVMGMT_MSG_PING_RSP:
      printf("Ping Response, Status : 0x%02X\n\r", (UINT8)rxMessage->Payload[0]);
      break;
    default:
      printf("unhandled DeviceMgmt message received - MsgID : 0x%02X\n\r", (UINT8)rxMessage->MsgID);
      break;
  }
}

// Handle received LoRaWAN SAP messages
static void WiMOD_LoRaWAN_Process_LoRaWAN_Message(TWiMOD_HCI_Message* rxMessage) {
  switch(rxMessage->MsgID) {
    case LORAWAN_MSG_SEND_UDATA_RSP:
      printf("Send U-Data Response, Status : 0x%02X\n\r", (UINT8)rxMessage->Payload[0]);
      break;
    case LORAWAN_MSG_SEND_CDATA_RSP:
      printf("Send C-Data Response, Status : 0x%02X\n\r", (UINT8)rxMessage->Payload[0]);
      break;
    default:
      printf("unhandled LoRaWAN SAP message received - MsgID : 0x%02X\n\r", (UINT8)rxMessage->MsgID);
      break;
  }
}

static TWiMOD_HCI_Message* WiMOD_LoRaWAN_Process_RxMessage(TWiMOD_HCI_Message* rxMessage){
  switch(rxMessage->SapID) {
    case DEVMGMT_SAP_ID:
      WiMOD_LoRaWAN_Process_DevMgmt_Message(rxMessage);
      break;
    case LORAWAN_SAP_ID:
      WiMOD_LoRaWAN_Process_LoRaWAN_Message(rxMessage);
    break;
  }
  return &RxMessage;
}

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
