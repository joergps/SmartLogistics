//-----------------------------------------------------------
// Interface to serial device
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Author: Joerg P-S
//-----------------------------------------------------------
#include "SerialDevice.h"
#include <stdio.h>

static int SerialDevice_ComHandle = INVALID_HANDLE_VALUE;

bool SerialDevice_Close() {
    if(SerialDevice_ComHandle != INVALID_HANDLE_VALUE)
    {
        ::close(SerialDevice_ComHandle);

        SerialDevice_ComHandle = INVALID_HANDLE_VALUE;
        return true;
    }
    
    return false;  
}

bool SerialDevice_Open(const char* comPort, UINT32 baudRate, int bits, UINT8 parity) {
  if (SerialDevice_ComHandle != INVALID_HANDLE_VALUE) {
    SerialDevice_Close();
  }

  // Open the serial port read/write, with no controlling terminal,
  // and don't wait for a connection.
  // The O_NONBLOCK flag also causes subsequent I/O on the device to
  // be non-blocking.
  // See open(2) ("man 2 open") for details.

  // TODO: Use parameter comPort
  const char* ptr = "/dev/ttyUSB0";
  
  //QString portName = QString("/dev/") + comPort;
  //QByteArray name  = portName.toLocal8Bit();
  ////const char* ptr = "/dev/tty.usbserial-IMST2"; //name.constData();
  //const char* ptr =name.constData();
  
  printf("Using device '%s'.\n", ptr);

  SerialDevice_ComHandle = ::open(ptr, O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (SerialDevice_ComHandle != INVALID_HANDLE_VALUE) {
    if (::ioctl(SerialDevice_ComHandle, TIOCEXCL) != INVALID_HANDLE_VALUE) {
      // Get the current options and save them so we can restore the
      // default settings later.
      struct termios _originalTTYAttrs;
      struct termios options;

      if (::tcgetattr(SerialDevice_ComHandle, &_originalTTYAttrs) != INVALID_HANDLE_VALUE) {
        // The serial port attributes such as timeouts and baud rate are set by
        // modifying the termios structure and then calling tcsetattr to
        // cause the changes to take effect. Note that the
        // changes will not take effect without the tcsetattr() call.
        // See tcsetattr(4) ("man 4 tcsetattr") for details.
        options = _originalTTYAttrs;
        
        // Print the current input and output baud rates.
        // See tcsetattr(4) ("man 4 tcsetattr") for details.
        cfmakeraw(&options);
        options.c_cc[VMIN] = 1;
        options.c_cc[VTIME] = 10;
        
        // The baud rate, word length, and handshake options can be set as follows:
        cfsetspeed(&options, baudRate);           // Set 57600 baud
        // cfsetspeed(&options, B115200);           // Set 115200 baud
        // Disable parity (even parity if PARODD
        options.c_cflag &= ~(CSTOPB | CRTSCTS | PARENB );
        
        // add flags for parity and word size
        options.c_cflag |= (CSIZE | parity);
        options.c_cflag |= (bits|CLOCAL|CREAD);               // Use n bit words
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        options.c_iflag &= ~(IXOFF | IXON | INPCK | OPOST);
        
        // Cause the new options to take effect immediately.
        if (tcsetattr(SerialDevice_ComHandle, TCSANOW, &options) != INVALID_HANDLE_VALUE) {
          return true;
        }
      }
    }
    SerialDevice_Close();
  }

  return false;
}

int SerialDevice_ReadData(UINT8* rxBuffer, int bufferSize) {
  // handle ok ?
  if(SerialDevice_ComHandle == INVALID_HANDLE_VALUE) {
    return 0;
  }

  ssize_t  numRxBytes = ::read(SerialDevice_ComHandle, rxBuffer, bufferSize);
  if(numRxBytes > 0) {
    return (int)numRxBytes;
  }

  return 0;
}

bool SerialDevice_SendData(UINT8* data, int txLength) {
  if(SerialDevice_ComHandle == INVALID_HANDLE_VALUE) {
    return false;
  }
  
  printf("Sending message...");
  size_t  numTxBytes = ::write(SerialDevice_ComHandle, data, txLength);

  if (numTxBytes == (size_t)txLength) {
    printf("successful.");
    return true;
  } else {
    printf("failed.\n");
    return false;
  }
}
