/*
 * USART.h
 *
 *  Created on: Oct 21, 2015
 *      Author: Yogev
 */

#ifndef USART_H_
#define USART_H_

/* Includes */
#include "stm32f0xx.h"

/*------   Msg id ------*/
#define USART_BUFFER_SIZE     20
#define PROTOCOL_PACKET_SIZE  8
#define USART_DELAY 		  2000
#define MASTER_ID             0

/*#define PWM_ID				1
#define VERSION       		2
#define VIN_VOUT            3
#define ADC_TEMP            4*/
#define STATUS_ID			0
#define PWM_ID				1
#define CMD_OUT_IO1			2
#define CMD_OUT_IO2			3
#define GET_IN_IO			4
#define CMD_OUT_IO3         5
#define GET_OUT_IO1     	6
#define SET_DAC       		7
#define GET_OUT_IO3        	8
#define SET_DEFAULT_IO 		9
#define VERSION       		10
#define RESET_ID			11
#define ERRORS				12
#define CLR_ERROR           13
#define OC_PROTECTION       14
#define V_ADC1            	15
#define V_ADC2            	16
#define V_ADC3            	17
#define V_ADC4            	18
#define ADC_TEMP            19

#define ADD_ACK             252

/*----- CAN macros  ---------*/
#define CAN_ID_MASK (0xFF70U)
#define CAN_ID1 (0x651U)
#define CAN_ID2 (0x652U)
#define FILTER_LIST (0) /* 0: filter mode = identifier mask, 1: filter mode = identifier list */


/*--     Globals Vars       --*/
extern uint8_t USART1_Transmit_Buffer[USART_BUFFER_SIZE];
extern uint8_t USART1_Recieve_Buffer[PROTOCOL_PACKET_SIZE];
extern uint8_t Data_ready;
extern uint8_t uid_add;

/*--  Functions     --*/
void Configure_USART1(void);
void Configure_USART1_DMA(void);
void Send_Command(uint8_t uid_add, uint8_t cmd_id, uint32_t data);
void EDP_interperter();
void Reset(void);

#endif /* USART_H_ */
