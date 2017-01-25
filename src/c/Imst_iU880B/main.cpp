//---
// Sample application
// Taken from: ${github:SmartLogistics}/doc/LoRaWan/Imst_iU880B/WiMOD_LoRaWAN_EndNode_Modem_HCI_Spec_V1_13.pdf
//
// Notes: Compile with "make lorasender"
//
// Author: Joerg P-S
//---

#include <stdio.h>
#include "WiMOD_LoRaWAN_API.h"

// forward declarations
static void Ping();

int main(int argc, char *argv[]) {
  printf("***** Main started.\n");
  Ping();
  printf("***** Main ended.\n");
}

void Ping() {
  WiMOD_LoRaWAN_SendPing();
}