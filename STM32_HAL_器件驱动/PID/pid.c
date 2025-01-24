#include "pid.h"

void PID_Init(PID_ValueStructure* pid)
{
    pid.kp = 0;
    pid.ki = 0;
    pid.kd = 0;
    pid.error = 0;
    pid.error_last = 0;
    pid.error_last_last = 0;
    pid.error_total = 0;
    pid.output = 0;
    pid.integral_max = 0;
    pid.output_max = 0;
}

void PID_ClearHistory(PID_ValueStructure* pid)
{
    pid.error = 0;
    pid.error_last = 0;
    pid.error_last_last = 0;
    pid.error_total = 0;
    pid.output = 0;
}

void PID_SetParam_LIMIT(PID_ValueStructure* pid, float integral_max, float output_max)
{
    pid.integral_max = integral_max;
    pid.output_max = output_max;
}

void PID_SetParam_PID(PID_ValueStructure* pid, float kp, float ki, float kd)
{
    pid.kp = kp;
    pid.ki = ki;
    pid.kd = kd;
}

float PID_Posi_Control(PID_ValueStructure* pid, float target, float feedback)
{
    pid.error_last = pid.error;
    pid.error = target - feedback;
    pid.error_total += pid.error;
    if(pid.error_total > pid.integral_max)
    {
        pid.error_total = pid.integral_max;
    }else if(pid.error_total < -pid.integral_max)
    {
        pid.error_total = -pid.integral_max;
    }
    pid.output = pid.kp*pid.error + pid.ki*pid.error_total + pid.kd*(pid.error - pid.error_last);
    if(pid.output > pid.output_max)
    {
        pid.output = pid.output_max;
    }else if(pid.output < -pid.output_max)
    {
        pid.output = -pid.output_max;
    }
    return pid.output;
}

float PID_Diff_Control(PID_ValueStructure* pid, float target, float feedback)
{
    pid.error_last_last = pid.error_last;
    pid.error_last = pid.error;
    pid.error = target - feedback;
    pid.output = pid.kp*(pid.error - pid.error_last) + pid.ki*pid.error + pid.kd*(pid.error - 2*pid.error_last + pid.error_last_last);
    if(pid.output > pid.output_max)
    {
        pid.output = pid.output_max;
    }else if(pid.output < -pid.output_max)
    {
        pid.output = -pid.output_max;
    }
    return pid.output;
}


