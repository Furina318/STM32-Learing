//
// Created by Sthy on 26-1-4.
//

#ifndef BALL_GAME_H
#define BALL_GAME_H

#include "oled.h"
#include "key.h"
#include "font.h"
#include <stdint.h>

// 屏幕参数
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// 游戏元素参数
#define BALL_RADIUS   2       // 小球半径
#define PADDLE_WIDTH  15      // 挡板宽度
#define PADDLE_HEIGHT 3       // 挡板高度
#define PADDLE_SPEED  2       // 挡板移动速度
#define BALL_SPEED_X  1       // 小球X轴速度
#define BALL_SPEED_Y  1       // 小球Y轴速度

// 游戏状态
typedef enum {
    GAME_READY,    // 准备状态
    GAME_PLAYING,  // 游戏中
    GAME_OVER      // 游戏结束
  } Game_State;

// 游戏数据结构体
typedef struct {
    // 小球属性
    int16_t ball_x;
    int16_t ball_y;
    int8_t ball_dx;
    int8_t ball_dy;

    // 挡板属性
    int16_t paddle_x;
    int16_t paddle_y;

    // 游戏状态
    Game_State state;
    uint16_t score; // 得分
} Game_Data;

// 函数声明
void Game_Init(void);
void Game_Update(void);
void Game_Draw(void);
void Game_HandleInput(void);

#endif //BALL_GAME_H
