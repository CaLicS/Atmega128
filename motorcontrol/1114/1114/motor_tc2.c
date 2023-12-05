#include "motor_tc2.h"

void mtr_tc2_init(void)
{
	DDRB |= 0xC0;	// 1100_0000, 포트 PB7 & PB6을 출력으로 설정
	PORTB &= 0x3F;	// 0011_1111, 포트 PB7 & PB6에 0 출력

	// 타이머/카운터2 설정
	TCCR2 = 0x68;		// 0110_1000 : OC2 사용, Fast PWM 모드, non-inverting mode, 타이머/카운터2 정지
	TCNT2 = 0;			// 카운터 레지스터 클리어
	OCR2 = 0;			// 비교값 설정
}

// PWM 파형의 듀티비 제어 --> DC 모터 구동 속도 제어
// iSpeed: (0 - 100) --> (듀티비: 0% - 100%)
void mtr_tc2_dir_spd(int iDir, uint uSpeed)
{
	if(uSpeed > 100) uSpeed = 100;	// 100으로 제한
	// OCR2 설정 --> PWM 파형 듀티비 설정
	OCR2 = (uint)(255. * (float)uSpeed / 100.);

	if(iDir == DIR_CW) {
		PORTB &= 0xBF;	// 1011_1111, 포트 PB6에 0 출력
		// 타이머/카운터2 구동
		TCCR2 = (TCCR2 & 0xC8) | 0x24;	// XX10_X100, non-inverting mode, 프리스케일러 = clk/256
	} else {
		PORTB |= 0x40;	// 0100_0000, 포트 PB6에 1 출력
		// 타이머/카운터2 구동
		TCCR2 = (TCCR2 & 0xC8) | 0x34;	// XX11_X100, inverting mode, 프리스케일러 = clk/256
	}
}
 
