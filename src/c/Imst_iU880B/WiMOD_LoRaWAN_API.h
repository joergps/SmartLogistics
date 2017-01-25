//-----------------------------------------------------------
// LoRaWAN Host Controller Interface
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#ifndef WIMOD_LORAWAN_API_H
#define WIMOD_LORAWAN_API_H

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------
#define DEVMGMT_SAP_ID		    0x01
#define DEVMGMT_MSG_PING_REQ	0x01


//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------

// Send ping
int WiMOD_LoRaWAN_SendPing();

#endif
