//-----------------------------------------------------------
// SLIP encoder
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include "slip.h"

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------
#define SLIP_END      0xC0
#define SLIP_ESC      0xDB
#define SLIP_ESC_END  0xDC
#define SLIP_ESC_ESC  0xDD

//-----------------------------------------------------------
// Declare SLIP variables
//-----------------------------------------------------------
typedef struct
{
  // Decoder
  int                 RxState;
  int                 RxIndex;
  int                 RxBufferSize;
  UINT8*              RxBuffer;
  TSLIP_CbRxMessage   CbRxMessage;

  // Encoder
  int                 TxIndex;
  int                 TxBufferSize;
  UINT8*              TxBuffer;
} TSLIP;

static TSLIP  SLIP;

//-----------------------------------------------------------
// Implementations
//-----------------------------------------------------------
static void SLIP_StoreTxByte(UINT8 txByte) {
  if (SLIP.TxIndex < SLIP.TxBufferSize) {
    SLIP.TxBuffer[SLIP.TxIndex++] = txByte;
  }
}

int SLIP_EncodeData(UINT8* dstBuffer, int dstBufferSize, UINT8* srcData, int srcLength) {
  int txLength = 0;
  
  SLIP.TxBuffer = dstBuffer;
  SLIP.TxIndex = 0;
  SLIP.TxBufferSize = dstBufferSize;
  
  SLIP_StoreTxByte(SLIP_END);
  
  // iterate over all message bytes
  while(srcLength--) {
    switch (*srcData) {
      case SLIP_END:
        SLIP_StoreTxByte(SLIP_ESC);
        SLIP_StoreTxByte(SLIP_ESC_END);
        break;
      case SLIP_ESC:
        SLIP_StoreTxByte(SLIP_ESC);
        SLIP_StoreTxByte(SLIP_ESC_ESC);
        break;
      default:
        SLIP_StoreTxByte(*srcData);
        break;
    }
    
    // next byte
    srcData++;
  }
  
  // send end of SLIP message
  SLIP_StoreTxByte(SLIP_END);
  
  // length ok ?
  if (SLIP.TxIndex <= SLIP.TxBufferSize) {
    return SLIP.TxIndex;
  }

  // return tx length error
  return -1;  
}