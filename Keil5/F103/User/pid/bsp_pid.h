#ifndef __BSP_PID_H
#define __BSP_PID_H

// TODO: ��������
#define KP		1
#define KI		0
#define KD		0

#define UKMAX 5   // ����޷�ֵ

typedef struct{
	double Kp, Ki, Kd;
	double Esum, Ek, Ek_1;
	double Sv, Mv;
	double Uk;
} _pid;

void PID_Init(void);
void PID_Calc(void);

#endif
