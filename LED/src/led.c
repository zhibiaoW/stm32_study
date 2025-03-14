#include "stm32f10x.h" 

void led_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Pin = GPIO_Pin;
	
	GPIO_Init(GPIOx, &gpio_init);
}

void led_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
	GPIO_WriteBit(GPIOx, GPIO_Pin, BitVal);
}

void led_turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin) == 0)
		GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
	else
		GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
}
