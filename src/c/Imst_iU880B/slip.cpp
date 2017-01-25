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

// SLIP Receiver/Decoder States
#define SLIPDEC_IDLE_STATE  0
#define SLIPDEC_START_STATE 1

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

void SLIP_Init(TSLIP_CbRxMessage cbRxMessage) {
  // init decoder to idle state, no rx-buffer avaliable
  SLIP.RxState = SLIPDEC_IDLE_STATE;
  SLIP.RxIndex = 0;
  SLIP.RxBuffer = 0;
  SLIP.RxBufferSize = 0;

  // save message receiver callback
  SLIP.CbRxMessage = cbRxMessage;
  
  // init encoder
  SLIP.TxIndex = 0;
  SLIP.TxBuffer = 0;
  SLIP.TxBufferSize = 0;
}

bool SLIP_SetRxBuffer(UINT8* rxBuffer, int rxBufferSize) {
  // receiver in IDLE state and client already registered ?
  if ((SLIP.RxState == SLIPDEC_IDLE_STATE) && SLIP.CbRxMessage) {
    // same buffer params
    SLIP.RxBuffer = rxBuffer;
    SLIP.RxBufferSize = rxBufferSize;
    
    // enable decoder
    SLIP.RxState = SLIPDEC_START_STATE;
    return true;
  }
  return false;
}