/**
 * @file PDDUsart.c
 * <!-----------------------------------------------------------------------.
 * @brief @ref REF ""
 *
 * @par Project:
 * <!-----------------------------------------------------------------------.
 * <!--
 * @par Description:
 *
 *  [Description]
 * -.
 * <!--
 *  @ref [extdocname] "more..."
 *  -.
 * <!-----------------------------------------------------------------------.
 * <!--
 * @remarks
 * - [...]
 * - [...]
 * -.
 * <!------------------------------------------------------------------------
 * Copyright (c) 2011
 * IMST GmbH
 * Carl-Friedrich Gauss Str. 2
 * 47475 Kamp-Lintfort
 * -------------------------------------------------------------------------.
 * @author Frank Brey (FB), IMST
 * <!------------------------------------------------------------------------
 * Target OS:    none
 * Target CPU:   EFM32
 * Compiler:     IAR C/C++ Compiler
 * -------------------------------------------------------------------------.
 * @internal
 * @par Revision History:
 * <PRE>
 * ---------------------------------------------------------------------------
 * Version | Date       | Author | Comment
 * ---------------------------------------------------------------------------
 * 0.1     | 18.10.2012 | FB     | Created
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
#include "bsp.h"
#include "PDDUsart.h"


//------------------------------------------------------------------------------
// local variables
//------------------------------------------------------------------------------

TPddUsartControlBlock PddUsart_Data;



//------------------------------------------------------------------------------
// private functions
//------------------------------------------------------------------------------

static uint32_t efm32_PDDUsart_ConvertDataRate(TUsartBaudrate dr) 
{
    uint32_t result;
    switch (dr) 
    {
      case BAUDRATE_9600:
          result = 9600;
          break;
      case BAUDRATE_19200:
          result = 19200;
          break;
      case BAUDRATE_38400:
          result = 38400;
          break;
      case BAUDRATE_57600:
          result = 57600;
          break;
      case BAUDRATE_115200:
          result = 115200;
          break;
      case BAUDRATE_125K0:
          result = 125000;
          break;
      default:
          result = 38400;
          break;
    }
    return result;
}
          
          

          

//------------------------------------------------------------------------------
// public functions
//------------------------------------------------------------------------------



TPddUsartControlBlock* PDDUsart_GetControlblock() 
{
    return &PddUsart_Data;
}




//! Init Usart Interface
void PDDUsart_Init() 
{
    PddUsart_Data.RxByteIndication     = NULL;
    PddUsart_Data.TxByteIndication     = NULL;
    PddUsart_Data.TxFinishedIndication = NULL;

    PddUsart_Data.efm32Spd.Usart = BSP_USART_INTERFACE;

    PddUsart_Data.efm32Spd.UsartInit.enable       = usartDisable;               /* Don't enable UART upon intialization */
    PddUsart_Data.efm32Spd.UsartInit.refFreq      = 0;                          /* Use current configured reference clock for configuring baudrate. */
    PddUsart_Data.efm32Spd.UsartInit.baudrate     = efm32_PDDUsart_ConvertDataRate(PDDUSART_DEFAULT_DATARATE);           /* 115200 baud/s */
    PddUsart_Data.Baudrate                        = PDDUSART_DEFAULT_DATARATE;
    PddUsart_Data.efm32Spd.UsartInit.oversampling = usartOVS16;                 /* 16x oversampling. */
    PddUsart_Data.efm32Spd.UsartInit.databits     = usartDatabits8;             /* 8 databits. */
    PddUsart_Data.efm32Spd.UsartInit.parity       = usartNoParity;              /* No parity. */
    PddUsart_Data.efm32Spd.UsartInit.stopbits     = usartStopbits1;             /* 1 stopbit. */
    PddUsart_Data.efm32Spd.UsartInit.mvdis        = false;                      /* Do not disable majority vote. */
    PddUsart_Data.efm32Spd.UsartInit.prsRxEnable  = false;                      /* Not USART PRS input mode. */
    PddUsart_Data.efm32Spd.UsartInit.prsRxCh      = usartPrsRxCh0;              /* PRS channel 0. */

    /* Enable clock for HF peripherals */
    CMU_ClockEnable(cmuClock_HFPER, true);

    /* Enable clock for USART module */
    CMU_ClockEnable(BSP_USART_CLOCK_MODULE, true);

    /* Enable clock for GPIO module (required for pin configuration) */
    CMU_ClockEnable(cmuClock_GPIO, true);
  
    /* Configure GPIO pins */
    GPIO_PinModeSet(BSP_USART_GPIO_TX_PIN_PORT,
                    BSP_USART_GPIO_TX_PIN_NR,
                    gpioModePushPull, 0x01);
    GPIO_PinModeSet(BSP_USART_GPIO_RX_PIN_PORT,
                    BSP_USART_GPIO_RX_PIN_NR,
                    gpioModeInput, 0);
  
    /* Init USART registers to HW reset state. */
    USART_Reset(PddUsart_Data.efm32Spd.Usart);

    /* Initialize USART with uartInit struct */
    USART_InitAsync(PddUsart_Data.efm32Spd.Usart, &PddUsart_Data.efm32Spd.UsartInit);

    /* Prepare UART Rx and Tx interrupts */
    USART_IntClear(PddUsart_Data.efm32Spd.Usart, BSP_USART_IF_CLEAR_MASK);
    USART_IntEnable(PddUsart_Data.efm32Spd.Usart, BSP_USART_IF_RXDATAV);
    NVIC_ClearPendingIRQ(BSP_USART_RX_IRQ_VEC);
    NVIC_ClearPendingIRQ(BSP_USART_TX_IRQ_VEC);
    NVIC_EnableIRQ(BSP_USART_RX_IRQ_VEC);
    NVIC_EnableIRQ(BSP_USART_TX_IRQ_VEC);

    /* Enable I/O pins for selected UART at selected  location */
    PddUsart_Data.efm32Spd.Usart->ROUTE = BSP_USART_RX_ROUTE_EN | BSP_USART_TX_ROUTE_EN | BSP_USART_LOCATION;

    /* Enable UART */
    USART_Enable(BSP_USART_INTERFACE, usartEnable);
}




//! Register Callback Functions for LoRa
void PDDUsart_RegisterClient(TPddUsartControlBlock * usartCtrlBlock,
                             TUsartCbRxByteIndication cbRxByteIndication,
                             TUsartCbTxByteIndication cbTxByteIndication) 
{
    if (usartCtrlBlock)
    {
        if(cbRxByteIndication)
            usartCtrlBlock->RxByteIndication = cbRxByteIndication;
        if(cbTxByteIndication)
            usartCtrlBlock->TxByteIndication = cbTxByteIndication;
    }
}

//! Send Single Byte
void PDDUsart_SendByte(TPddUsartControlBlock * usartCtrlBlock, uint8_t txByte) 
{
    if (usartCtrlBlock) 
    {
        USART_Tx(usartCtrlBlock->efm32Spd.Usart,  txByte);
    }
}

                    

//! Enable transmission interrupt
void PDDUsart_TXINT_Enable      (TPddUsartControlBlock * usartCtrlBlock) 
{
    if (usartCtrlBlock) 
    {
        /* Enable interrupt on USART TX Buffer*/
        USART_IntEnable(usartCtrlBlock->efm32Spd.Usart, BSP_USART_TX_IF_FLAG); // this flag is common to all interfaces
    }
}

//! Disable transmission interrupt
void PDDUsart_TXINT_Disable     (TPddUsartControlBlock * usartCtrlBlock) 
{
    if (usartCtrlBlock) 
    {
        /* Disable interrupt on USART TX Buffer*/
        USART_IntDisable(usartCtrlBlock->efm32Spd.Usart, BSP_USART_TX_IF_FLAG); // this flag is common to all interfaces
    }
}


//! Start interrupt supported transmission
bool PDDUsart_StartTransmission (TPddUsartControlBlock * usartCtrlBlock) 
{
    if (usartCtrlBlock && usartCtrlBlock->TxByteIndication) 
    {
        PDDUsart_TXINT_Enable(usartCtrlBlock);
        return true;
    }
    return false;
}





//------------------------------------------------------------------------------
// Hardware IRQs
//------------------------------------------------------------------------------



/**************************************************************************//**
 * @brief RX IRQ Handler
 *
 *****************************************************************************/
void BSP_USART_IRQ_HANDLER_RX(void) 
{
    uint8_t rxData;
    /* Check for RX data valid interrupt */
    if (BSP_USART_INTERFACE->STATUS & BSP_USART_RX_DATA_FLAG) 
    {
        /* Copy data into RX Buffer */
        rxData = USART_Rx(BSP_USART_INTERFACE);
        if (PddUsart_Data.RxByteIndication) 
        {
            PddUsart_Data.RxByteIndication(rxData);
        }
        /* Clear RXDATAV interrupt */
        USART_IntClear(BSP_USART_INTERFACE, BSP_USART_RX_DATA_FLAG);
    }
}

/**************************************************************************//**
 * @brief TX IRQ Handler
 *
 *****************************************************************************/
void BSP_USART_IRQ_HANDLER_TX(void) 
{
    uint32_t irqFlags = USART_IntGet(BSP_USART_INTERFACE);
    int16_t tmp;

    /* Check TX buffer level status */
    if (BSP_USART_INTERFACE->STATUS & BSP_USART_TX_STATUS_FLAG) 
    {
        tmp = -1; // EOF
        if (PddUsart_Data.TxByteIndication) 
        {
            tmp = PddUsart_Data.TxByteIndication();
        }

        /* Disable Tx interrupt if no more bytes in queue */
        if (tmp < 0) 
        {
            USART_IntDisable(BSP_USART_INTERFACE, BSP_USART_TX_IF_FLAG);
        } 
        else 
        {
            /* send the next TX byte */
            USART_Tx(BSP_USART_INTERFACE, tmp);
        }
    }
}


//------------------------------------------------------------------------------
// private functions
//------------------------------------------------------------------------------


