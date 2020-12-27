/*  CheapStepper.h - 
	v0.2
	Library for the 28BYJ-48 stepper motor, using ULN2003 driver board
	https://arduino-info.wikispaces.com/SmallSteppers
	Library written by Tyler Henry, 6/2016
	uses 8-step sequence: A-AB-B-BC-C-CD-D-DA
	motor has gear ratio of either:
		64:1 (per manufacturer specs)
		or 
		63.68395:1 measured
			(see: http://forum.arduino.cc/index.php?topic=71964.15)
	* 64 steps per internal motor rev
	= 
	4096 total mini-steps / revolution
	or ~4076 (4075.7728) depending on exact gear ratio
	assumes 5v power source for rpm calc
*/

#ifndef Stepper_h
#define Stepper_h
 
#include "basictype.h"
#include "sfr_r82b.h"

/*
 * Macro
 */
//#define DEBUG_STEP 
 
#define PORT_STEPPER_A			p1_0
#define PORT_STEPPER_B			p1_1
#define PORT_STEPPER_C			p1_2
#define PORT_STEPPER_D			p1_3
#define PORT_STEPPER_INVALID			0
#define PORT_DIR_STEPPER_A	pd1_0
#define PORT_DIR_STEPPER_B	pd1_1
#define PORT_DIR_STEPPER_C	pd1_2
#define PORT_DIR_STEPPER_D	pd1_3
#define PORT_MODE_OUTPUT  	1

#define STEPPER_OUT_HIGH		(U8)1
#define STEPPER_OUT_LOW		  (U8)0

/*** public function ***/
void drv_stepper_init(void);
void drv_stepper_setRpm (int rpm); // sets speed (10-24 rpm, hi-low torque)
// <6 rpm blocked in code, may overheat
// 23-24rpm may skip

void drv_stepper_set4076StepMode(void);
void drv_stepper_setTotalSteps (int numSteps);
// allows custom # of steps (usually 4076)

// blocking! (pauses arduino until move is done)
void drv_stepper_move (BOOLEAN clockwise, int numSteps); // 4096 steps = 1 revolution
void drv_stepper_moveTo (BOOLEAN clockwise, int toStep); // move to specific step position
void drv_stepper_moveDegrees (BOOLEAN clockwise, int deg);
void drv_stepper_moveToDegree (BOOLEAN clockwise, int deg);

void drv_stepper_moveCW (int numSteps);
void drv_stepper_moveCCW (int numSteps);
void drv_stepper_moveToCW (int toStep);
void drv_stepper_moveToCCW (int toStep);
void drv_stepper_moveDegreesCW (int deg);
void drv_stepper_moveDegreesCCW (int deg);
void drv_stepper_moveToDegreeCW (int deg);
void drv_stepper_moveToDegreeCCW (int deg);

// non-blocking versions of move()
// call run() in loop to keep moving

void drv_stepper_newMove (BOOLEAN clockwise, int numSteps);
void drv_stepper_newMoveTo (BOOLEAN clockwise, int toStep);
void drv_stepper_newMoveDegrees (BOOLEAN clockwise, int deg);
void drv_stepper_newMoveToDegree (BOOLEAN clockwise, int deg);

void drv_stepper_run(void);
void drv_stepper_stop(void);
void drv_stepper_off(void);

void drv_stepper_newMoveCW(int numSteps);
void drv_stepper_newMoveCCW(int numSteps);
void drv_stepper_newMoveToCW(int toStep);
void drv_stepper_newMoveToCCW(int toStep);
void drv_stepper_newMoveDegreesCW(int deg);
void drv_stepper_newMoveDegreesCCW(int deg);
void drv_stepper_newMoveToDegreeCW(int deg);
void drv_stepper_newMoveToDegreeCCW(int deg);

void drv_stepper_step (BOOLEAN clockwise);
// move 1 step clockwise or counter-clockwise

void drv_stepper_stepCW (void);
void drv_stepper_stepCCW (void);

int drv_stepper_getStep(void);
int drv_stepper_getDelay(void);
int drv_stepper_getRpm(void);
// struct	bit_def drv_stepper_getPin(int p);
int drv_stepper_getStepsLeft(void);

#endif

