/*
  OliStepper V 1.1 - Library for controlling
  a 28BYJ-48 stepper motor
  with a ULN2003APG driver
  Created by Olivier Friker, September 04, 2016.
  Not released into the public domain.
*/

/* include files */
#include <stdlib.h>
#include "drv_Stepper.h"

/*** private function ***/
static int drv_stepper_calcDelay(int rpm);  // calcs microsecond step delay for given rpm
static int drv_stepper_calcRpm(int _delay); // calcs rpm for given delay in microseconds
// static int calcRpm(void){
// 	return calcRpm(delay); // calcs rpm from current delay
// }

static void drv_stepper_seqCW(void);
static void drv_stepper_seqCCW(void);
static void drv_stepper_seq(int seqNum); // send specific sequence num to driver
static void drv_stepper_digitalWrite(int stepperPin, int pattern);
static void drv_stepper_delayMicroseconds(int delay);

/*** private variables ***/
static int pins[4];   // defaults to pins {8,9,10,11} (in1,in2,in3,in4 on the driver board)
static int pin_dir[4];   // defaults to pins {8,9,10,11} (in1,in2,in3,in4 on the driver board)

static int stepN = 0; // keeps track of step position
                      // 0-4095 (4096 mini-steps / revolution) or maybe 4076...
static int totalSteps = 4096;
static int delay = 900; // microsecond delay between steps
                        // 900 ~= 16.25 rpm
                        // low speed (high torque) = 1465 ~= 1 rpm
                        // high speed (low torque) = 600 ~=  24 rpm
static int seqN = -1;   // keeps track of sequence number
// variables for non-blocking moves:
// static unsigned long lastStepTime; // time in microseconds that last step happened
static int stepsLeft = 0;          // steps left to move, neg for counter-clockwise

/*****************************************************/
/* public functions */
/*****************************************************/
void drv_stepper_init(void)
{
  int phase_index;

  pins[0] = PORT_STEPPER_A;
  pins[1] = PORT_STEPPER_B;
  pins[2] = PORT_STEPPER_C;
  pins[3] = PORT_STEPPER_D;
  pin_dir[0] = PORT_DIR_STEPPER_A;
  pin_dir[1] = PORT_DIR_STEPPER_B;
  pin_dir[2] = PORT_DIR_STEPPER_C;
  pin_dir[3] = PORT_DIR_STEPPER_D;

  //for(phase_index = 0;phase_index<4;phase_index++)
  //{
  //  pins[phase_index] = (U8)STEPPER_OUT_HIGH;
  //  pin_dir[phase_index] = PORT_MODE_OUTPUT;/* direction is output */
  //}
}

void drv_stepper_setRpm(int rpm)
{

  delay = drv_stepper_calcDelay(rpm);
}

void drv_stepper_set4076StepMode(void)
{
  totalSteps = 4076;
}

void drv_stepper_setTotalSteps(int numSteps)
{
  totalSteps = numSteps;
}

void drv_stepper_move(BOOLEAN clockwise, int numSteps)
{
  int n;

  for (n = 0; n < numSteps; n++)
  {
    drv_stepper_step(clockwise);
  }
}

void drv_stepper_moveTo(BOOLEAN clockwise, int toStep)
{
  // keep to 0-(totalSteps-1) range
  if (toStep >= totalSteps)
    toStep %= totalSteps;
  else if (toStep < 0)
  {
    toStep %= totalSteps; // returns negative if toStep not multiple of totalSteps
    if (toStep < 0)
      toStep += totalSteps; // shift into 0-(totalSteps-1) range
  }
  while (stepN != toStep)
  {
    drv_stepper_step(clockwise);
  }
}

void drv_stepper_moveDegrees(BOOLEAN clockwise, int deg)
{
  int nSteps;

  nSteps = (unsigned long)deg * totalSteps / 360;
  drv_stepper_move(clockwise, nSteps);
}

void drv_stepper_moveToDegree(BOOLEAN clockwise, int deg)
{
  int toStep;

  // keep to 0-359 range
  if (deg >= 360)
    deg %= 360;
  else if (deg < 0)
  {
    deg %= 360; // returns negative if deg not multiple of 360
    if (deg < 0)
      deg += 360; // shift into 0-359 range
  }

  toStep = deg * totalSteps / 360;
  drv_stepper_moveTo(clockwise, toStep);
}

void drv_stepper_moveCW(int numSteps)
{
  drv_stepper_move(TRUE, numSteps);
}

void drv_stepper_moveCCW(int numSteps)
{
  drv_stepper_move(FALSE, numSteps);
}

void drv_stepper_moveToCW(int toStep)
{
  drv_stepper_moveTo(TRUE, toStep);
}

void drv_stepper_moveToCCW(int toStep)
{
  drv_stepper_moveTo(FALSE, toStep);
}

void drv_stepper_moveDegreesCW(int deg)
{
  drv_stepper_moveDegrees(TRUE, deg);
}

void drv_stepper_moveDegreesCCW(int deg)
{
  drv_stepper_moveDegrees(FALSE, deg);
}

void drv_stepper_moveToDegreeCW(int deg)
{
  drv_stepper_moveToDegree(TRUE, deg);
}

void drv_stepper_moveToDegreeCCW(int deg)
{
  drv_stepper_moveToDegree(FALSE, deg);
}

void drv_stepper_newMoveCW(int numSteps)
{
  drv_stepper_newMove(TRUE, numSteps);
}

void drv_stepper_newMoveCCW(int numSteps)
{
  drv_stepper_newMove(FALSE, numSteps);
}

void drv_stepper_newMoveToCW(int toStep)
{
  drv_stepper_newMoveTo(TRUE, toStep);
}

void drv_stepper_newMoveToCCW(int toStep)
{
  drv_stepper_newMoveTo(FALSE, toStep);
}

void drv_stepper_newMoveDegreesCW(int deg)
{
  drv_stepper_newMoveDegrees(TRUE, deg);
}

void drv_stepper_newMoveDegreesCCW(int deg)
{
  drv_stepper_newMoveDegrees(FALSE, deg);
}

void drv_stepper_newMoveToDegreeCW(int deg)
{
  drv_stepper_newMoveToDegree(TRUE, deg);
}

void drv_stepper_newMoveToDegreeCCW(int deg)
{
  drv_stepper_newMoveToDegree(FALSE, deg);
}

void drv_stepper_stepCW(void)
{
  drv_stepper_step(TRUE);
} // move 1 step clockwise

void drv_stepper_stepCCW(void)
{
  drv_stepper_step(FALSE);
} // move 1 step counter-clockwise

int drv_stepper_getStep(void)
{
  return stepN;
} // returns current miniStep position

int drv_stepper_getDelay(void)
{
  return delay;
} // returns current delay (microseconds)

int drv_stepper_getRpm(void)
{
  return drv_stepper_calcRpm(delay);
} // returns current rpm

int drv_stepper_getPin(int p)
{
  if (p < 4)
    return pins[p]; // returns pin #
  return 0;         // default 0
}

int drv_stepper_getStepsLeft(void)
{
  return stepsLeft;
} // returns steps left in current move

// NON-BLOCKING MOVES

void drv_stepper_newMove(BOOLEAN clockwise, int numSteps)
{
  // numSteps sign ignored
  // stepsLeft signed positive if clockwise, neg if ccw
  if (clockwise)
    stepsLeft = abs(numSteps);
  else
    stepsLeft = -1 * abs(numSteps);

  // lastStepTime = micros();
}

void drv_stepper_newMoveTo(BOOLEAN clockwise, int toStep)
{
  // keep toStep in 0-(totalSteps-1) range
  if (toStep >= totalSteps)
    toStep %= totalSteps;
  else if (toStep < 0)
  {
    toStep %= totalSteps; // returns negative if toStep not multiple of totalSteps
    if (toStep < 0)
      toStep += totalSteps; // shift into 0-(totalSteps-1) range
  }

  if (clockwise)
    stepsLeft = abs(toStep - stepN);
  // clockwise: simple diff, always pos
  else
    stepsLeft = -1 * (totalSteps - abs(toStep - stepN));
  // counter-clockwise: totalSteps - diff, made neg

  // lastStepTime = micros();
}

void drv_stepper_newMoveDegrees(BOOLEAN clockwise, int deg)
{
  int nSteps = (unsigned long)deg * totalSteps / 360;
  drv_stepper_newMove(clockwise, nSteps);
}

void drv_stepper_newMoveToDegree(BOOLEAN clockwise, int deg)
{
  int toStep;

  // keep to 0-359 range
  if (deg >= 360)
    deg %= 360;
  else if (deg < 0)
  {
    deg %= 360; // returns negative if deg not multiple of 360
    if (deg < 0)
      deg += 360; // shift into 0-359 range
  }

  toStep = deg * totalSteps / 360;
  drv_stepper_newMoveTo(clockwise, toStep);
}

void drv_stepper_run(void)
{
  // if (micros() - lastStepTime >= delay)
  // { // if time for step
    if (stepsLeft > 0)
    { // clockwise
      drv_stepper_stepCW();
      stepsLeft--;
    }
    else if (stepsLeft < 0)
    { // counter-clockwise
      drv_stepper_stepCCW();
      stepsLeft++;
    }

  //   lastStepTime = micros();
  // }
}

void drv_stepper_stop(void)
{
  stepsLeft = 0;
}

void drv_stepper_step(BOOLEAN clockwise)
{
  if (clockwise)
    drv_stepper_seqCW();
  else
    drv_stepper_seqCCW();
}

void drv_stepper_off(void)
{
  int p;

  for (p = 0; p < 4; p++)
    drv_stepper_digitalWrite(pins[p], 0);
}

/*****************************************************/
/* private functions */
/*****************************************************/

static int drv_stepper_calcDelay(int rpm)
{
  unsigned long d;

  if (rpm < 6)
    return delay; // will overheat, no change
  else if (rpm >= 24)
    return 600; // highest speed

  d = 60000000 / (totalSteps * (unsigned long)rpm);
  // in range: 600-1465 microseconds (24-1 rpm)
  return (int)d;
}

static int drv_stepper_calcRpm(int _delay)
{
  unsigned long rpm;

  rpm = 60000000 / (unsigned long)_delay / totalSteps;
  return (int)rpm;
}

static void drv_stepper_seqCW(void)
{
  seqN++;
  if (seqN > 7)
    seqN = 0; // roll over to A seq
  drv_stepper_seq(seqN);

  stepN++; // track miniSteps
  if (stepN >= totalSteps)
  {
    stepN -= totalSteps; // keep stepN within 0-(totalSteps-1)
  }
}

static void drv_stepper_seqCCW(void)
{
  seqN--;
  if (seqN < 0)
    seqN = 7; // roll over to DA seq
  drv_stepper_seq(seqN);

  stepN--; // track miniSteps
  if (stepN < 0)
  {
    stepN += totalSteps; // keep stepN within 0-(totalSteps-1)
  }
}

static void drv_stepper_digitalWrite(int stepperPin, int pattern)
{
  stepperPin = pattern;
}

/*
* Todo:
*   should replace with precise timer delay in microsecond
*/
static void drv_stepper_delayMicroseconds(int delay)
{
  do{
    delay--;
  }while(delay > 0);
}

static void drv_stepper_seq(int seqNum)
{
  int pattern[4];
  int p;
  // A,B,C,D HIGH/LOW pattern to write to driver board

  switch (seqNum)
  {
    case 0:
    {
      pattern[0] = STEPPER_OUT_HIGH;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
    case 1:
    {
      pattern[0] = STEPPER_OUT_HIGH;
      pattern[1] = STEPPER_OUT_HIGH;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
    case 2:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_HIGH;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
    case 3:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_HIGH;
      pattern[2] = STEPPER_OUT_HIGH;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
    case 4:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_HIGH;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
    case 5:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_HIGH;
      pattern[3] = STEPPER_OUT_HIGH;
      break;
    }
    case 6:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_HIGH;
      break;
    }
    case 7:
    {
      pattern[0] = STEPPER_OUT_HIGH;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_HIGH;
      break;
    }
    default:
    {
      pattern[0] = STEPPER_OUT_LOW;
      pattern[1] = STEPPER_OUT_LOW;
      pattern[2] = STEPPER_OUT_LOW;
      pattern[3] = STEPPER_OUT_LOW;
      break;
    }
  }

  // write pattern to pins
  for (p = 0; p < 4; p++)
  {
    drv_stepper_digitalWrite(pins[p], pattern[p]);
  }
  drv_stepper_delayMicroseconds(delay);
}

/* End of file */