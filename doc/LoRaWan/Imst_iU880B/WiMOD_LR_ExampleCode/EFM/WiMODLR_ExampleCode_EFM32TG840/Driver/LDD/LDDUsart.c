/**
 * @file LDDUsart.c
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
 * 0.1     | 21.08.2012 | FB     | Created
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
//
// Include Files
//
//------------------------------------------------------------------------------

#include "LDDUsart.h"
#include "PDDUsart.h"


static TLddUsartControlBlock    usartCntrlBlk;




//-----------------------------------------------------------------------------
// private functions
//-----------------------------------------------------------------------------

static int16_t LDDUsart_TXBuffer_GetNextTxByte(TLddUsartControlBlock * usartCntrlBlkPtr)
{
    int16_t result = EOF;

    if (usartCntrlBlkPtr) 
    {
        /* Check if all data is transmitted. */
        uint8_t tempTX_Tail = usartCntrlBlkPtr->RingBuffer.TX_Tail;

        if (usartCntrlBlkPtr->RingBuffer.TX_Head == tempTX_Tail)
        {
            // no further data to be send
            result = EOF;
        }
        else
        {
            // get the next tx bye
            result = usartCntrlBlkPtr->RingBuffer.TX[usartCntrlBlkPtr->RingBuffer.TX_Tail];

            /* Advance buffer tail. */
            usartCntrlBlkPtr->RingBuffer.TX_Tail =
                    (usartCntrlBlkPtr->RingBuffer.TX_Tail + 1) & USART_TX_BUFFER_MASK;
        }
    }

    return result;
}


static void LDDUsart_RxByteIndication(uint8_t  rxByte) 
{    
    (*usartCntrlBlk.RxByteIndication)(rxByte);
}


static inline int16_t LDDUsart_TxByteIndication(void) 
{
    // get the next char out of the ring buffer
    return LDDUsart_TXBuffer_GetNextTxByte(&usartCntrlBlk);
}




//------------------------------------------------------------------------------
// public available Functions
//------------------------------------------------------------------------------



//! Initialize USART
void LDDUsart_Init(void) 
{
    usartCntrlBlk.PddUsartControlBlock = PDDUsart_GetControlblock();

    PDDUsart_Init();
    
    PDDUsart_RegisterClient(usartCntrlBlk.PddUsartControlBlock, LDDUsart_RxByteIndication, LDDUsart_TxByteIndication);
    

    usartCntrlBlk.RingBuffer.RX_Head =  0;
    usartCntrlBlk.RingBuffer.RX_Tail =  0;
    usartCntrlBlk.RingBuffer.TX_Head =  0;
    usartCntrlBlk.RingBuffer.TX_Tail =  0;

    usartCntrlBlk.TxByteIndication     = NULL;
    usartCntrlBlk.RxByteIndication     = NULL;
    usartCntrlBlk.TxFinishedIndication = NULL;
}


// Register RX Callback Function
void LDDUsart_RegisterClient(TUsartCbRxByteIndication cbRxByteIndication) 
{
    usartCntrlBlk.RxByteIndication = cbRxByteIndication;
}



//! Send Single Byte
void LDDUsart_SendByte(uint8_t txByte) 
{
    PDDUsart_SendByte(usartCntrlBlk.PddUsartControlBlock, txByte);
}








