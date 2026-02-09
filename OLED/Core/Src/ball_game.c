//
// Created by Sthy on 26-1-4.
//
// game.c
#include "ball_game.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 全局游戏数据
static Game_Data game;

/**
 * @brief 初始化游戏数据
 */
void Game_Init(void)
{
  // 初始化小球（屏幕上方随机位置）
  game.ball_x = SCREEN_WIDTH / 2;
  game.ball_y = BALL_RADIUS + 5;
  game.ball_dx = BALL_SPEED_X;
  game.ball_dy = BALL_SPEED_Y;

  // 初始化挡板（屏幕底部中间）
  game.paddle_x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
  game.paddle_y = SCREEN_HEIGHT - PADDLE_HEIGHT - 2;

  // 初始化游戏状态
  game.state = GAME_READY;
  game.score = 0;
}

/**
 * @brief 处理按键输入
 */
void Game_HandleInput(void)
{
  if(game.state != GAME_PLAYING) return;

  // KEY2：挡板左移
  if(KEY2_Read() == KEY_PRESSED)
  {
    if(game.paddle_x > 0)
    {
      game.paddle_x -= PADDLE_SPEED;
    }
  }

  // KEY1：挡板右移
  if(KEY1_Read() == KEY_PRESSED)
  {
    if(game.paddle_x + PADDLE_WIDTH < SCREEN_WIDTH)
    {
      game.paddle_x += PADDLE_SPEED;
    }
  }
}

/**
 * @brief 更新游戏逻辑（小球移动、碰撞检测）
 */
void Game_Update(void)
{
  if(game.state == GAME_READY)
  {
    // 任意按键开始游戏
    if(KEY1_Read() == KEY_PRESSED || KEY2_Read() == KEY_PRESSED)
    {
      game.state = GAME_PLAYING;
    }
    return;
  }

  if(game.state == GAME_OVER)
  {
    // 任意按键重置游戏
    if(KEY1_Read() == KEY_PRESSED || KEY2_Read() == KEY_PRESSED)
    {
      Game_Init();
    }
    return;
  }

  // ========== 小球移动 ==========
  game.ball_x += game.ball_dx;
  game.ball_y += game.ball_dy;

  // ========== 边界碰撞检测 ==========
  // 左右边界回弹
  if(game.ball_x - BALL_RADIUS <= 0)
  {
    game.ball_x = BALL_RADIUS;
    game.ball_dx = -game.ball_dx;
  }
  else if(game.ball_x + BALL_RADIUS >= SCREEN_WIDTH - 1)
  {
    game.ball_x = SCREEN_WIDTH - 1 - BALL_RADIUS;
    game.ball_dx = -game.ball_dx;
  }

  // 上边界回弹
  if(game.ball_y - BALL_RADIUS <= 0)
  {
    game.ball_y = BALL_RADIUS;
    game.ball_dy = -game.ball_dy;
  }

  // ========== 挡板碰撞检测 ==========
  if( (game.ball_y + BALL_RADIUS >= game.paddle_y) &&
      (game.ball_x >= game.paddle_x) &&
      (game.ball_x <= game.paddle_x + PADDLE_WIDTH) )
  {
    // 碰到挡板，回弹并加分
    game.ball_y = game.paddle_y - BALL_RADIUS - 1;
    game.ball_dy = -game.ball_dy;
    game.score++;
  }

  // ========== 游戏结束检测（小球掉落底部） ==========
  if(game.ball_y + BALL_RADIUS >= SCREEN_HEIGHT)
  {
    game.state = GAME_OVER;
  }
}

/**
 * @brief 绘制游戏画面（适配你的OLED驱动）
 */
void Game_Draw(void)
{
  // 清空帧缓存
  OLED_NewFrame();

  if(game.state == GAME_READY)
  {
    // 显示游戏标题（需提前定义字体，这里用ASCII简化）
    char ready_str1[] = "PRESS KEY";
    char ready_str2[] = "TO START";
    OLED_PrintString(10, 20, ready_str1, &font16x16, OLED_COLOR_NORMAL);
    OLED_PrintString(10, 40, ready_str2, &font16x16, OLED_COLOR_NORMAL);
  }
  else if(game.state == GAME_OVER)
  {
    // 显示游戏结束和得分
    char over_str[] = "GAME OVER!";
    char score_str[20];
    sprintf(score_str, "SCORE: %d", game.score);
    OLED_PrintString(20, 20, over_str, &font16x16, OLED_COLOR_NORMAL);
    OLED_PrintString(20, 40, score_str, &font16x16, OLED_COLOR_NORMAL);
  }
  else if(game.state == GAME_PLAYING)
  {
    // 1. 绘制小球（实心圆）
    OLED_DrawFilledCircle(game.ball_x, game.ball_y, BALL_RADIUS, OLED_COLOR_NORMAL);

    // 2. 绘制挡板（填充矩形）
    OLED_DrawFilledRectangle(game.paddle_x, game.paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT, OLED_COLOR_NORMAL);

    // 3. 绘制得分
    char score_str[10];
    sprintf(score_str, "%d", game.score);
    OLED_PrintString(5, 5, score_str, &font16x16, OLED_COLOR_NORMAL);
  }

  // 显示当前帧到OLED
  OLED_ShowFrame();
}