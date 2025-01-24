#ifndef _PID_H_
#define _PID_H_

typedef struct
{
    float kp,ki,kd;
    float error,error_last,error_last_last,error_total;
    float output;
    float integral_max,output_max;
}PID_ValueStructure;

void PID_Init(PID_ValueStructure* pid);
void PID_ClearHistory(PID_ValueStructure* pid);
void PID_SetParam_LIMIT(PID_ValueStructure* pid, float integral_max, float output_max);
void PID_SetParam_PID(PID_ValueStructure* pid, float kp, float ki, float kd);
float PID_Posi_Control(PID_ValueStructure* pid, float target, float feedback);
float PID_Diff_Control(PID_ValueStructure* pid, float target, float feedback);


#endif
/*example*/
/*
    motor_speed = PID_Position(&pid, 0, mpu6050.pitch);
    MOTOR_SetSpeed(motor_speed);

*/

