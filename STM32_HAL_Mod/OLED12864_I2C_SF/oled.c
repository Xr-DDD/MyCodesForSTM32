#include "oled.h"
#define I2C_TIME_OUT			(1000)
#define DEV_ADDR				(0x78)
#define CMD_ADDR				(0x00)
#define DAT_ADDR				(0x40)


//内部延迟函数
static void oled_delay_while(uint16_t n)
{
	while(n--);
}
//内部求幂函数
static unsigned int oled_pow(uint8_t m, uint8_t n)
{
	unsigned int result = 1;

	while(n--)result *= m;
	
	return result;
}
//内部交换函数
static void oled_swap(uint8_t* a, uint8_t* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/** 
 * @brief 向OLED写入单个命令
 * @param cmd 需要写入的命令
 */
void OLED_WriteCmd(uint8_t cmd)
{
	M_I2C_Mem_Write(DEV_ADDR, CMD_ADDR, &cmd, 1);
}

/** 
 * @brief 向OLED写入多条命令
 * @param cmd 需要写入的命令数组
 * @param len 命令数组的长度
 */
void OLED_WriteMultiCmd(uint8_t cmd[], uint16_t len)
{
	M_I2C_Mem_Write(DEV_ADDR, CMD_ADDR, cmd, len);
}

/** 
 * @brief 向OLED写入单个数据
 * @param data 需要写入的数据
 */
void OLED_WriteData(uint8_t data)
{
	M_I2C_Mem_Write(DEV_ADDR, DAT_ADDR, &data, 1);
}

/** 
 * @brief 向OLED写入多条数据
 * @param data 需要写入的数据数组
 * @param len 数据数组的长度
 */
void OLED_WriteMultiData(uint8_t data[], uint16_t len)
{
	M_I2C_Mem_Write(DEV_ADDR, DAT_ADDR, data, len);
}

/** 
 * @brief 与物理显存相对应的显存缓冲数组，分成8页128列，每列8个竖排的像素点，写屏幕的操作是先编辑显存缓冲，再将显存缓冲写入物理显存中
 */
uint8_t OLED_GRAM[8][128];

/** 
 * @brief 向OLED写入字节前需要通过这个函数指定字节的地址
 * @param column 字节需要写入128列中的哪一列 输入 0~127
 * @param page 字节需要写入8页中的哪一页 输入 0~7
 */
void OLED_SetPos(uint8_t column, uint8_t page)
{
	if(column < 128 && page < 8)
	{
		uint8_t SetPos_CMD[3]=
		{
			0xb0 + page,								//设置页地址
			column & 0x0f,								//设置列低地址
			((column & 0xf0) >> 4) | 0x10				//设置列高地址
		};				

		OLED_WriteMultiCmd(SetPos_CMD, sizeof(SetPos_CMD)/sizeof(SetPos_CMD[0]));
	}
}

/** 
 * @brief 通过这个函数将显存缓冲数组的内容全部写入物理显存中从而使OLED显示出内容
 */
void OLED_GRAM_Refresh(void)
{
	uint8_t page;
	
	for(page = 0; page < 8; page++)					//只需要遍历页，因为列地址可以自增
	{
		OLED_SetPos(0, page);
		OLED_WriteMultiData(&OLED_GRAM[page][0], 128);
	}
}

/** 
 * @brief 通过这个函数将显存缓冲数组的一部分内容写入物理显存中，只写一部分，“可能”会更快？
 * @param page 需要刷新的页
 * @param column1 从哪一列开始进行刷新，column1处会被刷新
 * @param column2 从哪一列结束刷新，column2处会被刷新，如果结束的位置比开始的位置还要靠前，则刷新这个区间之外的部分
 */
void OLED_GRAM_RefreshPart(uint8_t page, uint8_t column1, uint8_t column2)
{
	while(page >= 8)page -= 8;
	while(column1 >= 128)column1 -= 128;
	while(column2 >= 128)column2 -= 128;
	if(column1 <= column2)
	{
		OLED_SetPos(column1, page);
		OLED_WriteMultiData(&OLED_GRAM[page][column1], column2 - column1 +1);
	}else
	{
		OLED_SetPos(column1, page);
		OLED_WriteMultiData(&OLED_GRAM[page][column1], 128 - column1);
		OLED_SetPos(0, page);
		OLED_WriteMultiData(&OLED_GRAM[page][0], column2 + 1);
	}
}

/** 
 * @brief 清屏，屏幕全灭
 */
void OLED_Clear(void)
{
	uint8_t page,column;
	
	for(page = 0; page < 8; page++)					
		for(column = 0; column < 128; column++)		
			OLED_GRAM[page][column] = 0x00;		//显存清零
	
	OLED_GRAM_Refresh();
}

/** 
 * @brief 亮屏，屏幕全亮
 */
void OLED_Fill(void)
{
	uint8_t page, column;

	for(page = 0; page < 8; page++)					
		for(column = 0; column < 128; column++)		
			OLED_GRAM[page][column] = 0xff;		//显存填充
	
	OLED_GRAM_Refresh();
}

/** 
 * @brief OLED初始化，使用OLED相关函数前必须先初始化
 */
void OLED_Init(void)
{
	oled_delay_while(10000);

    uint8_t Init_CMD[23]=
	{
		0xAE, 0xD5, 0x80, 0xA8, 0x3F, 
		0xD3, 0x00, 0x40, 0xA1, 0xC8, 
		0xDA, 0x12, 0x81, 0xCF, 0xD9, 
		0xF1, 0xDB, 0x40, 0xA4, 0xA6, 
		0x8D, 0x14, 0xAF
	};											//用于初始化的23条命令

	OLED_WriteMultiCmd(Init_CMD, sizeof(Init_CMD)/sizeof(Init_CMD[0]));
	OLED_Clear();
}

/** 
 * @brief 向显存缓冲数组而非OLED中写入字节，这个函数不会对实际的OLED造成影响
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param byte 写入显存缓冲数组的字节
 */
void OLED_GRAM_WriteByte(uint8_t page, uint8_t column, uint8_t byte)
{
	while(page >= 8)page -= 8;					//纵向循环
	while(column >= 128)column -= 128;			//横向循环
	OLED_GRAM[page][column] = byte;
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，点亮其中一个点（写1），这个函数不会对实际的OLED直接造成影响
 * @param x 输入 0~127
 * @param y 输入 0~63
 */
void OLED_GRAM_DrawPoint(uint8_t x, uint8_t y)
{
	OLED_GRAM_WriteByte(y/8, x, OLED_GRAM[y/8][x] | (0x01 << (y%8)));
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，熄灭其中一个点（写0），这个函数不会对实际的OLED直接造成影响
 * @param x 输入 0~127
 * @param y 输入 0~63
 */
void OLED_GRAM_WipePoint(uint8_t x, uint8_t y)
{
	OLED_GRAM_WriteByte(y/8, x, OLED_GRAM[y/8][x] & (~(0x01 << (y%8))));
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，在其中画一条线（写1），这个函数不会对实际的OLED直接造成影响
 * @param x1  线的起点横坐标 输入 0~127
 * @param y1  线的起点纵坐标 输入 0~63
 * @param x2  线的终点横坐标
 * @param y2  线的终点纵坐标
 */
void OLED_GRAM_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t x, y;

	if(x1 == x2 && y1 == y2)
	{
		OLED_GRAM_DrawPoint(x1, y1);
	}
	else if(x1 == x2)
	{
		if(y1 < y2)
			for(y = y1; y <= y2; y++)
				OLED_GRAM_DrawPoint(x1, y);
		else
			for(y = y2; y <= y1; y++)
				OLED_GRAM_DrawPoint(x1, y);
	}
	else if(y1 == y2)
	{
		if(x1 < x2)
			for(x = x1; x <= x2; x++)
				OLED_GRAM_DrawPoint(x, y1);
		else
			for(x = x2; x <= x1; x++)
				OLED_GRAM_DrawPoint(x, y1);
	}
	else
	{
		if((x1 > x2 && y1 > y2) || (x1 > x2 && y1 < y2))
		{
			oled_swap(&x1, &x2);
			oled_swap(&y1, &y2);
		}
		
		float k = (float)(y2 - y1)/(x2 - x1);
		uint8_t n = 0;

		if(x1 < x2 && y1 < y2 && k < 1)
		{
			for(x = x1, y = y1, n = 0; x <= x2; n++, x++, y = y1 + n*k)
			{
				OLED_GRAM_DrawPoint(x, y);
			}
		}
		else if(x1 < x2 && y1 < y2 && k >= 1)
		{
			for(x = x1, y = y1, n = 0; y <= y2; n++, y++, x = x1 + n/k)
			{
				OLED_GRAM_DrawPoint(x, y);
			}
		}
		else if(x1 < x2 && y1 > y2 && k > -1)
		{
			for(x = x1, y = y1, n = 0; x <= x2; n++, x++, y = y1 - n*(-k))
			{
				OLED_GRAM_DrawPoint(x, y);
			}
		}
		else if(x1 < x2 && y1 > y2 && k <= -1)
		{
			for(x = x1, y = y1, n = 0; y >= y2; n++, y--, x = x1 + n/(-k))
			{
				OLED_GRAM_DrawPoint(x, y);
			}
		}
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，在其中擦除一条线（写0），这个函数不会对实际的OLED直接造成影响
 * @param x1  线的起点横坐标 输入 0~127
 * @param y1  线的起点纵坐标 输入 0~63
 * @param x2  线的终点横坐标
 * @param y2  线的终点纵坐标
 */
void OLED_GRAM_WipeLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t x, y;

	if(x1 == x2 && y1 == y2)
	{
		OLED_GRAM_WipePoint(x1, y1);
	}
	else if(x1 == x2)
	{
		if(y1 < y2)
			for(y = y1; y <= y2; y++)
				OLED_GRAM_WipePoint(x1, y);
		else
			for(y = y2; y <= y1; y++)
				OLED_GRAM_WipePoint(x1, y);
	}
	else if(y1 == y2)
	{
		if(x1 < x2)
			for(x = x1; x <= x2; x++)
				OLED_GRAM_WipePoint(x, y1);
		else
			for(x = x2; x <= x1; x++)
				OLED_GRAM_WipePoint(x, y1);
	}
	else
	{
		if((x1 > x2 && y1 > y2) || (x1 > x2 && y1 < y2))
		{
			oled_swap(&x1, &x2);
			oled_swap(&y1, &y2);
		}
		
		float k = (float)(y2 - y1)/(x2 - x1);
		uint8_t n = 0;

		if(x1 < x2 && y1 < y2 && k < 1)
		{
			for(x = x1, y = y1, n = 0; x <= x2; n++, x++, y = y1 + n*k)
			{
				OLED_GRAM_WipePoint(x, y);
			}
		}
		else if(x1 < x2 && y1 < y2 && k >= 1)
		{
			for(x = x1, y = y1, n = 0; y <= y2; n++, y++, x = x1 + n/k)
			{
				OLED_GRAM_WipePoint(x, y);
			}
		}
		else if(x1 < x2 && y1 > y2 && k > -1)
		{
			for(x = x1, y = y1, n = 0; x <= x2; n++, x++, y = y1 - n*(-k))
			{
				OLED_GRAM_WipePoint(x, y);
			}
		}
		else if(x1 < x2 && y1 > y2 && k <= -1)
		{
			for(x = x1, y = y1, n = 0; y >= y2; n++, y--, x = x1 + n/(-k))
			{
				OLED_GRAM_WipePoint(x, y);
			}
		}
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，根据对角线绘制矩形（写1），这个函数不会对实际的OLED直接造成影响
 * @param x1  矩形对角线的起点横坐标 输入 0~127
 * @param y1  矩形对角线的起点纵坐标 输入 0~63
 * @param x2  矩形对角线的终点横坐标
 * @param y2  矩形对角线的终点纵坐标
 * @param fill 是否填充矩形，0：只画矩形框，1：画中间填充的矩形
 */
void OLED_GRAM_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill)
{
	uint8_t x, y;

	if(x1 > x2)oled_swap(&x1, &x2);
	if(y1 > y2)oled_swap(&y1, &y2);

	if(fill)
	{
		for(x = x1; x <= x2; x++)
			for(y = y1; y <= y2; y++)
				OLED_GRAM_DrawPoint(x, y);
	}
	else
	{
		for(x = x1, y = y1; x <= x2; x++)
			OLED_GRAM_DrawPoint(x, y);

		for(x = x1, y = y1; y <= y2; y++)
			OLED_GRAM_DrawPoint(x, y);
		
		for(x = x2, y = y2; x > x1; x--)
			OLED_GRAM_DrawPoint(x, y);
		
		for(x = x2, y = y2; y > y1; y--)
			OLED_GRAM_DrawPoint(x, y);
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，根据对角线擦除矩形（写0），这个函数不会对实际的OLED直接造成影响
 * @param x1  矩形对角线的起点横坐标 输入 0~127
 * @param y1  矩形对角线的起点纵坐标 输入 0~63
 * @param x2  矩形对角线的终点横坐标
 * @param y2  矩形对角线的终点纵坐标
 * @param fill 是否填充矩形，0：只擦除矩形框，1：擦除中间填充的矩形
 */
void OLED_GRAM_WipeRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill)
{
	uint8_t x, y;
	if(x1 > x2)oled_swap(&x1, &x2);
	if(y1 > y2)oled_swap(&y1, &y2);

	if(fill)
	{
		for(x = x1; x <= x2; x++)
			for(y = y1; y <= y2; y++)
				OLED_GRAM_WipePoint(x, y);
	}
	else
	{
		for(x = x1, y = y1; x <= x2; x++)
			OLED_GRAM_WipePoint(x, y);

		for(x = x1, y = y1; y <= y2; y++)
			OLED_GRAM_WipePoint(x, y);

		for(x = x2, y = y2; x > x1; x--)
			OLED_GRAM_WipePoint(x, y);

		for(x = x2, y = y2; y > y1; y--)
			OLED_GRAM_WipePoint(x, y);
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，根据圆心和半径绘制圆（写1），这个函数不会对实际的OLED直接造成影响
 * @param x0 圆心横坐标 输入 0~127
 * @param y0 圆心纵坐标 输入 0~63
 * @param r 圆的半径 不要超出屏幕范围
 */
void OLED_GRAM_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r)
{
	if(r <= x0 && r <= y0 && r <= 127 - x0 && r <= 63 - y0 && x0 < 128 && y0 < 64)
	{
		uint8_t x, y;
		short com;
		x = 0;
		y = r;
		com = 3 - 2*r;
		OLED_GRAM_DrawPoint(x0 - x, y0 - y);
		OLED_GRAM_DrawPoint(x0 - x, y0 + y);
		OLED_GRAM_DrawPoint(x0 + x, y0 - y);
		OLED_GRAM_DrawPoint(x0 + x, y0 + y);
		OLED_GRAM_DrawPoint(x0 - y, y0 - x);
		OLED_GRAM_DrawPoint(x0 - y, y0 + x);
		OLED_GRAM_DrawPoint(x0 + y, y0 - x);
		OLED_GRAM_DrawPoint(x0 + y, y0 + x);
		while(x < y)
		{
			if(com < 0)
			{
				com = com + 4*x + 6;
			}
			else
			{
				com = com + 4*(x - y) + 10;
				y--;
			}
			x++;
			OLED_GRAM_DrawPoint(x0 - x, y0 - y);
			OLED_GRAM_DrawPoint(x0 - x, y0 + y);
			OLED_GRAM_DrawPoint(x0 + x, y0 - y);
			OLED_GRAM_DrawPoint(x0 + x, y0 + y);
			OLED_GRAM_DrawPoint(x0 - y, y0 - x);
			OLED_GRAM_DrawPoint(x0 - y, y0 + x);
			OLED_GRAM_DrawPoint(x0 + y, y0 - x);
			OLED_GRAM_DrawPoint(x0 + y, y0 + x);
		}
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，根据圆心和半径擦除圆（写0），这个函数不会对实际的OLED直接造成影响
 * @param x0 圆心横坐标 输入 0~127
 * @param y0 圆心纵坐标 输入 0~63
 * @param r 圆的半径 不要超出屏幕范围
 */
void OLED_GRAM_WipeCircle(uint8_t x0, uint8_t y0, uint8_t r)
{
	if(r <= x0 && r <= y0 && r <= 127 - x0 && r <= 63 - y0 && x0 < 128 && y0 < 64)
	{	
		uint8_t x, y;
		short com;
		x = 0;
		y = r;
		com = 3 - 2*r;
		OLED_GRAM_WipePoint(x0 - x, y0 - y);
		OLED_GRAM_WipePoint(x0 - x, y0 + y);
		OLED_GRAM_WipePoint(x0 + x, y0 - y);
		OLED_GRAM_WipePoint(x0 + x, y0 + y);
		OLED_GRAM_WipePoint(x0 - y, y0 - x);
		OLED_GRAM_WipePoint(x0 - y, y0 + x);
		OLED_GRAM_WipePoint(x0 + y, y0 - x);
		OLED_GRAM_WipePoint(x0 + y, y0 + x);
		while(x < y)
		{
			if(com < 0)
			{
				com = com + 4*x + 6;
			}
			else
			{
				com = com + 4*(x - y) + 10;
				y--;
			}
			x++;
			OLED_GRAM_WipePoint(x0 - x, y0 - y);
			OLED_GRAM_WipePoint(x0 - x, y0 + y);
			OLED_GRAM_WipePoint(x0 + x, y0 - y);
			OLED_GRAM_WipePoint(x0 + x, y0 + y);
			OLED_GRAM_WipePoint(x0 - y, y0 - x);
			OLED_GRAM_WipePoint(x0 - y, y0 + x);
			OLED_GRAM_WipePoint(x0 + y, y0 - x);
			OLED_GRAM_WipePoint(x0 + y, y0 + x);
		}
	}
}

/** 
 * @brief 在OLED上根据圆心和半径绘制圆
 * @param x0 圆心横坐标 输入 0~127
 * @param y0 圆心纵坐标 输入 0~63
 * @param r 圆的半径 不要超出屏幕范围
 */
void OLED_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r)
{
	OLED_GRAM_DrawCircle(x0, y0, r);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在OLED上根据圆心和半径擦除圆
 * @param x0 圆心横坐标 输入 0~127
 * @param y0 圆心纵坐标 输入 0~63
 * @param r 圆的半径 不要超出屏幕范围
 */
void OLED_WipeCircle(uint8_t x0, uint8_t y0, uint8_t r)
{
	OLED_GRAM_WipeCircle(x0, y0, r);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在OLED上绘制点
 * @param x 点的横坐标 输入 0~127
 * @param y 点的纵坐标 输入 0~63
 */
void OLED_DrawPoint(uint8_t x, uint8_t y)
{
	OLED_GRAM_DrawPoint(x, y);
	OLED_GRAM_RefreshPart(y/8, x, x);
}

/** 
 * @brief 在OLED上擦除点
 * @param x 点的横坐标 输入 0~127
 * @param y 点的纵坐标 输入 0~63
 */
void OLED_WipePoint(uint8_t x, uint8_t y)
{
	OLED_GRAM_WipePoint(x, y);
	OLED_GRAM_RefreshPart(y/8, x, x);
}

/** 
 * @brief 在OLED上绘制线
 * @param x1 线的起始横坐标 输入 0~127
 * @param y1 线的起始纵坐标 输入 0~63
 * @param x2 线的结束横坐标
 * @param y2 线的结束纵坐标
 */
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	OLED_GRAM_DrawLine(x1, y1, x2, y2);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在OLED上擦除线
 * @param x1 线的起始横坐标 输入 0~127
 * @param y1 线的起始纵坐标 输入 0~63
 * @param x2 线的结束横坐标
 * @param y2 线的结束纵坐标
 */
void OLED_WipeLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	OLED_GRAM_WipeLine(x1, y1, x2, y2);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在OLED上根据对角线绘制矩形
 * @param x1 对角线的起始横坐标 输入 0~127
 * @param y1 对角线的起始纵坐标 输入 0~63
 * @param x2 对角线的结束横坐标
 * @param y2 对角线的结束纵坐标
 * @param fill 是否填充矩形，0：只绘制矩形框，1：绘制填充的矩形
 */
void OLED_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill)
{
	OLED_GRAM_DrawRect(x1, y1, x2, y2, fill);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在OLED上根据对角线擦除矩形
 * @param x1 对角线的起始横坐标 输入 0~127
 * @param y1 对角线的起始纵坐标 输入 0~63
 * @param x2 对角线的结束横坐标
 * @param y2 对角线的结束纵坐标
 * @param fill 是否填充矩形，0：只擦除矩形框，1：擦除填充的矩形
 */
void OLED_WipeRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill)
{
	OLED_GRAM_WipeRect(x1, y1, x2, y2, fill);
	OLED_GRAM_Refresh();
}

/** 
 * @brief 在显存缓冲数组中，在某一页的某一列开始显示一个字符，这个函数不会对实际的OLED直接造成影响
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param chr 需要显示的字符
 * @param char_size 字符大小，选用CHAR_SIZE_6（大小：1page x 6column）和CHAR_SIZE_8（大小：2page x 8column）
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_GRAM_ShowChr(uint8_t page, uint8_t column, uint8_t chr, uint8_t char_size, uint8_t char_color)
{
	uint8_t c = chr - ' ';
	uint8_t i;
	
    if(char_size == 8)
    {
		for(i = 0; i < char_size; i++)
		{
			if(char_color)
			{
				OLED_GRAM_WriteByte(page, column+i, ~F8X16[c][i]);
				OLED_GRAM_WriteByte(page+1, column+i, ~F8X16[c][i+8]);
			}
			else
			{
				OLED_GRAM_WriteByte(page, column+i, F8X16[c][i]);
				OLED_GRAM_WriteByte(page+1, column+i, F8X16[c][i+8]);
			}
		}
    }
    else if(char_size == 6)
    {
        for(i = 0; i < char_size; i++)
        {
            if(char_color)
				OLED_GRAM_WriteByte(page, column+i, ~F6x8[c][i]);
            else
                OLED_GRAM_WriteByte(page, column+i, F6x8[c][i]);
        }
    }
}

/** 
 * @brief 在OLED上在某一页的某一列开始显示一个字符
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param chr 需要显示的字符
 * @param char_size 字符大小，选用CHAR_SIZE_6（大小：1page x 6column）和CHAR_SIZE_8（大小：2page x 8column）
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_ShowChr(uint8_t page, uint8_t column, uint8_t chr, uint8_t char_size, uint8_t char_color)
{
	OLED_GRAM_ShowChr(page, column, chr, char_size, char_color);
	if(char_size == 6)
	{
		OLED_GRAM_RefreshPart(page, column, column+char_size);
	}else if(char_size == 8)
	{
		OLED_GRAM_RefreshPart(page, column, column+char_size);
		OLED_GRAM_RefreshPart(page+1, column, column+char_size);
	}
}

/** 
 * @brief 在OLED上在某一页的某一列开始显示一串字符串
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param chr 需要显示的字符串
 * @param char_size 字符大小，选用CHAR_SIZE_6（大小：1page x 6column）和CHAR_SIZE_8（大小：2page x 8column）
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_ShowStr(uint8_t page, uint8_t column, char* chr, uint8_t char_size, uint8_t char_color)
{
	uint8_t  j = 0;
	if (char_size == 6)
		for(j = 0; chr[j] != '\0'; j++, column += 6)		
        	OLED_ShowChr(page, column, chr[j], char_size, char_color);
	else if(char_size == 8)
		for(j = 0; chr[j] != '\0'; j++, column += 8)		
        	OLED_ShowChr(page, column, chr[j], char_size, char_color);
}

/** 
 * @brief 在OLED上在某一页的某一列开始显示一串整数，负数前加“-”表示
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param num 需要显示的整数
 * @param num_len 整数的长度，即该整数中包含几个数字
 * @param show_sign 如果是正数，是否在前显示“+”，选用SHOW_SIGN_OFF和SHOW_SIGN_ON
 * @param char_size 字符大小，选用CHAR_SIZE_6（大小：1page x 6column）和CHAR_SIZE_8（大小：2page x 8column）
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_ShowNum(uint8_t page, uint8_t column, int num, uint8_t num_len, uint8_t show_sign, uint8_t char_size, uint8_t char_color)
{
	uint8_t num_temp, i;
	if(num >= 0)
	{
		if(show_sign)
		{
			OLED_ShowChr(page, column, '+', char_size, char_color);
			for(i = 0; i < num_len; i++)
			{
				num_temp = num/oled_pow(10, num_len-1-i)%10;
				OLED_ShowChr(page, column+(i+1)*char_size, num_temp+'0', char_size, char_color);
			}
		}
		else
		{
			for(i = 0; i < num_len; i++)
			{	
				num_temp = num/oled_pow(10, num_len-1-i)%10;
				OLED_ShowChr(page, column+i*char_size, num_temp+'0', char_size, char_color);
			}
		}
	}
	else
	{
		OLED_ShowChr(page, column, '-', char_size, char_color);
		for(i = 0; i < num_len; i++)
		{
			num_temp = (-num)/oled_pow(10, num_len-1-i)%10;
			OLED_ShowChr(page, column+(i+1)*char_size, num_temp+'0', char_size, char_color);
		}
	}
}

/** 
 * @brief 在OLED上在某一页的某一列开始显示一串小数，负数前加“-”表示
 * @param page 页 输入 0~7
 * @param column 列 输入 0~127
 * @param dec 需要显示的小数
 * @param int_len 整数部分的长度，即整数部分中包含几个数字
 * @param flo_len 小数部分的长度
 * @param show_sign 如果是正数，是否在前显示“+”，选用SHOW_SIGN_OFF和SHOW_SIGN_ON
 * @param char_size 字符大小，选用CHAR_SIZE_6（大小：1page x 6column）和CHAR_SIZE_8（大小：2page x 8column）
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_ShowDec(uint8_t page, uint8_t column, double dec, uint8_t int_len, uint8_t flo_len, uint8_t show_sign, uint8_t char_size, uint8_t char_color)
{
	int flo = (int)((dec - (int)dec) * oled_pow(10, flo_len));
	OLED_ShowNum(page, column, (int)dec, int_len, show_sign, char_size, char_color);
	if(show_sign && dec < 0)
	{
		OLED_ShowChr(page, column+(int_len+1)*char_size, '.', char_size, char_color);
		OLED_ShowNum(page, column+(int_len+2)*char_size, -flo, flo_len, 0, char_size, char_color);
	}
	else if((show_sign && dec >= 0))
	{
		OLED_ShowChr(page, column+(int_len+1)*char_size, '.', char_size, char_color);
		OLED_ShowNum(page, column+(int_len+2)*char_size, flo, flo_len, 0, char_size, char_color);
	}
	else if(!show_sign && dec < 0)
	{
		OLED_ShowChr(page, column+(int_len)*char_size, '.', char_size, char_color);
		OLED_ShowNum(page, column+(int_len+1)*char_size, -flo, flo_len, 0, char_size, char_color);
	}
	else
	{
		OLED_ShowChr(page, column+(int_len)*char_size, '.', char_size, char_color);
		OLED_ShowNum(page, column+(int_len+1)*char_size, flo, flo_len, 0, char_size, char_color);
	}
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，对显存缓冲写入一个16X16像素的中文字符，这个函数不会对实际的OLED直接造成影响
 * @param page 开始页 输入 0~7
 * @param column 开始列 输入 0~127
 * @param CH16X16 需要写入的字符所在的数组，它应该保存在一个CH16X16[][32]的数组里
 * @param n 这个数组的第几个字符
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_GRAM_ShowCHInese(uint8_t page, uint8_t column, uint8_t CH16X16[][32], uint8_t n, uint8_t char_color)
{
	uint8_t i;
	if(char_color)
	{
		for(i = 0; i < 16; i++)
		OLED_GRAM_WriteByte(page, column+i, ~(CH16X16[n][i]));
		for(i = 0; i < 16; i++)
		OLED_GRAM_WriteByte(page+1, column+i, ~(CH16X16[n][i+16]));
	}
	else
	{
		for(i = 0; i < 16; i++)
		OLED_GRAM_WriteByte(page, column+i, CH16X16[n][i]);
		for(i = 0; i < 16; i++)
		OLED_GRAM_WriteByte(page+1, column+i, CH16X16[n][i+16]);
	}
}

/** 
 * @brief 对OLED写入一个16X16像素的中文字符
 * @param page 开始页 输入 0~7
 * @param column 开始列 输入 0~127
 * @param CH16X16 需要写入的字符，它应该保存在一个CH[][32]的数组里
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_ShowCHinese(uint8_t page, uint8_t column, uint8_t CH16X16[][32], uint8_t n,uint8_t char_color)
{
	OLED_GRAM_ShowCHInese(page, column, CH16X16, n, char_color);
	OLED_GRAM_RefreshPart(page, column, column+15);
	OLED_GRAM_RefreshPart(page+1, column, column+15);
}

/** 
 * @brief 将显存缓冲数组看成由128x64的像素点组成，在缓冲数组上绘制一定大小的图片，这个函数不会对实际的OLED直接造成影响
 * @param page 开始页 输入 0~7
 * @param column 开始列 输入 0~127
 * @param BMP 需要绘制的图片，它应该保存在一个BMP[pag_wid*col_len]的数组里
 * @param pag_wid 这个图片占据屏幕的页宽
 * @param col_len 这个图片占据屏幕的列长
 * @param char_color 字符颜色，选用CHAR_COLOR_WHITE（黑底白字）和CHAR_COLOR_BLACK（白底黑字）
 */
void OLED_GRAM_DrawBMP(uint8_t page, uint8_t column, uint8_t* BMP, uint8_t pag_wid, uint8_t col_len, uint8_t char_color)
{
	uint8_t l,w;
	if(char_color)
	{	
		for(w = 0; w < pag_wid; w++)
			for(l = 0; l < col_len; l++)
			OLED_GRAM_WriteByte(page+w, column+l, ~(BMP[w*col_len+l]));
	}
	else
	{
		for(w = 0; w < pag_wid; w++)
			for(l = 0; l < col_len; l++)
				OLED_GRAM_WriteByte(page+w, column+l, BMP[w*col_len+l]);	
	}
}

/**
 * @brief 在OLED上绘制一定大小的图片
 * @param page 开始页 输入 0~7
 * @param column 开始列 输入 0~127
 * @param BMP 需要绘制的图片，它应该保存在一个数组里
 * @param pag_wid 这个图片占据屏幕的页宽
 * @param col_len 这个图片占据屏幕的列长
 * @param char_color 可以将图片反色显示，选用CHAR_COLOR_WHITE（正常）和CHAR_COLOR_BLACK（反色）
 */
void OLED_DrawBMP(uint8_t page, uint8_t column, uint8_t* BMP, uint8_t pag_wid, uint8_t col_len, uint8_t char_color)
{
	OLED_GRAM_DrawBMP(page, column, BMP, pag_wid, col_len, char_color);
	OLED_GRAM_Refresh();
}
/** 
 * @brief 开启屏幕显示
 */
void OLED_DisplayOn(void)
{
	uint8_t DisplayOn_CMD[3]={
	0X8D, 									//SET DCDC命令
	0X8D,									//DCDC ON
	0XAF};									//DISPLAY ON 打开显示
	OLED_WriteMultiCmd(DisplayOn_CMD, sizeof(DisplayOn_CMD)/sizeof(DisplayOn_CMD[0]));
}

/** 
 * @brief 关闭屏幕显示
 */
void OLED_DisplayOff(void)
{
	uint8_t DisplayOff_CMD[3]={
	0X8D,									//SET DCDC命令
	0X10,									//DCDC OFF
	0XAE};									//DISPLAY OFF 关闭显示
	OLED_WriteMultiCmd(DisplayOff_CMD, sizeof(DisplayOff_CMD)/sizeof(DisplayOff_CMD[0]));
}

/** 
 * @brief 修改OLED屏幕背景颜色
 * @param bg_color OLED屏幕背景颜色，默认黑，选用 BG_COLOR_BLACK 和 BG_COLOR_WHITE
 */
void OLED_BackgroundColor(uint8_t bg_color)
{
	OLED_WriteCmd(bg_color);
}


