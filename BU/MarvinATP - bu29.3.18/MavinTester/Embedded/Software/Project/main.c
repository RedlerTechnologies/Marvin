/**
  ******************************************************************************
  * @file    TIM_PWM_Input/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "USART.h"
#include "stm32f0xx_gpio.h"

/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup TIM_PWM_Input
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address                0x40012440
#define BSRR_VAL1        				0x0200
#define BSRR_VAL2        				0x0100


#define   ADC_ENABLE

//__________PA____________________________________

#define PA0_ON (GPIOA->BSRR |= GPIO_Pin_0)	  
#define PA0_OFF (GPIOA->BRR |= GPIO_Pin_0)	  

#define PA1_ON (GPIOA->BSRR |= GPIO_Pin_1)	  
#define PA1_OFF (GPIOA->BRR |= GPIO_Pin_2)	  

#define PA2_ON (GPIOA->BSRR |= GPIO_Pin_2)	  
#define PA2_OFF (GPIOA->BRR |= GPIO_Pin_2)	  

#define PA3_ON (GPIOA->BSRR |= GPIO_Pin_3)	  
#define PA3_OFF (GPIOA->BRR |= GPIO_Pin_3)	  

#define PA4_ON (GPIOA->BSRR |= GPIO_Pin_4)	  
#define PA4_OFF (GPIOA->BRR |= GPIO_Pin_4)	  

#define PA5_ON (GPIOA->BSRR |= GPIO_Pin_5)	  
#define PA5_OFF (GPIOA->BRR |= GPIO_Pin_5)	

#define PA6_ON (GPIOA->BSRR |= GPIO_Pin_6)	  
#define PA6_OFF (GPIOA->BRR |= GPIO_Pin_6)

#define PA7_ON (GPIOA->BSRR |= GPIO_Pin_7)	  
#define PA7_OFF (GPIOA->BRR |= GPIO_Pin_7)

#define PA13_ON (GPIOA->BSRR |= GPIO_Pin_13)	  
#define PA13_OFF (GPIOA->BRR |= GPIO_Pin_13)

#define PA14_ON (GPIOA->BSRR |= GPIO_Pin_14)	  
#define PA14_OFF (GPIOA->BRR |= GPIO_Pin_14)

#define PA15_ON (GPIOA->BSRR |= GPIO_Pin_15)	  
#define PA15_OFF (GPIOA->BRR |= GPIO_Pin_15)

//__________PB____________________________________
#define PB0_ON (GPIOB->BSRR |= GPIO_Pin_0)	  
#define PB0_OFF (GPIOB->BRR |= GPIO_Pin_0)	  

#define PB1_ON (GPIOB->BSRR |= GPIO_Pin_1)	  
#define PB1_OFF (GPIOB->BRR |= GPIO_Pin_2)	  

#define PB2_ON (GPIOB->BSRR |= GPIO_Pin_2)	  
#define PB2_OFF (GPIOB->BRR |= GPIO_Pin_2)	  

#define PB3_ON (GPIOB->BSRR |= GPIO_Pin_3)	  
#define PB3_OFF (GPIOB->BRR |= GPIO_Pin_3)	  

#define PB4_ON (GPIOB->BSRR |= GPIO_Pin_4)	  
#define PB4_OFF (GPIOB->BRR |= GPIO_Pin_4)	  

#define PB5_ON (GPIOB->BSRR |= GPIO_Pin_5)	  
#define PB5_OFF (GPIOB->BRR |= GPIO_Pin_5)	

#define PB6_ON (GPIOB->BSRR |= GPIO_Pin_6)	  
#define PB6_OFF (GPIOB->BRR |= GPIO_Pin_6)

#define PB7_ON (GPIOB->BSRR |= GPIO_Pin_7)	  
#define PB7_OFF (GPIOB->BRR |= GPIO_Pin_7)

//__________PC____________________________________

#define PC0_ON (GPIOC->BSRR |= GPIO_Pin_0)	  
#define PC0_OFF (GPIOC->BRR |= GPIO_Pin_0)	  

#define PC1_ON (GPIOC->BSRR |= GPIO_Pin_1)	  
#define PC1_OFF (GPIOC->BRR |= GPIO_Pin_2)	  

#define PC2_ON (GPIOC->BSRR |= GPIO_Pin_2)	  
#define PC2_OFF (GPIOC->BRR |= GPIO_Pin_2)	  

#define PC3_ON (GPIOC->BSRR |= GPIO_Pin_3)	  
#define PC3_OFF (GPIOC->BRR |= GPIO_Pin_3)	  

#define PC4_ON (GPIOC->BSRR |= GPIO_Pin_4)	  
#define PC4_OFF (GPIOC->BRR |= GPIO_Pin_4)	  

#define PC5_ON (GPIOC->BSRR |= GPIO_Pin_5)	  
#define PC5_OFF (GPIOC->BRR |= GPIO_Pin_5)	

#define PC10_ON (GPIOC->BSRR |= GPIO_Pin_10)	  
#define PC10_OFF (GPIOC->BRR |= GPIO_Pin_10)

#define PC11_ON (GPIOC->BSRR |= GPIO_Pin_11)	  
#define PC11_OFF (GPIOC->BRR |= GPIO_Pin_11)

#define PC12_ON (GPIOC->BSRR |= GPIO_Pin_12)	  
#define PC12_OFF (GPIOC->BRR |= GPIO_Pin_12)	

//__________PD____________________________________

#define PD2_ON (GPIOD->BSRR |= GPIO_Pin_2)	  
#define PD2_OFF (GPIOD->BRR |= GPIO_Pin_2)	

//__________PF____________________________________

#define PF4_ON (GPIOF->BSRR |= GPIO_Pin_4)	  
#define PF4_OFF (GPIOF->BRR |= GPIO_Pin_4)	  

#define PF5_ON (GPIOF->BSRR |= GPIO_Pin_5)	  
#define PF5_OFF (GPIOF->BRR |= GPIO_Pin_5)	

#define PF6_ON (GPIOF->BSRR |= GPIO_Pin_6)	  
#define PF6_OFF (GPIOF->BRR |= GPIO_Pin_6)

#define PF7_ON (GPIOF->BSRR |= GPIO_Pin_7)	  
#define PF7_OFF (GPIOF->BRR |= GPIO_Pin_7)

#define PC8_ON (GPIOC->BSRR |= GPIO_Pin_8)	  
#define PC8_OFF (GPIOC->BRR |= GPIO_Pin_8)	 

#define POWER_ON (GPIOB->BSRR |= GPIO_Pin_11)	  
#define POWER_OFF (GPIOB->BRR |= GPIO_Pin_1)	  

#define ADC_TIMEOUT          1000
#define DAC_DHR12R_Address      0x40007408

GPIO_TypeDef* GPIOCMD1_PORT[28] =     {GPIOB		,GPIOB		,GPIOB		,GPIOB		,GPIOB		,GPIOB		,GPIOB		,GPIOC		,GPIOC		,GPIOC		,GPIOA		,GPIOF		,GPIOF		,GPIOA		,GPIOB     	,GPIOB      ,GPIOB		,GPIOC		,GPIOC		,GPIOB			,GPIOB		};
const uint16_t GPIOCMD1_PIN[28] =     {GPIO_Pin_9	,GPIO_Pin_8	,GPIO_Pin_7	,GPIO_Pin_6	,GPIO_Pin_5	,GPIO_Pin_4	,GPIO_Pin_3	,GPIO_Pin_12,GPIO_Pin_11,GPIO_Pin_10,GPIO_Pin_15,GPIO_Pin_7	,GPIO_Pin_6,GPIO_Pin_12 ,GPIO_Pin_13, GPIO_Pin_14,GPIO_Pin_15,GPIO_Pin_6 ,GPIO_Pin_7	,GPIO_Pin_10	,GPIO_Pin_11	};
const uint16_t GPIOCMD1_PINMODE[28] = {  9*2		,8*2		,7*2		,6*2		,5*2		,4*2		,3*2		,12*2		,11*2		,10*2		,15*2		,7*2		,6*2		,12*2 		,13*2		  	,14*2	     ,15*2		 ,6*2 		 ,7*2		 ,10*2			,11*2		};

GPIO_TypeDef* GPIOCMD2_PORT[6] = 	{GPIOB     	,GPIOB      ,GPIOB		,GPIOC		,GPIOC		,GPIOB				};
const uint16_t GPIOCMD2_PIN[6] = 	{GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_0 ,GPIO_Pin_1	,GPIO_Pin_2	,GPIO_Pin_10    };
const uint16_t GPIOCMD2_PINMODE[6] ={4*2		,5*2		,0*2 	   ,1*2		     ,2*2		,10*2    		};
uint16_t Sine12bit[1] = {0};

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_ICInitTypeDef  TIM_ICInitStructure;
__IO uint32_t TempSensVoltmv = 0, VrefIntVoltmv = 0;
__IO uint16_t RegularConvData_Tab[5];
static __IO uint32_t TimingDelay;

extern uint8_t Data_ready;
/* Private function prototypes -----------------------------------------------*/
void ADC1_CH_DMA_Config(void);
void TIM_Config(void);
void Delay(__IO uint32_t nTime);
void IO_Init(void);
void DAC_Config(void);
void DMA_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f0xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f0xx.c file
	*/
	IO_Init();
	/* Initialize Leds mounted on STM32F0-discovery */
	STM_EVAL_LEDInit(LED3);

	/* Turn on LED3 and LED4 */
	STM_EVAL_LEDOn(LED3);

	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
	#ifdef ADC_ENABLE
	/* ADC1 channel with DMA configuration */
	ADC1_CH_DMA_Config();
	#endif
	
	#ifdef PWM_ENABLE
	/* TIM Configuration */
	TIM_Config();

	/* --------------------------------------------------------------------------- 
	TIM2 configuration: PWM Input mode

	In this example TIM2 input clock (TIM2CLK) is set to APB1 clock (PCLK1)   
	TIM2CLK = PCLK1 
	=> TIM2CLK = HCLK = SystemCoreClock

	External Signal Frequency = TIM2 counter clock / TIM2_CCR2 in Hz. 

	External Signal DutyCycle = (TIM2_CCR1*100)/(TIM2_CCR2) in %.

	--------------------------------------------------------------------------- */

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);

	/* Select the TIM2 Input Trigger: TI2FP2 */
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

	/* Select the slave Mode: Reset Mode */
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);

	/* TIM enable counter */
	TIM_Cmd(TIM2, ENABLE);

	/* Enable the CC2 Interrupt Request */
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	#endif

	/* DAC configuration ------------------------------------------------------*/
	DAC_Config();

	Configure_USART1_DMA();
	Configure_USART1();
	POWER_ON;

  /* Infinite loop */
  while (1)
  {
		/* Toggle LED4 */
		STM_EVAL_LEDToggle(LED4);

		/* Insert 50 ms delay */
		Delay(50);

		/* Toggle LED3 */
		STM_EVAL_LEDToggle(LED3);

		if (Data_ready)
		{
			Data_ready = 0;
			EDP_interperter();
		}
		/* Insert 100 ms delay */
		Delay(50);
		}
}

/**
  * @brief  Configure the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* TIM2 chennel2 configuration : PA.01 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2);
  
  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  ADC1 channel with DMA configuration
  * @param  None
  * @retval None
  */
void ADC1_CH_DMA_Config(void)
{
  ADC_InitTypeDef     ADC_InitStructure;
  DMA_InitTypeDef     DMA_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  uint32_t ADC_TimeOut=0;
  
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* (1) Enable the peripheral clock of the ADC */
  /* (2) Start HSI14 RC oscillator */
  /* (3) Wait HSI14 is ready */
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; /* (1) */
  RCC->CR2 |= RCC_CR2_HSI14ON; /* (2) */
  while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) /* (3) */
  {
		if ((++ADC_TimeOut) > ADC_TIMEOUT)
		{
			return;
		}
  }

  /* Configure ADC Channel11 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);

  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
 
  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_55_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SampleTime_55_5Cycles);   
  ADC_ChannelConfig(ADC1, ADC_Channel_3 , ADC_SampleTime_55_5Cycles);   
  ADC_ChannelConfig(ADC1, ADC_Channel_6 , ADC_SampleTime_55_5Cycles);   
  ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles); 

  ADC_VrefintCmd(ENABLE);
  ADC_TempSensorCmd(ENABLE);
  
  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 5;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}
/**
  * @brief  Configures DAC channel 1
  * @param  None
  * @retval None
  */
void DAC_Config(void)
{
  DAC_InitTypeDef   DAC_InitStructure;
 // DMA_InitTypeDef   DMA_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable GPIOA Periph clock --------------------------------------*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure PA.04 DAC_OUT as analog */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  /* Fill DAC InitStructure */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

  /* DAC channel1 Configuration */
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is 
     automatically connected to the DAC converter. */
  DAC_Cmd(DAC_Channel_1, ENABLE);

  /* Enable DMA for DAC Channel2 */
  //DAC_DMACmd(DAC_Channel_1, ENABLE);
  
  DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}
/**
  * @brief  Configures DMA1 channel3
  * @param  None
  * @retval None
  */
void DMA_Config(void)
{
  DMA_InitTypeDef   DMA_InitStructure;

  /* Enable DMA1 clock -------------------------------------------------------*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  DMA_DeInit(DMA1_Channel3);
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Sine12bit;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);

  /* Enable DMA1 Channel3 */
  DMA_Cmd(DMA1_Channel3, ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
/**
  * @brief  Configures IO GPIO.
  * @param  Led: Specifies the IO to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void IO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  	/* Enable the GPIOA Clock */
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOD|RCC_AHBPeriph_GPIOF, ENABLE);

	/* Configure the GPIO A pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure the GPIO B pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure the GPIO C pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	/* Configure the GPIO D pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* Configure the GPIO F pin */
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	
}

void set_io1 (uint32_t data)
{
	int idx,j=0;
	//uint32_t pinpos=0;

	for(idx=0;idx<28;idx++)
	{
        if((data&(1<<idx))==((uint32_t)1<<idx))//ON
		{
			/*pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			GPIOCMD1_PORT[j]->MODER  |= (0x01 << (pinpos)); */  // output mode

			GPIOCMD1_PORT[j]->BSRR |= GPIOCMD1_PIN[j];
		}
		else if ((data&(1<<idx))==(0<<idx))//OFF
		{
			/*pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			GPIOCMD1_PORT[j]->MODER  |= (0x01 << (pinpos)); */ // output mode

			GPIOCMD1_PORT[j]->BRR |= GPIOCMD1_PIN[j];
		}
		/*else if ((data&(3<<idx))==(2<<idx))//OPEN
		{
			pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			//GPIOCMD1_PORT[j]->MODER  |= (0 << (pinpos));  // input mode
			
		}*/
		j++;
	}
}

void set_io3 (uint32_t data)
{
	int idx,j;
	uint32_t pinpos=0;

	j=14;

	for(idx=0;idx<28;idx+=2)
	{
		if((data&(3<<idx))==((uint32_t)1<<idx))//ON
		{
			pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos));
			GPIOCMD1_PORT[j]->MODER  |= (0x01 << (pinpos ));   // output mode

			GPIOCMD1_PORT[j]->BSRR = GPIOCMD1_PIN[j];
		}
		else if ((data&(3<<idx))==(0<<idx))//OFF
		{
			pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			GPIOCMD1_PORT[j]->MODER  |= (0x01 << (pinpos ));  // output mode

			GPIOCMD1_PORT[j]->BRR = GPIOCMD1_PIN[j];
		}
		else if ((data&(3<<idx))==(2<<idx))//OPEN
		{
			pinpos = GPIOCMD1_PINMODE[j];
			GPIOCMD1_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos));
			//GPIOCMD1_PORT[j]->MODER  |= (0 << (pinpos ));  // input mode
		}
		j++;
	}
}

void set_io2 (uint32_t data)
{
	int idx,j=0;
	uint32_t pinpos=0;

	for(idx=0;idx<12;idx+=2)
	{
        if((data&(3<<idx))==((uint32_t)1<<idx))//ON
		{
			pinpos = GPIOCMD2_PINMODE[j];
			GPIOCMD2_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			GPIOCMD2_PORT[j]->MODER  |= (0x01 << (pinpos ));   // output mode

			GPIOCMD2_PORT[j]->BSRR = GPIOCMD2_PIN[j];
		}
		else if ((data&(3<<idx))==(0<<idx))//OFF
		{
			pinpos = GPIOCMD2_PINMODE[j];
			GPIOCMD2_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			GPIOCMD2_PORT[j]->MODER  |= (0x01 << (pinpos ));  // output mode

			GPIOCMD2_PORT[j]->BRR = GPIOCMD2_PIN[j];
		}
		else if ((data&(3<<idx))==(2<<idx))//OPEN
		{
			pinpos = GPIOCMD2_PINMODE[j];
			GPIOCMD2_PORT[j]->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos ));
			//GPIOCMD2_PORT[j]->MODER  |= (0 << (pinpos));  // input mode
		}
		j++;
	}
}

uint32_t get_in_io(void)
{
	uint32_t data=0;
	/*
	A  GPIO_Pin_8
	B  GPIO_Pin_11|GPIO_Pin_12||GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15
	C  GPIO_Pin_6|GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15
	F  GPIO_Pin_0|GPIO_Pin_1 
	*/
	if(GPIOA->IDR&0x100)//PA.8;   	S1_GIO_1
		data|=1<<0;
	
	if(GPIOB->IDR&0x800)//PB.11;  	S2_GIO_18
		data|=1<<1;
	if(GPIOB->IDR&0x1000)//PB.12;  	S2_GIO_19
		data|=1<<2;
	if(GPIOB->IDR&0x2000)//PB.13;  	S1_GIO_19
		data|=1<<3;
	if(GPIOB->IDR&0x4000)//PB.14;  	S1_GIO_18
		data|=1<<4;
	if(GPIOB->IDR&0x8000)//PB.15;   	S1_GIO_17
		data|=1<<5;

	if(GPIOC->IDR&0x40)//PC.6;   		S1_GIO_15
		data|=1<<6;
	if(GPIOC->IDR&0x80)//PC.7;   		S1_GIO_11
		data|=1<<7;
	if(GPIOC->IDR&0x100)//PC.8;   	S1_GIO_3
		data|=1<<8;
	if(GPIOC->IDR&0x2000)//PC.13;  	S2_GIO_1
		data|=1<<9;
	if(GPIOC->IDR&0x4000)//PC.14;  	S2_GIO_3
		data|=1<<10;
	if(GPIOC->IDR&0x8000)//PC.15;  	S2_GIO_11
		data|=1<<11;

	if(GPIOF->IDR&0x1)//PF.0;  		S2_GIO_15
		data|=1<<12;
	if(GPIOF->IDR&0x2)//PF.1;  		S2_GIO_17
		data|=1<<13;
        
        return data;
}

void set_io_default(void)
{
	uint32_t defData=0;
	
	//OFF-00b, ON-01b, OPEN-10b

    //S1 GIO_0 , GIO_2 , GIO_4, GIO_5, GIO_6, GIO_7, GIO_8 ,GIO_9 , GIO_10 , GIO_12, GIO_13, GIO_14, GIO_16, GIO_20
    //10       , 10    , 10   , 10   , 10   , 10   , 10    ,10    , 10     , 10    ,10     , 10    , 10    , 10
	//defData= 0b1010101010101010101010101010;
        defData=0xAAAAAAA;
	set_io1(defData);
	
    // RS_Indic , BOX ID0 ,BOX ID1 ,BOX ID2 ,BOX ID3 ,BOX ID4
    // 10       ,10       ,10      ,    10  ,   10  ,  10
	//defData=0b101010101010;
        defData=0xAAA;
	set_io2(defData);
	
    //S2 GIO_0 , GIO_2 , GIO_4, GIO_5, GIO_6, GIO_7, GIO_8 ,GIO_9 , GIO_10 , GIO_12, GIO_13, GIO_14, GIO_16, GIO_20
    //10       , 10    , 10   , 10   , 10   , 10   , 10    ,10    , 10     , 10    ,10     , 10    , 10    , 10
	//defData=0b0101010101010101010101010101;
        defData=0xAAAAAAA;
	set_io3(defData);

}

uint32_t get_io1 (void)
{
	int idx,j=0;
	uint32_t data=0,pinpos;

	for(idx=0;idx<28;idx+=2)
	{
		data&= ~(3<<idx);
		pinpos = GPIOCMD1_PINMODE[j];
		if((GPIOCMD1_PORT[j]->MODER &(3<<pinpos))==((uint32_t)1<<pinpos))//OUTPUT
		{
			if(GPIOCMD1_PORT[j]->ODR & GPIOCMD1_PIN[j])
				data|=	(1<<idx);  // ON
		}
		else if (!(GPIOCMD1_PORT[j]->MODER&(3<<pinpos)))//INPUT
		{
			data|=	(2<<idx);  // OPEN
		}
                j++;
	}
	return data;
}
uint32_t get_io2 (void)
{
	int idx,j=0;
	uint32_t data=0,pinpos;

	for(idx=0;idx<12;idx+=2)
	{
		data&= ~(3<<idx);
		pinpos = GPIOCMD2_PINMODE[j];
		if((GPIOCMD2_PORT[j]->MODER &(3<<pinpos))==((uint32_t)1<<pinpos))//OUTPUT
		{
			if(GPIOCMD2_PORT[j]->ODR & GPIOCMD2_PIN[j])
				data|=	(1<<idx);  // ON
		}
		else if (!(GPIOCMD2_PORT[j]->MODER&(3<<pinpos)))//INPUT
		{
			data|=	(2<<idx);  // OPEN
		}
                j++;
	}
	return data;
}
uint32_t get_io3 (void)
{
	int idx,j=14;
	uint32_t data=0,pinpos;

	for(idx=0;idx<28;idx+=2)
	{
		data&= ~(3<<idx);
		pinpos = GPIOCMD1_PINMODE[j];
		if((GPIOCMD1_PORT[j]->MODER &(3<<pinpos))==((uint32_t)1<<pinpos))//OUTPUT
		{
			if(GPIOCMD1_PORT[j]->ODR & GPIOCMD1_PIN[j])
				data|=	(1<<idx);  // ON
		}
		else if (!(GPIOCMD1_PORT[j]->MODER&(3<<pinpos)))//INPUT
		{
			data|=	(2<<idx);  // OPEN
		}
                j++;
	}
	return data;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
