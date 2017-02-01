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
#include <string.h>
#include "WiMOD_LoRaWAN_API.h"
#include "WiMOD_HCI_Layer.h"

//-----------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------
// HCI Message Receiver callback
static void WiMOD_LoRaWAN_Process_DevMgmt_Message(TWiMOD_HCI_Message* rxMessage);

static void WiMOD_LoRaWAN_Process_LoRaWAN_Message(TWiMOD_HCI_Message* rxMessage);

static TWiMOD_HCI_Message* WiMOD_LoRaWAN_Process_RxMessage(TWiMOD_HCI_Message* rxMessage);

static void WiMOD_LoRaWAN_ShowResponse(const char* string, const TIDString* statusTable, UINT8 statusID);

//-----------------------------------------------------------
// Status codes translation
//-----------------------------------------------------------

// Status Codes for DeviceMgmt Response Messages
static const TIDString WiMOD_DeviceMgmt_StatusStrings[] =
{
    { DEVMGMT_STATUS_OK,                   "ok" },
    { DEVMGMT_STATUS_ERROR,                "error" } ,
    { DEVMGMT_STATUS_CMD_NOT_SUPPORTED,    "command not supported" },
    { DEVMGMT_STATUS_WRONG_PARAMETER,      "wrong parameter" },
    { DEVMGMT_STATUS_WRONG_DEVICE_MODE,    "wrong device mode" },

    // end of table
    { 0, 0 }
};

// Status Codes for LoRaWAN Response Messages
static const TIDString WiMOD_LoRaWAN_StatusStrings[] =
{
    { LORAWAN_STATUS_OK,                    "ok" },
    { LORAWAN_STATUS_ERROR,                 "error" } ,
    { LORAWAN_STATUS_CMD_NOT_SUPPORTED,     "command not supported" },
    { LORAWAN_STATUS_WRONG_PARAMETER,       "wrong parameter" },
    { LORAWAN_STATUS_WRONG_DEVICE_MODE,     "wrong device mode" },
    { LORAWAN_STATUS_NOT_ACTIVATED,         "device not activated" },
    { LORAWAN_STATUS_BUSY,                  "device busy - command rejected" },
    { LORAWAN_STATUS_QUEUE_FULL,            "message queue full - command rejected" },
    { LORAWAN_STATUS_LENGTH_ERROR,          "HCI message length error" },
    { LORAWAN_STATUS_NO_FACTORY_SETTINGS,   "no factory settings available" },
    { LORAWAN_STATUS_CHANNEL_BLOCKED_BY_DC, "error: channel blocked due to duty cycle, please try later again" },
    { LORAWAN_STATUS_CHANNEL_NOT_AVAILABLE, "error: channel not available" },

    // end of table
    { 0, 0 }
};

//-----------------------------------------------------------
// Variables
//-----------------------------------------------------------
bool hasDeviceInfoResponse = false;
bool hasMessageResponse = false;
bool hasPingResponse = false;

// reserve one TxMessage
TWiMOD_HCI_Message TxMessage;

// reserve one RxMessage
TWiMOD_HCI_Message RxMessage;

//-----------------------------------------------------------
// Implementation
//-----------------------------------------------------------
int WiMOD_LoRaWAN_ActivateDevice(UINT8* deviceId, UINT8* networkSessionKey, UINT8* applicationSessionKey) {
  // TODO Check length of networkSessionKey and applicationSessionKey
  
  // 2. init header
  TxMessage.SapID	  = LORAWAN_SAP_ID; 
  TxMessage.MsgID	  = LORAWAN_MSG_ACTIVATE_DEVICE_REQ;
  TxMessage.Length	= 36;  

  // 3. init payload
  // (see Spec p. 25)
  // a) Payload[0..3] = deviceId
  memcpy(&TxMessage.Payload[0], deviceId, DEVICE_ID_LENGTH);  
  
  // b) Payload[4..19] = networkSessionKey
  memcpy(&TxMessage.Payload[4], networkSessionKey, SESSION_KEY_LENGTH);  
  
  // c) Payload[20..35] = applicationSessionKey
  memcpy(&TxMessage.Payload[20], applicationSessionKey, SESSION_KEY_LENGTH);  
  
  // 4. send message with payload
  return WiMOD_HCI_SendMessage(&TxMessage);  
}

void WiMOD_LoRaWAN_Close() {
  WiMOD_HCI_Close();
}

bool WiMOD_LoRaWAN_Init(const char* comPort) {
  // init HCI layer
  return WiMOD_HCI_Init(comPort, // comPort
                  WiMOD_LoRaWAN_Process_RxMessage, // receiver callback
                  &RxMessage); // rx message
}

int WiMOD_LoRaWAN_GetDeviceInformation() {
  printf("Getting device information...");
  // Init header
  TxMessage.SapID	  = DEVMGMT_SAP_ID;
  TxMessage.MsgID	  = DEVMGMT_MSG_GET_DEVICE_INFO_REQ;
  TxMessage.Length	= 0;
  
  // Send message
  int result = WiMOD_HCI_SendMessage(&TxMessage);
  if (result == 0) {
    printf("successful.\n");
  } else {
    printf("failed.\n");
  }
  return result;
}

void WiMOD_LoRaWAN_Process() {
  // call HCI process
  WiMOD_HCI_Process();
}

// Handle received Device Management SAP messages
static void WiMOD_LoRaWAN_Process_DevMgmt_Message(TWiMOD_HCI_Message* rxMessage) {
  switch(rxMessage->MsgID) {
    case DEVMGMT_MSG_PING_RSP:
      WiMOD_LoRaWAN_ShowResponse("Ping response", WiMOD_DeviceMgmt_StatusStrings, rxMessage->Payload[0]);
      hasPingResponse = true;
      break;
    case DEVMGMT_MSG_GET_DEVICE_INFO_RSP:
      WiMOD_LoRaWAN_ShowResponse("Device info response", WiMOD_DeviceMgmt_StatusStrings, rxMessage->Payload[0]);
      hasDeviceInfoResponse = true;
      break;      
    default:
      printf("unhandled DeviceMgmt message received - MsgID : 0x%02X\n\r", (UINT8)rxMessage->MsgID);
      break;
  }
}

// Handle received LoRaWAN SAP messages
static void WiMOD_LoRaWAN_Process_LoRaWAN_Message(TWiMOD_HCI_Message* rxMessage) {
  // printf("In ..LoRaWAN_Message... \n");
  switch(rxMessage->MsgID) {
    case LORAWAN_MSG_SEND_UDATA_RSP:
      WiMOD_LoRaWAN_ShowResponse("Send U-Data response", WiMOD_DeviceMgmt_StatusStrings, rxMessage->Payload[0]);
      printf("Send message!\n");
      hasMessageResponse = true;
      break;
    case LORAWAN_MSG_SEND_CDATA_RSP:
      WiMOD_LoRaWAN_ShowResponse("Send C-Data response", WiMOD_DeviceMgmt_StatusStrings, rxMessage->Payload[0]);
      break;
    case LORAWAN_MSG_ACTIVATE_DEVICE_RSP:
      WiMOD_LoRaWAN_ShowResponse("Activate device response", WiMOD_DeviceMgmt_StatusStrings, rxMessage->Payload[0]);
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

int WiMOD_LoRaWAN_SendUnconfirmedRadioData(UINT8 port, UINT8* data, int length) {
  // 1. check length
  if (length > (WIMOD_HCI_MSG_PAYLOD_SIZE - 1)) {
    return -1;
  }
  
  // 2. init header
  TxMessage.SapID	  = LORAWAN_SAP_ID;
  TxMessage.MsgID	  = LORAWAN_MSG_SEND_UDATA_REQ;
  TxMessage.Length	= 1 + length;  

  // 3. init payload
  TxMessage.Payload[0] = port;
  memcpy(&TxMessage.Payload[1], data, length);
  
  // 4. send message with payload
  return WiMOD_HCI_SendMessage(&TxMessage);
}

int WiMOD_LoRaWAN_SendPing() {
  printf("Pinging device...");
  // Init header
  TxMessage.SapID	  = DEVMGMT_SAP_ID;
  TxMessage.MsgID	  = DEVMGMT_MSG_PING_REQ;
  TxMessage.Length	= 0;
  
  // Send message
  int result = WiMOD_HCI_SendMessage(&TxMessage);
  if (result == 0) {
    printf("successful.\n");
  } else {
    printf("failed.\n");
  }
  return result;
}

static void WiMOD_LoRaWAN_ShowResponse(const char* string, const TIDString* statusTable, UINT8 statusID) {
  while(statusTable->String) {
    if (statusTable->ID == statusID) {
      printf(string);
      printf(" - Status(0x%02X) : ", statusID);
      printf(statusTable->String);
      printf("\n\r");
      return;
    }
    statusTable++;
  }
}
