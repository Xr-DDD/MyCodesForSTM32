#ifndef _OLED_I2C_H_
#define _OLED_I2C_H_

#include "stm32f1xx_hal.h"
#include "oledfont.h"
/**修改所使用的I2C*****************************************************************************************************************************************/
#define OLED_I2C_HANDLE             (&hi2c1)
extern I2C_HandleTypeDef              hi2c1;
/**预定义可选参数******************************************************************************************************************************************/
#define CHAR_SIZE_8                 (8)
#define CHAR_SIZE_6                 (6) 
#define CHAR_COLOR_WHITE            (0)
#define CHAR_COLOR_BLACK            (1)
#define SHOW_SIGN_OFF               (0)
#define SHOW_SIGN_ON                (1)
#define BG_COLOR_BLACK              (0xA6)
#define BG_COLOR_WHITE              (0xA7)
/**显存缓冲数组********************************************************************************************************************************************/
extern uint8_t OLED_GRAM[8][128];
/**OLED写命令或数据或指定地址*******************************************************************************************************************************/
void OLED_WriteCmd(uint8_t cmd);
void OLED_WriteMultiCmd(uint8_t cmd[], uint16_t len);
void OLED_WriteData(uint8_t data);
void OLED_WriteMultiData(uint8_t data[], uint16_t len);
void OLED_SetPos(uint8_t column, uint8_t page);
/**使用下面的函数对显存缓冲数组进行编辑或将缓冲写入物理显存****************************************************************************************************/
void OLED_GRAM_Refresh(void);
void OLED_GRAM_RefreshPart(uint8_t page, uint8_t column1, uint8_t column2);
void OLED_GRAM_WriteByte(uint8_t page, uint8_t column, uint8_t byte);
void OLED_GRAM_DrawPoint(uint8_t x, uint8_t y);
void OLED_GRAM_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_GRAM_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill);
void OLED_GRAM_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);
void OLED_GRAM_WipePoint(uint8_t x, uint8_t y);
void OLED_GRAM_WipeLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_GRAM_WipeRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill);
void OLED_GRAM_WipeCircle(uint8_t x0, uint8_t y0, uint8_t r);
void OLED_GRAM_ShowChr(uint8_t page, uint8_t column, uint8_t chr, uint8_t char_size, uint8_t char_color);
void OLED_GRAM_ShowCHinese(uint8_t page, uint8_t column, uint8_t CH16X16[][32], uint8_t n, uint8_t char_color);
void OLED_GRAM_DrawBMP(uint8_t page, uint8_t column, uint8_t* BMP, uint8_t pag_wid, uint8_t col_len, uint8_t char_color);
/**使用下面的函数对OLED进行操作*****************************************************************************************************************************/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Fill(void);
void OLED_DrawPoint(uint8_t x, uint8_t y);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill);
void OLED_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);
void OLED_WipePoint(uint8_t x, uint8_t y);
void OLED_WipeLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_WipeRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill);
void OLED_WipeCircle(uint8_t x0, uint8_t y0, uint8_t r);
void OLED_ShowChr(uint8_t page, uint8_t column, uint8_t chr, uint8_t char_size, uint8_t char_color);
void OLED_ShowStr(uint8_t page, uint8_t column, char*   chr, uint8_t char_size, uint8_t char_color);
void OLED_ShowNum(uint8_t page, uint8_t column, int     num, uint8_t   num_len, uint8_t show_sign, uint8_t char_size, uint8_t char_color);
void OLED_ShowDec(uint8_t page, uint8_t column, double  dec, uint8_t   int_len, uint8_t flo_len, uint8_t show_sign, uint8_t char_size, uint8_t char_color);
void OLED_ShowCHinese(uint8_t page, uint8_t column, uint8_t CH16X16[][32], uint8_t n,uint8_t char_color);
void OLED_DrawBMP(uint8_t page, uint8_t column, uint8_t* BMP, uint8_t pag_wid, uint8_t col_len, uint8_t char_color);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_BackgroundColor(uint8_t bg_color);
/*********************************************************************************************************************************************************/
#endif


