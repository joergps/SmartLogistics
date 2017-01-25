//-----------------------------------------------------------
// LoRaWAN Host Controller Interface Objects
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#ifndef WIMOD_HCI_LAYER_H
#define WIMOD_HCI_LAYER_H

//-----------------------------------------------------------
// Includes
//-----------------------------------------------------------
#include <stdint.h>

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------
typedef unsigned char	UINT8;
typedef uint16_t	    UINT16;
typedef uint32_t	    UINT32;

#define WIMOD_HCI_MSG_PAYLOD_SIZE 	300
#define WIMOD_HCI_MSG_FCS_SIZE		  2
#define WIMOD_HCI_MSG_HEADER_SIZE   2

#define LOBYTE(x)                   (x)
#define HIBYTE(x)                   ((UINT16) (x) >> 8)

//-----------------------------------------------------------
// HCI Message Object
//-----------------------------------------------------------
typedef struct {
  UINT16 	Length;

  UINT8 	SapID;

  UINT8 	MsgID;

  UINT8 	Payload[WIMOD_HCI_MSG_PAYLOD_SIZE];

  UINT8 	CRC16[WIMOD_HCI_MSG_FCS_SIZE];
} TWiMOD_HCI_Message;

typedef TWiMOD_HCI_Message* (*TWiMOD_HCI_CbRxMessage)(TWiMOD_HCI_Message* rxMessage);

//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------

bool WiMOD_HCI_Init(const char* comPort, 
                    TWiMOD_HCI_CbRxMessage cbRxMessage, 
                    TWiMOD_HCI_Message* rxMessage);
                    
int WiMOD_HCI_SendMessage(TWiMOD_HCI_Message* txMessage);

#endif
