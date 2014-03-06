/*
 * draw_task.h
 *
 *  Created on: 3/6/2014
 *      Author: hawkdtw
 *       email: hawkdtw@gmail.com
 */

#ifndef __DRAW_TASK_H__
#define __DRAW_TASK_H__
/*
 * Includes
 */

/*
 * Typedef
 */
typedef enum{
	DISP_INIT = 0,
	DISP_WAIT_VCC12,
	DISP_PLAY,
	DISP_SETTING,
}DISP_STATE;

typedef enum{
	DISP_FOLDER_INIT = 0,
	DISP_FOLDER_UP,
	DISP_FOLDER_DOWN,
	DISP_FOLDER_IDLE,
	DISP_FOLDER_EXIT,
}DISP_FOLDER_STATE;

typedef enum{
	DISP_SHUTDOWN_INIT = 0,
	DISP_SHUTDOWN_1,
	DISP_SHUTDOWN_2,
	DISP_SHUTDOWN_3,
	DISP_SHUTDOWN_4,
}DISP_SHUTDOWN_STATE;

/*
 * Macro
 */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void App_Task_Disp(void);

/*
 * Private variables and functions
 */

#endif
/* End of file */
