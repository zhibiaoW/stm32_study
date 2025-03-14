#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"
#include "OLED.h"

uint32_t global_count_sensor_num = 0;

int main(void)
{
	EXTI_InitTypeDef exit_initstruct;
	NVIC_InitTypeDef nvic_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// AFIO 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

	// EXit
	exit_initstruct.EXTI_Line = EXTI_Line1;
	exit_initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	exit_initstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exit_initstruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exit_initstruct);
	exit_initstruct.EXTI_Line = EXTI_Line14;
	EXTI_Init(&exit_initstruct);

	// NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nvic_initstruct.NVIC_IRQChannel = EXTI1_IRQn;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 1;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_initstruct);
	nvic_initstruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&nvic_initstruct);
	
	led_init(GPIOA, GPIO_Pin_0);
	key_init(GPIOA, GPIO_Pin_1 | GPIO_Pin_3, GPIO_Mode_IPD);
	key_init(GPIOA, GPIO_Pin_2, GPIO_Mode_IPU);


	key_init(GPIOB, GPIO_Pin_11 | GPIO_Pin_13, GPIO_Mode_IPU);

	led_init(GPIOB, GPIO_Pin_12);
	
	led_set(GPIOA, GPIO_Pin_0, Bit_SET);
	led_set(GPIOB, GPIO_Pin_12, Bit_SET);

	OLED_Init();
	// OLED_Clear();

	OLED_ShowString(3, 1, "count: ");
	OLED_ShowNum(3, 8, global_count_sensor_num, 3);


	while (1)
	{
		// if (key_get_bit(GPIOB, GPIO_Pin_10) == 1)
		// 	led_turn(GPIOB, GPIO_Pin_12);

			

		// if (key_get_bit(GPIOA, GPIO_Pin_2) == 1)
		// {
		// 	global_count_sensor_num = 0;
		// 	OLED_ShowNum(3, 8, global_count_sensor_num, 3);
		// }

		if (key_normal_get_bit(GPIOB, GPIO_Pin_13) == 1)
		{
			
			OLED_ShowString(1, 1, "bitset");
			led_set(GPIOA, GPIO_Pin_0, Bit_SET);

		}
		else
		{
			
			OLED_ShowString(1, 1, "bitreset");
			led_set(GPIOA, GPIO_Pin_0, Bit_RESET);
		}


	}
}

void EXTI1_IRQHandler(void)
{

	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI15_10_IRQHandler(void)
{
	if (SET == EXTI_GetITStatus(EXTI_Line14))
	{
		OLED_ShowNum(3, 8, ++global_count_sensor_num, 3);
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
