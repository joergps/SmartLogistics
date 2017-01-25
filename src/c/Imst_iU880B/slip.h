//-----------------------------------------------------------
// SLIP encoder
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#ifndef SLIP_H
#define SLIP_H

#include <stdint.h>

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------
typedef uint8_t     UINT8;
typedef UINT8*      (*TSLIP_CbRxMessage)(UINT8* message, int length);

//-----------------------------------------------------------
// Method declarations
//-----------------------------------------------------------
int SLIP_EncodeData(UINT8* dstBuffer, int txBufferSize, UINT8* srcData, int srcLength);

#endif