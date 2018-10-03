/*
 * USART.c
 *
 *  Created on: Oct 21, 2015
 *      Author: Yogev Modlin.
 */

/* Includes */
#include "USART.h"
#include "main.h"
#include <string.h>

/* ----------  Globals -----------  */
uint8_t USART1_Transmit_Buffer[USART_BUFFER_SIZE];
uint8_t USART1_Recieve_Buffer[PROTOCOL_PACKET_SIZE];
uint8_t Data_ready;

uint8_t uid_add;
uint8_t usart_error_cnt=0;

extern uint32_t Frequency ;
extern uint16_t RegularConvData_Tab[];
extern uint16_t Sine12bit[1] ;

void Send_Version(uint8_t uid_add, uint8_t cmd_id);

/* -------------------------------  */

/**
  * @brief  This function configures USART1.
  * @param  None
  * @retval None
  */
void Configure_USART1(void)
{
  /* Enable the peripheral clock USART1 */
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  /* GPIO configuration for USART1 signals */
	  /* (1) Select AF mode (10) on PA9 and PA10 */
	  /* (2) AF1 for USART1 signals */
	  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10))\
				   | (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1); /* (1) */
	  GPIOA->AFR[1] = (GPIOA->AFR[1] &~ (GPIO_AFRH_AFRH1 | GPIO_AFRH_AFRH2))\
					| (1 << (1 * 4)) | (1 << (2 * 4)); /* (2) */
  
	  /* Enable the peripheral clock of GPIOC */
	  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	  /* Configure PC15 as output port RS485_Direction */
	  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER15)) \
						  | (GPIO_MODER_MODER15_0);
	  GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;

  /* Configure USART1 */
  /* (1) oversampling by 16, 115200 baud */
  /* (2) Enable DMA in reception and transmission */
  /* (3) 8 data bit, 1 start bit, 1 stop bit, no parity, reception and transmission enabled */
  USART1->BRR = 480000 / 1152/*96*/; /* (1) */
  USART1->CR3 = USART_CR3_DMAT | USART_CR3_DMAR; /* (2) */
  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; /* (3) */

  while((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)/* polling idle frame Transmission */
  {
    /* add time out here for a robust application */
  }
  USART1->ICR |= USART_ICR_TCCF;/* Clear TC flag */
  USART1->CR1 |= USART_CR1_TCIE;/* Enable TC interrupt */
}

/**
  * @brief  This function configures DMA channels for USART1.
  *          Channel 2: Transmit.
  * 		 CHannel 3: Recieve.
  * @param  None
  * @retval None
  */
void Configure_USART1_DMA(void)
{
  /* Enable the peripheral clock DMA1 */
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  /* DMA1 Channel2 USART1_TX config */
  /* (1)  Peripheral address */
  /* (2)  Memory address */
  /* (3)  Memory increment */
  /*      Memory to peripheral */
  /*      8-bit transfer */
  /*      Transfer complete IT */
  DMA1_Channel2->CPAR = (uint32_t)&(USART1->TDR); /* (1) */
  DMA1_Channel2->CMAR = (uint32_t)USART1_Transmit_Buffer; /* (2) */
  DMA1_Channel2->CCR |= DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE; /* (3) */

  /* DMA1 Channel2 USART_RX config */
  /* (4)  Peripheral address */
  /* (5)  Memory address */
  /* (6)  Data size */
  /* (7)  Memory increment */
  /*      Peripheral to memory*/
  /*      8-bit transfer */
  /*      Transfer complete IT */
  DMA1_Channel3->CPAR = (uint32_t)&(USART1->RDR); /* (4) */
  DMA1_Channel3->CMAR = (uint32_t)USART1_Recieve_Buffer; /* (5) */
  DMA1_Channel3->CNDTR = PROTOCOL_PACKET_SIZE; /* (6) */
  DMA1_Channel3->CCR |= DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_EN; /* (7) */

  /* Configure IT */
  /* (8) Set priority for DMA1_Channel2_3_IRQn */
  /* (9) Enable DMA1_Channel2_3_IRQn */
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, UART_INT_PR); /* (8) */
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn); /* (9) */
}


void Send_Command(uint8_t uid_add, uint8_t cmd_id, uint32_t data)
{
	  /* Building the packet   */
	  USART1_Transmit_Buffer[0] = 75;               /* Sync Byte    */
	  USART1_Transmit_Buffer[1] = uid_add;          /* UID  Byte    */
	  USART1_Transmit_Buffer[2] = 4;                /* Length Byte  */
	  USART1_Transmit_Buffer[3] = cmd_id;           /* CMD Byte     */

	  memcpy(&USART1_Transmit_Buffer[4], &data, 4);  /*  Data Bytes   */

	  //flag_buffer |= PKT_SENT;
	  GPIOC->ODR |= (1<<15);    //Put logic '1' on PC15
	  DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	  DMA1_Channel2->CNDTR = PROTOCOL_PACKET_SIZE;
	  DMA1_Channel2->CCR |= DMA_CCR_EN;

}

void Send_Version(uint8_t uid_add, uint8_t cmd_id)
{
	/* Building the packet   */

	memset(USART1_Transmit_Buffer,0, 0);

	/* Building the packet   */
	USART1_Transmit_Buffer[0] = 75;               /* Sync Byte    */
	USART1_Transmit_Buffer[1] = uid_add;          /* UID  Byte    */
	USART1_Transmit_Buffer[2] = 4;                /* Length Byte  */
	USART1_Transmit_Buffer[3] = cmd_id;           /* CMD Byte     */

	USART1_Transmit_Buffer[4] = VERSION_P; 			  /* Sync Byte	  */
	USART1_Transmit_Buffer[5] = VERSION_L;		  /* UID  Byte	  */
	USART1_Transmit_Buffer[6] = VERSION_MD;				 /* Length Byte  */
	USART1_Transmit_Buffer[7] = VERSION_MS; 		  /* CMD Byte	  */

	DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	DMA1_Channel2->CNDTR = 4+4/*USART_BUFFER_SIZE*/;
	DMA1_Channel2->CCR |= DMA_CCR_EN;
	GPIOC->ODR |= (1<<15);    //Put logic '1' on PC15
}

void Reset(void)
{
	DMA_DeInit(DMA1_Channel3);
	DMA_DeInit(DMA1_Channel2);
	DMA_DeInit(DMA1_Channel1);
	TIM_DeInit(TIM2);
	USART_DeInit(USART1);
	ADC_DeInit(ADC1);
	NVIC_SystemReset();

}

void EDP_interperter()
{
uint32_t data;
//uint32_t temp_data;

	if (USART1_Recieve_Buffer[0] == 75 )
	{
		if (USART1_Recieve_Buffer[1] == uid_add)
		{
			usart_error_cnt=0;

			//memcpy(&temp_data, &USART1_Recieve_Buffer[4], 4);

			switch (USART1_Recieve_Buffer[3])
			{
				case PWM_ID:   /*  PWM reading     */
					Send_Command(uid_add, PWM_ID, (uint32_t)Frequency);
				break;
				case CMD_OUT_IO1:   /*  CMD OUT_IO1     */
					data=USART1_Recieve_Buffer[4];
					data|=USART1_Recieve_Buffer[5]<<8;
					data|=USART1_Recieve_Buffer[6]<<16;
					data|=USART1_Recieve_Buffer[7]<<24;
					set_io1(data);
					data=get_io1();
					Send_Command(uid_add, CMD_OUT_IO1, (uint32_t)data);
				break;
				case CMD_OUT_IO2:   /*  CMD OUT_IO2     */
					data=USART1_Recieve_Buffer[4];
					data|=USART1_Recieve_Buffer[5]<<8;
					data|=USART1_Recieve_Buffer[6]<<16;
					data|=USART1_Recieve_Buffer[7]<<24;
					set_io2(data);
					data=get_io2();
					Send_Command(uid_add, CMD_OUT_IO2, (uint32_t)data);
				break;
				case CMD_OUT_IO3:   /*  CMD OUT_IO3     */
					data=USART1_Recieve_Buffer[4];
					data|=USART1_Recieve_Buffer[5]<<8;
					data|=USART1_Recieve_Buffer[6]<<16;
					data|=USART1_Recieve_Buffer[7]<<24;
					set_io3(data);
					data=get_io3();
					Send_Command(uid_add, CMD_OUT_IO3, (uint32_t)data);
				break;
				case GET_IN_IO:
					data=get_in_io();
					Send_Command(uid_add, GET_IN_IO, (uint32_t)data);
					break;
				case GET_OUT_IO1:
					data=get_io1();
					Send_Command(uid_add, GET_OUT_IO1, (uint32_t)data);
					break;
				case SET_DAC:
					data=USART1_Recieve_Buffer[4];
					data|=USART1_Recieve_Buffer[5]<<8;
					data|=USART1_Recieve_Buffer[6]<<16;
					data|=USART1_Recieve_Buffer[7]<<24;
					
					DAC_SetChannel1Data(DAC_Align_12b_R,(uint16_t)data);
					Send_Command(uid_add, SET_DAC, (uint32_t)data);
					break;
				case GET_OUT_IO3:
					data=get_io3();
					Send_Command(uid_add, GET_OUT_IO3, (uint32_t)data);
					break;
				case SET_DEFAULT_IO:
					data=0;
					set_io_default();
					Send_Command(uid_add, SET_DEFAULT_IO, (uint32_t)data);
					break;
				case VERSION:
					Send_Version(uid_add, VERSION );
				break;
				case V_ADC1:
					Send_Command(uid_add, V_ADC1, (uint32_t)RegularConvData_Tab[0]);
				break;
				case V_ADC2:
					Send_Command(uid_add, V_ADC2, (uint32_t)RegularConvData_Tab[1]);
				break;
				case V_ADC3:
					Send_Command(uid_add, V_ADC3, (uint32_t)RegularConvData_Tab[2]);
				break;
				case V_ADC4:
					Send_Command(uid_add, V_ADC4, (uint32_t)RegularConvData_Tab[3]);
				break;
				case ADC_TEMP:
					Send_Command(uid_add, ADC_TEMP, (uint32_t)RegularConvData_Tab[4]);
				break;
				case RESET_ID:
					Reset();
				break;
				default:
					break;
			}
		}
	}
	else
	{
		if(usart_error_cnt>=3)
			Reset();
		usart_error_cnt++;
	}
}

