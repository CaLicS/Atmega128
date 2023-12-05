#include "main.h"
#include "motor_tc2.h"
#include "led_sw.h"

int main(void)
{
	mtr_tc2_init();
	led_init();
	sw_init();
	
	int con = FALSE, idir = DIR_CW, ledon = TRUE;
	int spd[3] = {30, 60, 100};
	int i = 0;
	
	
	while(TRUE){
		if(sw_onoff(SW1)){
			con = !con;
			if(con){
				mtr_tc2_dir_spd(idir, spd[i]);
			}
			else{
				mtr_tc2_dir_spd(idir, 0);
				led_off(LED_ALL);
				if(idir == DIR_CW) idir = DIR_CCW;
				else idir = DIR_CW;
			}
		}
		if(sw_onoff(SW2) && con){
			i++;
			if(i == 3) i = 0;
			mtr_tc2_dir_spd(idir, spd[i]);
		}
		if(con){
			if(ledon && i == 0) 
				led_off(LED_ALL), led_on(LED1), led_on(LED2);
			else if(ledon && i == 1)
				led_off(LED_ALL), led_on(LED3), led_on(LED4);
			else if(ledon && i == 2)
				led_off(LED_ALL), led_on(LED5), led_on(LED6);
			else
				led_off(LED_ALL);
			ledon = !ledon;
			_delay_ms(100);
		}
		
	}
}


