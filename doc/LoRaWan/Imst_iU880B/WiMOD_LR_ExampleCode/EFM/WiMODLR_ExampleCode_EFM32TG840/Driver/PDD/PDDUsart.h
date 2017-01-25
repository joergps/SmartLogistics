/**
 * @file PDDUsart.h
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


#ifndef PDDUSART_H_
#define PDDUSART_H_

//------------------------------------------------------------------------------
// public needed include files
//------------------------------------------------------------------------------

#include "bsp.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"


//------------------------------------------------------------------------------
// public available Constants and Macros
//------------------------------------------------------------------------------

/* \brief  Receive buffer size: 2,4,8,16,32,64,128 or 256 bytes. */
#define USART_RX_BUFFER_SIZE 256
/* \brief Transmit buffer size: 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 256


/* \brief Receive buffer mask. */
#define USART_RX_BUFFER_MASK ( USART_RX_BUFFER_SIZE - 1 )
/* \brief Transmit buffer mask. */
#define USART_TX_BUFFER_MASK ( USART_TX_BUFFER_SIZE - 1 )


#if ( USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK )
    #error RX buffer size is not a power of 2
#endif
#if ( USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK )
    #error TX buffer size is not a power of 2
#endif

//------------------------------------------------------------------------------
// public available Data Types
//------------------------------------------------------------------------------

//! Enumeration Type for Baudrates
typedef enum 
{
    BAUDRATE_9600 = 0,
    BAUDRATE_19200,
    BAUDRATE_38400,
    BAUDRATE_57600,
    BAUDRATE_115200,
    BAUDRATE_125K0,
} TUsartBaudrate;


//***********************************************
// TUsartCbRxByteIndication
//-----------------------------------------------
//! @brief: Type for RX Interrupt Callback Function
//! <!------------------------------------------->
//! @param[in]    rxyte     Received Byte
//***********************************************

typedef void (*TUsartCbRxByteIndication)(uint8_t rxyte);

//***********************************************
// TUsartCbTxByteIndication
//-----------------------------------------------
//! @brief: Type for TX Interrupt Callback Function
//! <!------------------------------------------->
//! @retval       INT16        >=0: next character to be sent<br>
//!                            <0:  no further character in queue
//************************************************

typedef int16_t (*TUsartCbTxByteIndication)(void);
typedef void    (*TUsartCbTxFinishedIndication)(void);


typedef struct efm32UsartT 
{
    USART_TypeDef*          Usart;
    USART_InitAsync_TypeDef UsartInit;
} TEFM32_USART;


/* \brief USART transmit and receive ring buffer. */
typedef struct USART_Buffer
{
    /* \brief Receive buffer. */
    volatile uint8_t RX[USART_RX_BUFFER_SIZE];
    /* \brief Transmit buffer. */
    volatile uint8_t TX[USART_TX_BUFFER_SIZE];
    /* \brief Receive buffer head. */
    volatile uint8_t RX_Head;
    /* \brief Receive buffer tail. */
    volatile uint8_t RX_Tail;
    /* \brief Transmit buffer head. */
    volatile uint8_t TX_Head;
    /* \brief Transmit buffer tail. */
    volatile uint8_t TX_Tail;
} USART_Buffer_t;


typedef struct PddUsartControlBlock 
{
    TUsartBaudrate               Baudrate;
    TUsartCbRxByteIndication     RxByteIndication;
    TUsartCbTxByteIndication     TxByteIndication;
    TUsartCbTxFinishedIndication TxFinishedIndication;

    // platform specific data
    TEFM32_USART                efm32Spd;

} TPddUsartControlBlock;



//------------------------------------------------------------------------------
// public available Function Prototypes
//------------------------------------------------------------------------------

TPddUsartControlBlock* PDDUsart_GetControlblock();

void PDDUsart_Init(void);

void PDDUsart_RegisterClient(TPddUsartControlBlock * usartCtrlBlock,
                             TUsartCbRxByteIndication cbRxByteIndication,
                             TUsartCbTxByteIndication cbTxByteIndication);


//! Send Single Byte
void PDDUsart_SendByte          (TPddUsartControlBlock * usartCtrlBlock,
                                uint8_t txByte);

//! Enable transmission interrupt
void PDDUsart_TXINT_Enable      (TPddUsartControlBlock * usartCtrlBlock);

//! Disable transmission interrupt
void PDDUsart_TXINT_Disable     (TPddUsartControlBlock * usartCtrlBlock);

//! Start interrupt supported transmission
bool PDDUsart_StartTransmission (TPddUsartControlBlock * usartCtrlBlock);


//------------------------------------------------------------------------------
// private available Constants and Macros
//------------------------------------------------------------------------------

#define PDDUSART_DEFAULT_DATARATE           BAUDRATE_115200



//------------------------------------------------------------------------------



#endif /* PDDUSART_H_ */
