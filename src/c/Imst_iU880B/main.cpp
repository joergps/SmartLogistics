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
  WiMOD_LoRaWAN_Init(COM_PORT);
  
  // ping device
  Ping();
  
  // wait for reply from USB adapter
  bool run = true;
  while (run) {
    printf("Waiting for feedback from adaptor; press <q> to quit...");
    
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
  
  printf("\n***** Main ended.\n");
}

void Ping() {
  WiMOD_LoRaWAN_SendPing();
}