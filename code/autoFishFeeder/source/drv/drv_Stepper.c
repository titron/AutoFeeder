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

/* Global variables */
float tpm;
long ppt;
step_dir_t sens;
int angle_afaire;
long nbpas_afaire;
// int mot_pin1;
// int mot_pin2;
// int mot_pin3;
// int mot_pin4;

/* Private variables */
static void tourne1pasCCW();
static void tourne1pasCW();
static void tourneSTOP();
static long _nbpas_faits;
static BOOLEAN _arretnbpas;
static float _delaivitesse;
static float _tpm;
static long _ppt;
static step_dir_t _sens;
static int _angle_afaire;
static long _nbpas_afaire;
// static int _mot_pin1;
// static int _mot_pin2;
// static int _mot_pin3;
// static int _mot_pin4;
static int _pos_rel;

/* private function */
static void drv_stepper_tourne1pasCCW(void);
static void drv_stepper_tourne1pasCW(void);
static void drv_stepper_tourneSTOP(void);

void drv_stepper_init(long ppt) 
{
  // _mot_pin1 = mot_pin1;
  // _mot_pin2 = mot_pin2;
  // _mot_pin3 = mot_pin3;
  // _mot_pin4 = mot_pin4;
  _ppt = ppt;
  tpm = 14.0;
  _tpm = 14.0;
  _ppt = ppt;
  _sens = STEPPER_DIR_CW;
  _angle_afaire = 0;
  _nbpas_afaire = 0;
  _nbpas_faits = 0;
  _pos_rel = 0;
  _arretnbpas = FALSE;
  _delaivitesse = 60000 / ( _tpm * _ppt * 8); // le delai pour un 8eme de pas

  PORT_STEPPER_A = (U8) STEPPER_OUT_HIGH;
	PORT_DIR_STEPPER_A = (U8) 1; /* direction is output */
	PORT_STEPPER_A = (U8) STEPPER_OUT_HIGH;

  PORT_STEPPER_B = (U8) STEPPER_OUT_HIGH;
	PORT_DIR_STEPPER_B = (U8) 1; /* direction is output */
	PORT_STEPPER_B = (U8) STEPPER_OUT_HIGH;

  PORT_STEPPER_C = (U8) STEPPER_OUT_HIGH;
	PORT_DIR_STEPPER_C = (U8) 1; /* direction is output */
	PORT_STEPPER_C = (U8) STEPPER_OUT_HIGH;

  PORT_STEPPER_D = (U8) STEPPER_OUT_HIGH;
	PORT_DIR_STEPPER_D = (U8) 1; /* direction is output */
	PORT_STEPPER_D = (U8) STEPPER_OUT_HIGH;
}


void drv_stepper_setRPM (float tpm) {
  _tpm = tpm;
  _delaivitesse = 60000 / ( _tpm * _ppt * 8); // le delai pour un 8eme de pas
}


void drv_stepper_setDirection (step_dir_t sens) {
	_sens = sens;
}


void drv_stepper_setAngle (int angle_afaire) {
  if (angle_afaire != 0){
    _nbpas_afaire = angle_afaire * _ppt / 360L;
	_nbpas_faits = 0;
	_arretnbpas = FALSE;
  };
}


void drv_stepper_setSteps (long nbpas_afaire) {
    _nbpas_afaire = nbpas_afaire;
	_nbpas_faits = 0;
	_arretnbpas = FALSE;
}


void drv_stepper_returnToOrigin (){
	if (_pos_rel < 0) {_sens=STEPPER_DIR_CW;}
    if (_pos_rel == 0) {_sens=STEPPER_DIR_STOP;}
    if (_pos_rel > 0) {_sens=STEPPER_DIR_CCW;}
    _nbpas_afaire = (abs(_pos_rel) % _ppt) -1;
	_nbpas_faits = 0;
    _arretnbpas = FALSE;
}


void drv_stepper_rewindFully (){
	if (_pos_rel < 0) {_sens=STEPPER_DIR_CW;}
    if (_pos_rel == 0) {_sens=STEPPER_DIR_STOP;}
    if (_pos_rel > 0) {_sens=STEPPER_DIR_CCW;}
    _nbpas_afaire = abs(_pos_rel) -1;
	_nbpas_faits = 0;
    _arretnbpas = FALSE;
}


void drv_stepper_setOrigin(){
	_pos_rel = 0;
}


void drv_stepper_Run (){

  if (!_arretnbpas) {
    if (_sens == STEPPER_DIR_CW) {
      drv_stepper_tourne1pasCW ();
      _pos_rel++;
    }
    else if (_sens == STEPPER_DIR_CCW) {
      drv_stepper_tourne1pasCCW();
      _pos_rel--;
    }
    else if (_sens == STEPPER_DIR_STOP) {
      drv_stepper_tourneSTOP();
    }
  }
  if (_arretnbpas) {
    drv_stepper_tourneSTOP();
  }

  // nombre de pas defini --------------------------
  if (_nbpas_afaire != 0 && _nbpas_faits < _nbpas_afaire){
    _nbpas_faits ++;
  }
  if (_nbpas_faits >= _nbpas_afaire && _nbpas_afaire != 0){
    _arretnbpas = TRUE;
  }

}
static void drv_stepper_digitalWrite(int pin, int level)
{
  if((PORT_STEPPER_A == pin) ||
    (PORT_STEPPER_B == pin) ||
    (PORT_STEPPER_C == pin) ||
    (PORT_STEPPER_D == pin))
  {
      pin = level;
  }
  else
  {
    /* Error happened */
  }
}

static void drv_stepper_tourne1pasCCW(void)
{
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);

}


static void drv_stepper_tourne1pasCW(void)
{
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);

  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_HIGH);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);
  
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_HIGH);
  delay (_delaivitesse);
  
}

//---------------------------------------------------------
static void drv_stepper_tourneSTOP(void) 
{
  drv_stepper_digitalWrite (PORT_STEPPER_A, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_B, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_C, STEPPER_OUT_LOW);
  drv_stepper_digitalWrite (PORT_STEPPER_D, STEPPER_OUT_LOW);

}