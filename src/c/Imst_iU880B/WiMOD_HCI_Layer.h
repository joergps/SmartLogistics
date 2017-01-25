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
typedef uint16_t	UINT16;

#define WIMOD_HCI_MSG_PAYLOD_SIZE 	300
#define WIMOD_HCI_MSG_FCS_SIZE		  2
#define WIMOD_HCI_MSG_HEADER_SIZE   2

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

//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------
int WiMOD_HCI_SendMessage(TWiMOD_HCI_Message* txMessage);

#endif
