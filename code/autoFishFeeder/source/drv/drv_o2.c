#include "drv_o2.h"


void drv_O2_init(void)
{
  int phase_index;

  PORT_ADD_O2 = O2_OUT_HIGH;
  PORT_DIR_O2 = PORT_MODE_OUTPUT;/* direction is output */

}


/*
 * sys_AddingO2
 * start adding O2.
 */
void sys_AddingO2(void)
{
	// vsysFeedTime = 0;
	drv_Led_SetState(LED_O2, LED_ON);
	// drv_Pwr_5V_TurnOn();

	PORT_ADD_O2 = O2_OUT_LOW;
}

/*
 * sys_stopO2
 */
void sys_stopO2(void)
{
	// vsysFeedTime = 0;
	drv_Led_SetState(LED_O2, LED_OFF);
	//O2 complete now
	PORT_ADD_O2 = O2_OUT_HIGH;
}

/* End of file */