//---
// Sample application
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Notes: Compile with "make lorasender"
//
// Author: Joerg P-S
//---

#include "WiMOD_LoRaWAN_API.h"
#include "utilities.h"

#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <thread>

#define COM_PORT  "COM128"

typedef unsigned char	UINT8;
typedef uint32_t UINT32;

// forward declarations
extern bool hasPingResponse;
extern bool hasMessageResponse;

static void DoPing();
static void DoSendUnconfirmedData();
static char* getUsageString();
static void Ping();
static void SendUnconfirmedData();

// defines
static int TIMEOUT_IN_SECONDS = 5;
static UINT8 DEVICE_ID[4] = {0x01};
static UINT8 NETWORK_SESSION_KEY[16] = {0x01}; // Network Session Key = [1][0]...[0]
static UINT8 APPLICATION_SESSION_KEY[16] = {0x02}; // Application Session Key = [2][0]...[0]

// Possible switches:
// p = ping
// see: https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html#Using-Getopt
static char* options = "p--s--?-- ";

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // at least one option is required
    fprintf (stderr, getUsageString(), argv[0]);
    return -1;
  }
  
  printf("***** Main started.\n");
  
  // initialization
  bool init = WiMOD_LoRaWAN_Init(COM_PORT);
  
  if (init == false) {
    printf("Could not initialize adapter at port '%s'.", COM_PORT);
    return -1;
  }
  
  int c;

  while ((c = getopt (argc, argv, options)) != -1) {
    switch (c) {  
      case 'p': 
        Ping();
        break;
      case 's':
        SendUnconfirmedData();
        break;
      case '?': 
        fprintf (stderr, getUsageString(), argv[0]);
        break;
    }  
  }
  
  // Close device
  WiMOD_LoRaWAN_Close();
  
  printf("\n***** Main ended.\n");
}

void DoPing() {
  WiMOD_LoRaWAN_SendPing();
}

void DoSendUnconfirmedData() {
  // port 0x21
  // TODO: Adapt?
  UINT8 port = 0x21;
  
  UINT8 data[4];
  
  data[0] = 0x01;
  data[1] = 0x02;
  data[2] = 0x03;
  data[3] = 0x04;
  
  // TODO: Send actual message
  WiMOD_LoRaWAN_SendUnconfirmedRadioData(port, data, 4);
}

char* getUsageString() {
  return "usage: %s -p \nOptions: \n     -p  : Send ping\n     -s  : Send unconfirmed message\n\n";
}

void Ping() {
  // TODO figure out why ping has to be sent twice
  DoPing();
  DoPing();
  int waitInSeconds = 0; // obviously not really seconds, but close enough
  
  while (waitInSeconds < TIMEOUT_IN_SECONDS && !hasPingResponse) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
    
    // handle receiver process
    WiMOD_LoRaWAN_Process();

    ++waitInSeconds;
  }
  
  if (hasPingResponse) {
    printf("Ping was successfully received after about %d seconds.\n", waitInSeconds);
  } else {
    printf("Ping FAILED with timeout after %d seconds.\n", TIMEOUT_IN_SECONDS);
  }
  
}

void SendUnconfirmedData() {
  printf("Activating device '%d'...", DEVICE_ID);
  WiMOD_LoRaWAN_ActivateDevice(DEVICE_ID, NETWORK_SESSION_KEY, APPLICATION_SESSION_KEY);
  int activationResult = WiMOD_LoRaWAN_ActivateDevice(DEVICE_ID, NETWORK_SESSION_KEY, APPLICATION_SESSION_KEY);
  if (activationResult == 0) {
    printf("successful.\n");
  } else {
    printf("failed.\n");
    return;
  }
  
  DoSendUnconfirmedData();
  int waitInSeconds = 0; // obviously not really seconds, but close enough
  
  while (waitInSeconds < TIMEOUT_IN_SECONDS && !hasMessageResponse) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
    
    // handle receiver process
    WiMOD_LoRaWAN_Process();

    ++waitInSeconds;
  }
  
  if (hasMessageResponse) {
    printf("Message was successfully received after about %d seconds.\n", waitInSeconds);
  } else {
    printf("Message FAILED with timeout after %d seconds.\n", TIMEOUT_IN_SECONDS);
  }  
}
