/*====================================================================================================*/
/*====================================================================================================*/
#include "module_ws2812b.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define WS2812B_PIN       (2)

#define WS_PIN 0x00000004  // 1UL << WS2812B_PIN

uint8_t WS2812B_RGB[WS2812B_LENS][3] = {0};
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_Config
**功能 : WS2812B Config
**輸入 : None
**輸出 : None
**使用 : WS2812B_Config();
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_Config( void )
{
  nrf_gpio_cfg_output(WS2812B_PIN);
  WS2812B_clearAll(0, 0, 0);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_setRGB
**功能 : Set RGB Data
**輸入 : led, r, g, b
**輸出 : None
**使用 : WS2812B_setRGB(led, r, g, b);
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_setRGB( uint16_t index, uint8_t r, uint8_t g, uint8_t b )
{
  WS2812B_RGB[index][0] = g;
  WS2812B_RGB[index][1] = r;
  WS2812B_RGB[index][2] = b;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_sendPixel
**功能 : WS2812B Send Pixel
**輸入 : led, r, g, b
**輸出 : None
**使用 : WS2812B_sendPixel(led, r, g, b);
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_sendPixel( uint16_t index, uint8_t r, uint8_t g, uint8_t b )
{
  WS2812B_RGB[index][0] = g;
  WS2812B_RGB[index][1] = r;
  WS2812B_RGB[index][2] = b;
  WS2812B_show();	
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_show
**功能 : WS2812B Show
**輸入 : None
**輸出 : None
**使用 : WS2812B_show();
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_show( void )
{
  WS2812B_RESET();

  for(uint8_t i = 0; i < WS2812B_LENS; i++) {
    for(uint8_t j = 0; j < 3; j++) {
      if(WS2812B_RGB[i][j] & 0x80)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x40)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x20)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x10)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x08)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x04)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x02)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
      if(WS2812B_RGB[i][j] & 0x01)  {WS2812B_LOGIC_H()}
      else                          {WS2812B_LOGIC_L()}
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_clearAll
**功能 : WS2812B Clear All
**輸入 : r, g, b
**輸出 : None
**使用 : WS2812B_clearAll(r, g, b);
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b )
{
  for(uint8_t i = 0; i < WS2812B_LENS; i++) {
    WS2812B_RGB[i][0] = g;
    WS2812B_RGB[i][1] = r;
    WS2812B_RGB[i][2] = b;
  }
  WS2812B_show();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_testRainbow
**功能 : WS2812B Test Rainbow
**輸入 : None
**輸出 : None
**使用 : WS2812B_testRainbow();
**====================================================================================================*/
/*====================================================================================================*/
#define TLIG_R 4
void WS2812B_testRainbow( void )
{
  uint8_t intStageNum = 0;
  uint8_t r = TLIG_R, g = 0, b = 0;

  for(uint16_t i = 0; i < TLIG_R * 6; i++) {
    switch(intStageNum) {
      case 0: { g++; if(g == TLIG_R) { intStageNum = 1;}  break; }
      case 1: { r--; if(r == 0)      { intStageNum = 2;}  break; }
      case 2: { b++; if(b == TLIG_R) { intStageNum = 3;}  break; }
      case 3: { g--; if(g == 0)      { intStageNum = 4;}  break; }
      case 4: { r++; if(r == TLIG_R) { intStageNum = 5;}  break; }
      case 5: { b--; if(b == 0)      { intStageNum = 0;}  break; }
    }
    for(uint8_t j = 0; j < WS2812B_LENS; j++) {
      WS2812B_RGB[j][0] = g;
      WS2812B_RGB[j][1] = r;
      WS2812B_RGB[j][2] = b;
    }

    WS2812B_show();
    delay_ms(100);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_testBreath
**功能 : WS2812B test Breath
**輸入 : speed
**輸出 : None
**使用 : WS2812B_testBreath(speed);
**====================================================================================================*/
/*====================================================================================================*/
#define TLIG_B 16
void WS2812B_testBreath( uint32_t speed )
{
  uint8_t state = 1;
  uint8_t color = 0;

  for(uint16_t i = 0; i < TLIG_B * 2; i++) {
    color = (state == 1) ? (color + 1) : (color - 1);
    WS2812B_clearAll(color, color, color);
    delay_ms(speed);

    if(color == TLIG_B)
      state = 0;
    else if (color == 0) {
      state = 1;
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_DEMO
**功能 : WS2812B DEMO
**輸入 : None
**輸出 : None
**使用 : WS2812B_DEMO();
**====================================================================================================*/
/*====================================================================================================*/
void WS2812B_DEMO( void )
{
  WS2812B_clearAll(0, 0, 0);
  delay_ms(100);

  WS2812B_testBreath(40);
  WS2812B_testBreath(40);
  delay_ms(100);
  for(uint8_t i = 0; i < TLIG_R; i++) {
    WS2812B_clearAll(i, 0, 0);
    delay_ms(100);
  }

  while(1) {
    WS2812B_testRainbow();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
