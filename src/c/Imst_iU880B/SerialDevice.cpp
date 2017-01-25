//-----------------------------------------------------------
// Interface to serial device
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include "SerialDevice.h"

bool SerialDevice_Open(const char* comPort, UINT32 baudRate, int bits, UINT8 parity) {
  // TODO!!!
  return false;
}

int SerialDevice_ReadData(UINT8* rxBuffer, int bufferSize) {
  // TODO!!!
  return -1;
}

bool SerialDevice_SendData(UINT8* data, int txLength) {
  // TODO!!!
  return false;
}