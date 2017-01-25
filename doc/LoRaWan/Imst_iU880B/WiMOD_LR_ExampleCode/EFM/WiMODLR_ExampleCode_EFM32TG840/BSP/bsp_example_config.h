/**
 * @file bsp_example_config.h
 * <!------------------------------------------------------------------------>
 * @brief @ref REF "Board Support Package (BSP)"
 *
 * @par Project:
 * <!------------------------------------------------------------------------>
 * <!--
 * @par Description:
 *
 * Port and Peripheral Assignments for LoRa specific board.
 *
 * <!------------------------------------------------------------------------>
 * <!--
 * @remarks
 * - [...]
 * - [...]
 * -->
 * <!------------------------------------------------------------------------
 * Copyright (c) 2015
 * IMST GmbH
 * Carl-Friedrich Gauss Str. 2
 * 47475 Kamp-Lintfort
 * -------------------------------------------------------------------------->
 * @author Mathias Hater (MH), IMST
 * <!------------------------------------------------------------------------
 * Target OS:    independent
 * Target CPU:   EFM32
 * Compiler:     IAR C/C++ Compiler
 * -------------------------------------------------------------------------->
 * @internal
 * @par Revision History:
 * <PRE>
 * ---------------------------------------------------------------------------
 * Version | Date       | Author | Comment
 * ---------------------------------------------------------------------------
 * 0.1     | 2015-01-22 | MH     |  initial version
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



#ifndef BSP_EXAMPLE_CONFIG_H_
#define BSP_EXAMPLE_CONFIG_H_


//------------------------------------------------------------------------------
//
// Section Oscillator & Frequency Settings
//
//------------------------------------------------------------------------------

#define BSP_XTAL_FREQ_MHZ               ( 48 )
#define BSP_XTAL_FREQ_HZ                ( 48000000UL )



//------------------------------------------------------------------------------
//
// Section RF Transceiver
//
//------------------------------------------------------------------------------

// UART0 

#define BSP_USART_INTERFACE                 USART0

#define BSP_USART_LOCATION                  USART_ROUTE_LOCATION_LOC0

#define BSP_USART_CLOCK_MODULE              cmuClock_USART0

#define BSP_USART_GPIO_TX_PIN_PORT          gpioPortE
#define BSP_USART_GPIO_TX_PIN_NR            10

#define BSP_USART_GPIO_RX_PIN_PORT          gpioPortE
#define BSP_USART_GPIO_RX_PIN_NR            11

#define BSP_USART_RX_IRQ_VEC                USART0_RX_IRQn
#define BSP_USART_TX_IRQ_VEC                USART0_TX_IRQn

#define BSP_USART_IRQ_HANDLER_RX            USART0_RX_IRQHandler
#define BSP_USART_IRQ_HANDLER_TX            USART0_TX_IRQHandler

#define BSP_USART_TX_IF_FLAG                USART_IF_TXBL
#define BSP_USART_TX_STATUS_FLAG            USART_STATUS_TXBL
#define BSP_USART_RX_DATA_FLAG              USART_STATUS_RXDATAV

#define BSP_USART_IF_CLEAR_MASK             _USART_IF_MASK
#define BSP_USART_IF_RXDATAV                USART_IF_RXDATAV

#define BSP_USART_RX_ROUTE_EN               USART_ROUTE_RXPEN
#define BSP_USART_TX_ROUTE_EN               USART_ROUTE_TXPEN



#endif
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------

