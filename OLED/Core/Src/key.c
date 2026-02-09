//
// Created by Sthy on 26-1-4.
//
// key.c
#include "key.h"
// #include "stm32f1xx_hal_gpio.h"
#include "main.h"
/**
 * @brief 通用按键读取函数（消抖）
 */
uint8_t KEY_Read(uint16_t key)
{
    if (key == 1)
    {
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(20); // 消抖延时
            if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET)
            {
                return KEY_PRESSED;
            }
        }
        return KEY_RELEASED;
    }
    else if (key == 0)
    {
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)
        {
            HAL_Delay(20); // 消抖延时
            if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)
            {
                return KEY_PRESSED;
            }
        }
        return KEY_RELEASED;
    }
}

/**
 * @brief 读取KEY1状态, 左键
 */
uint8_t KEY1_Read(void)
{
    return KEY_Read(0);
}

/**
 * @brief 读取KEY2状态, 右键
 */
uint8_t KEY2_Read(void)
{
    return KEY_Read(1);
}