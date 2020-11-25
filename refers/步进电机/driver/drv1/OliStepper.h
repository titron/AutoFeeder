/*
  OliStepper.h V 0.1 - Library for controlling
  a 28BYJ-48 stepper motor
  with a ULN2003APG driver
  Created by Olivier Friker, September 04, 2016.
  Not released into the public domain.
*/

#ifndef OliStepper_h
#define OliStepper_h
 
#include <Arduino.h>

class OliStepper {
  
public:
	OliStepper (int mot_pin1, int mot_pin2, int mot_pin3, int mot_pin4, long ppt);
	void setRPM(float tpm);
	void setDirection(word sens); // (CW, CCW ou STOP)
	void setAngle (int angle_afaire); // (1 to 360)
	void setSteps (long nbpas_afaire);
	void returnToOrigin ();
	void rewindFully ();
	void setOrigin();
	void oliRun ();
	float tpm;
	long ppt;
	word sens;
	int angle_afaire;
	long nbpas_afaire;
  int mot_pin1;
  int mot_pin2;
  int mot_pin3;
  int mot_pin4;


private:
  void tourne1pasCCW();
  void tourne1pasCW();
  void tourneSTOP();
  long _nbpas_faits;
  boolean _arretnbpas;
  float _delaivitesse;
  float _tpm;
  long _ppt;
  word _sens;
  int _angle_afaire;
  long _nbpas_afaire;
  int _mot_pin1;
  int _mot_pin2;
  int _mot_pin3;
  int _mot_pin4;
  int _pos_rel;

};

#endif

