//-----------------------------------------------------------
// LoRaWAN Host Controller Interface
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#ifndef WIMOD_LORAWAN_API_H
#define WIMOD_LORAWAN_API_H

//-----------------------------------------------------------
// Defines; see HCI_Spec_v1.13
//-----------------------------------------------------------
typedef unsigned char	UINT8;

#define DEVMGMT_SAP_ID		    0x01
#define LORAWAN_SAP_ID        0x10

#define DEVMGMT_MSG_PING_REQ	0x01
#define DEVMGMT_MSG_PING_RSP  0x02

#define LORAWAN_MSG_SEND_UDATA_REQ 0x0D
#define LORAWAN_MSG_SEND_UDATA_RSP 0x0E

#define LORAWAN_MSG_SEND_CDATA_RSP 0x12

#define SESSION_KEY_LENGTH          16


//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------
void WiMOD_LoRaWAN_ActivateDevice(UINT8 deviceId, UINT8[] networkSessionKey, UINT8[] applicationSessionKey);

void WiMOD_LoRaWAN_Close();

// Initialize device
bool WiMOD_LoRaWAN_Init(const char* comPort);

// Handle process, i.e. incoming data from USB adaptor
void WiMOD_LoRaWAN_Process();

// Send unconfirmed data
int WiMOD_LoRaWAN_SendUnconfirmedRadioData(UINT8 port, UINT8* data, int length);

// Send ping
int WiMOD_LoRaWAN_SendPing();

#endif
