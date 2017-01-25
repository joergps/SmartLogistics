//-----------------------------------------------------------
// Interface to serial device
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

#include <termios.h>

#define Baudrate_9600       9600
#define Baudrate_115200     115200
#define DataBits_7          CS7
#define DataBits_8          CS8
#define Parity_Even         PARENB
#define Parity_None         0

typedef unsigned char	UINT8;
typedef uint32_t	    UINT32;

// SerialDevice_Open(comPort, Baudrate_115200, DataBits_8, Parity_None);
bool SerialDevice_Open(const char* comPort, UINT32 baudRate, int bits = DataBits_8, UINT8 parity = Parity_None);

int SerialDevice_ReadData(UINT8* rxBuffer, int bufferSize);

bool SerialDevice_SendData(UINT8* data, int txLength);

#endif