/*
  Stepper.h V 0.1 - Library for controlling
  a 28BYJ-48 stepper motor
  with a ULN2003APG driver
  Created by Olivier Friker, September 04, 2016.
  Not released into the public domain.
*/

#ifndef Stepper_h
#define Stepper_h
 
#include "basictype.h"
#include "sfr_r82b.h"

/*
 * Macro
 */
#define PORT_STEPPER_A			p1_0
#define PORT_STEPPER_B			p1_1
#define PORT_STEPPER_C			p1_2
#define PORT_STEPPER_D			p1_3
#define PORT_DIR_STEPPER_A	pd1_0
#define PORT_DIR_STEPPER_B	pd1_1
#define PORT_DIR_STEPPER_C	pd1_2
#define PORT_DIR_STEPPER_D	pd1_3

#define STEPPER_OUT_HIGH		(U8)1
#define STEPPER_OUT_LOW		  (U8)0

/* typedef */
typedef enum {
  STEPPER_DIR_CW,
  STEPPER_DIR_CCW,
  STEPPER_DIR_STOP,
}step_dir_t;

/* public function */
void drv_stepper_init(long ppt);
void drv_stepper_setRPM(float tpm);
void drv_stepper_setDirection(step_dir_t sens); // (CW, CCW ou STOP)
void drv_stepper_setAngle (int angle_afaire); // (1 to 360)
void drv_stepper_setSteps (long nbpas_afaire);
void drv_stepper_returnToOrigin ();
void drv_stepper_rewindFully ();
void drv_stepper_setOrigin();
void drv_stepper_Run ();

#endif

