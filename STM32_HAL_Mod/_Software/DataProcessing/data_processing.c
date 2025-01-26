#include "data_processing.h"


float DataTrend(float arr[], uint8_t n)
{
		float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
		for(uint8_t i = 0; i < n; i++)
		{
				sum_x += i;
				sum_y += arr[i];
				sum_xy += i*arr[i];
				sum_x2 += i * i;
		}
		float slope = (n * sum_xy - sum_x *sum_y) / (n * sum_x2 - sum_x * sum_x);
		return slope;
}

void SildingWindow(float arr_window[], uint8_t n, float data)
{
		if(data != arr_window[n - 1])
		{
				for(uint8_t i = 0; i < n - 1; i++)
				{
						arr_window[i] = arr_window[i + 1];
				}
				arr_window[n - 1] = data;
		}
}

void ShellSort(float arr_origin[], float arr_order[], uint8_t n)
{
		for(uint8_t i = 0; i < n; i++)
		{
				arr_order[i] = arr_origin[i];
		}
		for(uint8_t gap = n/2; gap > 0; gap /= 2)
		{
				for(uint8_t i = 0; i < n; i++)
				{
						uint8_t temp = arr_order[i];
						uint8_t j;
						for(j = i; j>= gap && arr_order[j - gap] > temp; j -= gap)
						{
								arr_order[j] = arr_order[j - gap];
						}
						arr_order[j] = temp;
				}
		}
}

float MedianFilter(float arr_order[], uint8_t n)
{
    float result = 0;
    for(uint8_t i = n/4 + 1; i < n*3/4 + 1; i++)
    {
            result += arr_order[i];
    }
    result /= (n/2);
    return result;
}
