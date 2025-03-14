#ifndef __LED_H
#define __LED_H

void led_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void led_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void led_turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
