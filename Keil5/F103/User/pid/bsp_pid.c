#include "bsp_pid.h"
#include <stdlib.h>

extern _pid* pid;

void PID_Init(void){
	
	pid = malloc(sizeof(_pid));
	
	pid->Kp = KP;
	pid->Ki = KI;
	pid->Kd = KD;
	
	pid->Ek = 0;
	pid->Ek_1 = 0;
	pid->Esum = 0;
	
	pid->Mv = 0;
	pid->Sv = 0;
	
	pid->Uk = 0;
}

	// u(k)= Kp*e(k) +
	//			 Ki*[e(1)+e(2)+...+e(k)] +
	// 			 Kd*[e(k)-e(k-1)]
void PID_Calc(void){
	
	pid->Ek = pid->Sv - pid->Mv;
	pid->Esum += pid->Ek;
	
	pid->Uk = pid->Kp * pid->Ek +
						pid->Ki * pid->Esum +
						pid->Kd * (pid->Ek - pid->Ek_1);
	
	pid->Ek_1 = pid->Ek;

	// Êä³öÏÞ·ù
	if(pid->Uk> UKMAX) pid->Uk = UKMAX;
	if(pid->Uk<0)			 pid->Uk = 0;
}

