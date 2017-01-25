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
#include <stdio.h>

#define COM_PORT  "COM128"

// forward declarations
static void Ping();

int main(int argc, char *argv[]) {
  printf("***** Main started.\n");
  
  // initialization
  bool init = WiMOD_LoRaWAN_Init(COM_PORT);
  
  if (init == false) {
    printf("Could not initialize adapter at port '%s'.", COM_PORT);
    return -1;
  }
  
  // ping device
  // TODO: Why does a single "ping" not work?
  Ping();
  Ping();
  
  // wait for reply from USB adapter
  bool run = true;
  printf("Waiting for feedback from adaptor; press <q> to quit...");
  while (run) {
  
    // handle receiver process
    WiMOD_LoRaWAN_Process();
    
    if (kbhit()) {
      char cmd = getch();
      
      switch (cmd) {
        case 'Q':
        case 'q':
          run = false;
          break;
        default:
          break;
      }
    }
  }
  WiMOD_LoRaWAN_Close();
  
  printf("\n***** Main ended.\n");
}

void Ping() {
  WiMOD_LoRaWAN_SendPing();
}
