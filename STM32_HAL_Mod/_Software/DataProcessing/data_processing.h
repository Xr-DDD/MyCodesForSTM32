#ifndef _DATA_PROCESSING_H_
#define _DATA_PROCESSING_H_

#include "stm32f1xx_hal.h"

float DataTrend(float arr[], uint8_t n); //分析一组数据是上升趋势还是下降趋势，返回最小二乘法斜率
void SildingWindow(float arr_window[], uint8_t n, float data); //以滑动窗口形式收集数据 先进先出
void ShellSort(float arr_origin[], float arr_order[], uint8_t n); //希尔排序
float MedianFilter(float arr_order[], uint8_t n); //取有序数组的中间一半数据计算平均值

#endif
