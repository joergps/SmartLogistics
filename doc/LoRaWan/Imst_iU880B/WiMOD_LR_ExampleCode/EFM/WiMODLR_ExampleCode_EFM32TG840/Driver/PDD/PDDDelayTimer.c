/**
 * @file efm32_PDDDelayTimer.h
 * <!------------------------------------------------------------------------>
 * @brief @ref REF ""
 *
 * @par Project:
 * <!------------------------------------------------------------------------>
 * <!--
 * @par Description:
 *
 *  [Description]
 * -->
 * <!--
 *  @ref [extdocname] "more..."
 *  -->
 * <!------------------------------------------------------------------------>
 * <!--
 * @remarks
 * - [...]
 * - [...]
 * -->
 * <!------------------------------------------------------------------------
 * Copyright (c) 2011
 * IMST GmbH
 * Carl-Friedrich Gauss Str. 2
 * 47475 Kamp-Lintfort
 * -------------------------------------------------------------------------->
 * @author Frank Brey (FB), IMST
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
 * 0.1     | 07.01.2012 | FB     | Created
 * </PRE>

 Copyright (c) 2011 IMST GmbH.
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


//------------------------------------------------------------------------------
// include files
//------------------------------------------------------------------------------
#include "PDDDelayTimer.h"

#include "bsp.h"

#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_timer.h"

//------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------

#define DELAY_HW_TIMER_MODULE           TIMER0
#define DELAY_HW_TIMER_CLOCK            cmuClock_TIMER0



//------------------------------------------------------------------------------
// private functions
//------------------------------------------------------------------------------

static bool 
doActiveWaiting(uint32_t value) 
{
    uint32_t fullValue;

    fullValue = BSP_XTAL_FREQ_MHZ / 16; // clock freq / (prescaler) ) !!!!!!
    fullValue *=  value;

    if (fullValue > 3u) 
    {
        fullValue -= 3u; // adjust timer a little bit
    }

    if (fullValue > 0xFFFFul) 
    {
        // error: timeout is too big
        return false;
    } 
    else 
    {
        DELAY_HW_TIMER_MODULE->IFC |= TIMER_IFC_CC0;

        DELAY_HW_TIMER_MODULE->CC[0].CCV = DELAY_HW_TIMER_MODULE->CNT + fullValue;

        /* wait for the Compare value to match */
        while (!(DELAY_HW_TIMER_MODULE->IF & TIMER_IFC_CC0))
            ;
    }

    return true;
}

//------------------------------------------------------------------------------
// public functions
//------------------------------------------------------------------------------

void PDDDelayTimer_Setup() 
{
    TIMER_Init_TypeDef timerInit;
    TIMER_InitCC_TypeDef timerCCInit;


    /* Enable clock for TIMER0 module */
    CMU_ClockEnable(DELAY_HW_TIMER_CLOCK, true);

    /* Select TIMER0 parameters */
    timerInit.enable     = true;
    timerInit.debugRun   = false;
    timerInit.prescale   = timerPrescale16;
    timerInit.clkSel     = timerClkSelHFPerClk;
    timerInit.fallAction = timerInputActionNone;
    timerInit.riseAction = timerInputActionNone;
    timerInit.mode       = timerModeUp;
    timerInit.dmaClrAct  = false;
    timerInit.quadModeX4 = false;
    timerInit.oneShot    = false;
    timerInit.sync       = true;
    timerInit.count2x    = 0;


    timerCCInit.cufoa      = timerOutputActionNone,
    timerCCInit.cofoa      = timerOutputActionNone,
    timerCCInit.cmoa       = timerOutputActionNone,
    timerCCInit.mode       = timerCCModeCompare,
    timerCCInit.filter     = true,
    timerCCInit.prsInput   = false,
    timerCCInit.coist      = false,
    timerCCInit.outInvert  = false,

    TIMER_InitCC(DELAY_HW_TIMER_MODULE, 0, &timerCCInit);

    /* Configure & start TIMER */
    TIMER_Init(DELAY_HW_TIMER_MODULE, &timerInit);

    TIMER_TopSet(DELAY_HW_TIMER_MODULE, 0xFFFF);

}

bool PDDDelayTimer_Delay_us(uint16_t duration_us) 
{
    return doActiveWaiting(duration_us);
}


bool PDDDelayTimer_Delay_ms(uint16_t duration_ms) 
{
    for(uint16_t i=0; i<1000; i++)
    {
        if(!doActiveWaiting(duration_ms))
            return false;
    }
    return true;
}


uint32_t PDDDelayTimer_GetMaxDelay_us() 
{
    uint32_t maxDelay_us;
    // max timer length = 16bit * prescaler / (Freq_in_MHz * 1000)

    maxDelay_us =(uint32_t) (65535ul * 16ul ) / (uint32_t) BSP_XTAL_FREQ_MHZ;
    return maxDelay_us;
}



