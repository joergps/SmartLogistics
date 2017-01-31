//-----------------------------------------------------------
// LoRaWAN Host Controller Interface Objects
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include "WiMOD_HCI_Layer.h"
#include "crc16.h"
#include "slip.h"
#include "SerialDevice.h"

//-----------------------------------------------------------
// Defines
//-----------------------------------------------------------

// SLIP Message Receiver Callback
static UINT8* WiMOD_HCI_ProcessRxMessage(UINT8* rxData, int rxLength);

static UINT8  TxBuffer[sizeof( TWiMOD_HCI_Message ) * 2 + 2];

typedef struct {
  // CRC Error counter
  UINT32 CRCErrors;
  
  // RxMessage
  TWiMOD_HCI_Message* RxMessage;
  
  // Receiver callback
  TWiMOD_HCI_CbRxMessage CbRxMessage;
} TWiMOD_HCI_MsgLayer;

static TWiMOD_HCI_MsgLayer HCI;

//-----------------------------------------------------------
// Implementation
//-----------------------------------------------------------
bool WiMOD_HCI_Close() {
  SerialDevice_Close();
}

bool WiMOD_HCI_Init(const char* comPort, // comPort
                    TWiMOD_HCI_CbRxMessage cbRxMessage, // HCI msg receiver callback
                    TWiMOD_HCI_Message* rxMessage) { // intial rxMessage
  // init error counter
  HCI.CRCErrors = 0;
  
  // save receiver callback
  HCI.CbRxMessage = cbRxMessage;

  // save RxMessage
  HCI.RxMessage = rxMessage;
  
  // init SLIP
  SLIP_Init(WiMOD_HCI_ProcessRxMessage);
  
  // init first RxBuffer to SAP_ID of HCI message, size without 16-Bit Length Field
  SLIP_SetRxBuffer(&rxMessage->SapID, sizeof(TWiMOD_HCI_Message) - sizeof(UINT16));
  
  // init serial device
  // see HCI_Spec_v1.13 page 10 for details
  return SerialDevice_Open(comPort, Baudrate_115200, DataBits_8, Parity_None);
}
//------------------------------------------------------------------------------

void WiMOD_HCI_Process() {
  UINT8 rxBuf[20];
  
  // read small chunk of data
  int rxLength = SerialDevice_ReadData(rxBuf, sizeof(rxBuf));
  
  // data available ?
  if (rxLength > 0) {
    // printf("*** Found data\n");
    // yes, forward to SLIP decoder, decoded SLIP message will be passed to
    // function "WiMOD_HCI_ProcessRxMessage"
    SLIP_DecodeData(rxBuf, rxLength);
  }
}

int WiMOD_HCI_SendMessage(TWiMOD_HCI_Message* txMessage) {
  // check parameter
  if (!txMessage) {
    return -1;
  }
  
  // calculate CRC16 over header and payload
  UINT16 crc16 = CRC16_Calc(&txMessage->SapID,
                            txMessage->Length + WIMOD_HCI_MSG_HEADER_SIZE,
                            CRC16_INIT_VALUE);
  
  // get 1s complement
  // PSJ: ???
  crc16 = ~crc16;
  
  // attach CRC16 and fix length
  txMessage->Payload[txMessage->Length]     = LOBYTE(crc16);
  txMessage->Payload[txMessage->Length + 1] = HIBYTE(crc16);
  
  // SLIP encoding 
  int txLength = SLIP_EncodeData(TxBuffer,
                                  sizeof(TxBuffer),
                                  &txMessage->SapID,
                                  txMessage->Length + WIMOD_HCI_MSG_HEADER_SIZE + WIMOD_HCI_MSG_FCS_SIZE);
                                  
  if (txLength > 0) {
    // i.e. message is ok
    int result = SerialDevice_SendData(TxBuffer, txLength);
    if (result > 0) {
      // send message worked!
      return 1;
    }
  }

  // ERROR: Slip layer could not encode message
  return 0;
}

static UINT8* WiMOD_HCI_ProcessRxMessage(UINT8* rxData, int rxLength) {
  // check min length
  if (rxLength >= (WIMOD_HCI_MSG_HEADER_SIZE + WIMOD_HCI_MSG_FCS_SIZE)) {
    if (CRC16_Check(rxData, rxLength, CRC16_INIT_VALUE)) {
      // receiver registered ?
      if (HCI.CbRxMessage) {
        // yes, complete message info
        HCI.RxMessage->Length = rxLength - (WIMOD_HCI_MSG_HEADER_SIZE + WIMOD_HCI_MSG_FCS_SIZE);
        
        // call upper layer receiver and save new RxMessage
        HCI.RxMessage = (*HCI.CbRxMessage)(HCI.RxMessage);
      }
    } else {
      HCI.CRCErrors++;
    }
  }

  // free HCI message available ?
  if (HCI.RxMessage) {
    // yes, return pointer to first byte
    return &HCI.RxMessage->SapID;
  }
  
  // error, disable SLIP decoder
  return 0;
}
