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

//-----------------------------------------------------------
//  Endpoint (SAP) Identifier
//-----------------------------------------------------------

#define DEVMGMT_SAP_ID		    0x01
#define LORAWAN_SAP_ID        0x10

//-----------------------------------------------------------
//  Message Identifier
//-----------------------------------------------------------

#define DEVMGMT_MSG_PING_REQ	0x01
#define DEVMGMT_MSG_PING_RSP  0x02

#define DEVMGMT_MSG_GET_DEVICE_INFO_REQ 0x03
#define DEVMGMT_MSG_GET_DEVICE_INFO_RSP 0x04

#define LORAWAN_MSG_ACTIVATE_DEVICE_REQ   0x01
#define LORAWAN_MSG_ACTIVATE_DEVICE_RSP   0x02

#define LORAWAN_MSG_SEND_UDATA_REQ 0x0D
#define LORAWAN_MSG_SEND_UDATA_RSP 0x0E

#define LORAWAN_MSG_SEND_CDATA_RSP 0x12

#define DEVICE_ID_LENGTH            4
#define SESSION_KEY_LENGTH          16

//-----------------------------------------------------------
//  Device Management SAP Message Identifier
//-----------------------------------------------------------

// Status Identifier
#define	DEVMGMT_STATUS_OK                       0x00
#define	DEVMGMT_STATUS_ERROR                    0x01
#define	DEVMGMT_STATUS_CMD_NOT_SUPPORTED        0x02
#define	DEVMGMT_STATUS_WRONG_PARAMETER          0x03
#define DEVMGMT_STATUS_WRONG_DEVICE_MODE        0x04

//-----------------------------------------------------------
//  LoRaWAN SAP Message Identifier
//-----------------------------------------------------------

// Status Identifier
#define LORAWAN_STATUS_OK                       0x00
#define	LORAWAN_STATUS_ERROR                    0x01
#define	LORAWAN_STATUS_CMD_NOT_SUPPORTED        0x02
#define	LORAWAN_STATUS_WRONG_PARAMETER          0x03
#define LORAWAN_STATUS_WRONG_DEVICE_MODE        0x04
#define LORAWAN_STATUS_NOT_ACTIVATED            0x05
#define LORAWAN_STATUS_BUSY                     0x06
#define LORAWAN_STATUS_QUEUE_FULL               0x07
#define LORAWAN_STATUS_LENGTH_ERROR             0x08
#define LORAWAN_STATUS_NO_FACTORY_SETTINGS      0x09
#define LORAWAN_STATUS_CHANNEL_BLOCKED_BY_DC    0x0A
#define LORAWAN_STATUS_CHANNEL_NOT_AVAILABLE    0x0B

// helper struct for ID -> string conversion
typedef struct {
  int         ID;
  const char* String;
} TIDString;


//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------
int WiMOD_LoRaWAN_ActivateDevice(UINT8* deviceId, UINT8* networkSessionKey, UINT8* applicationSessionKey);

void WiMOD_LoRaWAN_Close();

int WiMOD_LoRaWAN_GetDeviceInformation();

// Initialize device
bool WiMOD_LoRaWAN_Init(const char* comPort);

// Handle process, i.e. incoming data from USB adaptor
void WiMOD_LoRaWAN_Process();

// Send unconfirmed data
int WiMOD_LoRaWAN_SendUnconfirmedRadioData(UINT8 port, UINT8* data, int length);

// Send ping
int WiMOD_LoRaWAN_SendPing();

#endif
