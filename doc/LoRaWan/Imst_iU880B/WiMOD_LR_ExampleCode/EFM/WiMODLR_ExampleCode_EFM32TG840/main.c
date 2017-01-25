/**
 * @file main.c
 * <!------------------------------------------------------------------------>
 * @brief @ref REF "WiMODLR HCI Example"
 *
 * @par Project:
 * <!------------------------------------------------------------------------>
 * <!--
 * @par Description:
 *
 * This example shows how to get started with iM880A via HCI. The radio module
 * will send out a test telegramm after reception of any redio telegramm.
 * The RF configuration is equal to the default settings so that SK-iM880A can
 * be used as peer device without changings
 * -->
 * <!------------------------------------------------------------------------>
 * <!--
 * @remarks
 * - REMARK: The Interval of incoming radio telegrams has to be large enough  
 *           to receice the answer telegram ! (e.g. 2 seconds) 
 * -->
 * <!------------------------------------------------------------------------
 * Copyright (c) 2015
 * IMST GmbH
 * Carl-Friedrich Gauss Str. 2
 * 47475 Kamp-Lintfort
 * -------------------------------------------------------------------------->
 * @author Mathias Hater (MH), IMST
 * <!------------------------------------------------------------------------
 * Target OS:    none
 * Target CPU:   EFM32
 * Compiler:     IAR C/C++ Compiler
 * -------------------------------------------------------------------------->
 * @internal
 * @par Revision History:
 * <PRE>
 * ---------------------------------------------------------------------------
 * Version | Date       | Author | Comment
 * ---------------------------------------------------------------------------
 * 0.1     | 22.01.2015 | MH     | Created
 *
 * </PRE>

 Copyright (c) 2015 IMST GmbH.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are NOT permitted without prior written permission
 of the IMST GmbH.

 THIS SOFTWARE IS PROVIDED BY THE IMST GMBH AND CONTRIBUTORS ``AS IS'' AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE IMST GMBH OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 THIS SOFTWARE IS CLASSIFIED AS: CONFIDENTIAL

 *******************************************************************************/

// board support package
#include "bsp.h"

// EFM32 device files
#include "em_chip.h"
#include "em_cmu.h"

// HCI wrapper file
#include "iM880A_RadioInterface.h"

// needed for power-up delay
#include "PDDDelayTimer.h"


//------------------------------------------------------------------------------
//
//	Section Defines
//
//------------------------------------------------------------------------------

#define TX_LENGTH               13

#define POWERUP_DELAY           500     // ms

     
//------------------------------------------------------------------------------
//
//	Section Typedefs
//
//------------------------------------------------------------------------------

typedef enum
{
    SEND_MSG                        = 0x0001,
    POWER_UP                        = 0x0002,
    MSG_RECEIVED                    = 0x0004,
    
}TMainEventCode;


//------------------------------------------------------------------------------
//
//	Section RAM
//
//------------------------------------------------------------------------------

UINT32 mainEvent = 0;

uint8_t txBuffer[TX_LENGTH] = {'"','H','e','l','l','o',' ','W','o','l','d','!','"'};



//------------------------------------------------------------------------------
//
//	Section Code
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//	CbRxIndication
//
//------------------------------------------------------------------------------
static void
CbRxIndication     (UINT8*          rxMsg,
                    UINT8           length,
                    TRadioFlags     rxFlags)
{
    if(rxFlags == trx_RXDone)
    {
        mainEvent |= MSG_RECEIVED;  // Radio Msg received
    }
}


//------------------------------------------------------------------------------
//
//	CbTxIndication
//
//------------------------------------------------------------------------------
static void
CbTxIndication     (TRadioMsg*     txMsg,
                    TRadioFlags     txFlags)
{
    if(txFlags == trx_TXDone)
    {
        // TX was successfull
    }
    else
    {   
        //  error
    }
}



//------------------------------------------------------------------------------
//
//	System_Setup
//
//------------------------------------------------------------------------------
//!
//! @brief: Top Level Setup routine
//!
//------------------------------------------------------------------------------
void System_Setup(void)
{        
    // Init external clock
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);    
    CMU_ClockEnable(cmuClock_HFPER, true);
    
    // Init delay timer
    PDDDelayTimer_Setup();            
}





//------------------------------------------------------------------------------
//
//	main
//
//------------------------------------------------------------------------------

int main(void)
{
    // Initialize µC
    CHIP_Init();
    
    // Initalizing System
    System_Setup();    
    
    // Initialize radio driver
    iM880A_Init();    
    
    // Register callback functions for receive / send
    iM880A_RegisterRadioCallbacks(CbRxIndication, CbTxIndication);
        
    // Wait for radio to power up
    PDDDelayTimer_Delay_ms(POWERUP_DELAY);
        
    // Set configuration parameters
    iM880A_Configure();
    
    while(1)    
    {
        // Radio telegram received?
        if(mainEvent & MSG_RECEIVED)
        {
            // Send out radio message                
            if(iM880A_SendRadioTelegram(txBuffer, TX_LENGTH) != WiMODLR_RESULT_OK)
                   ; // handle faults
            
            // clear event
            mainEvent &= ~MSG_RECEIVED;
        }
    }

}



