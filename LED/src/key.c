#include "stm32f10x.h" 
#include "Delay.h"

void key_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Mode = GPIO_Mode;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Pin = GPIO_Pin;
	
	GPIO_Init(GPIOx, &gpio_init);
}

uint8_t key_get_bit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1);
		Delay_ms(20);
		return 1;
	}
	return 0;
}

uint8_t key_normal_get_bit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
}
