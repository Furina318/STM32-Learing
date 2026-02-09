//
// Created by Sthy on 26-1-4.
//

#ifndef KEY_H
#define KEY_H

#include <stdint.h>

#define KEY1_Pin GPIO_PIN_12
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOB

// 按键状态
#define KEY_PRESSED  1
#define KEY_RELEASED 0

// 函数声明
uint8_t KEY_Read(uint16_t GPIO_Pin);
uint8_t KEY1_Read(void);
uint8_t KEY2_Read(void);

#endif //KEY_H
