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
#include <thread>

#define COM_PORT  "COM128"

// forward declarations
extern bool hasPingResponse;
static void Ping();
static void DoPing();

// defines
static int TIMEOUT_IN_SECONDS = 5;

int main(int argc, char *argv[]) {
  printf("***** Main started.\n");
  
  // initialization
  bool init = WiMOD_LoRaWAN_Init(COM_PORT);
  
  if (init == false) {
    printf("Could not initialize adapter at port '%s'.", COM_PORT);
    return -1;
  }
  
  // ping device
  Ping();
  
  // Close device
  WiMOD_LoRaWAN_Close();
  
  printf("\n***** Main ended.\n");
}

void DoPing() {
  WiMOD_LoRaWAN_SendPing();
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
