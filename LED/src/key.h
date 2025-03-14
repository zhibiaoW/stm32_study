#ifndef __KEY_H
#define __KEY_H

void key_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);
uint8_t key_get_bit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int result);
uint8_t key_normal_get_bit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
