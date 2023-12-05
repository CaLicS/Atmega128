#ifndef MOTOR_TC2_H_
#define MOTOR_TC2_H_

#include "main.h"

#define DIR_CW		0	// 시계 방향(clockwise)
#define DIR_CCW	1	// 반시계 방향(counterclockwise)

void mtr_tc2_init(void);
void mtr_tc2_dir_spd(int iDir, uint uSpeed);

#endif /* MOTOR_TC2_H_ */ 