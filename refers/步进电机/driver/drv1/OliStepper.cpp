/*
  OliStepper V 1.1 - Library for controlling
  a 28BYJ-48 stepper motor
  with a ULN2003APG driver
  Created by Olivier Friker, September 04, 2016.
  Not released into the public domain.
*/

#include "OliStepper.h"



OliStepper::OliStepper (int mot_pin1, int mot_pin2, int mot_pin3, int mot_pin4, long ppt) {

  _mot_pin1 = mot_pin1;
  _mot_pin2 = mot_pin2;
  _mot_pin3 = mot_pin3;
  _mot_pin4 = mot_pin4;
  _ppt = ppt;
  tpm = 14.0;
  _tpm = 14.0;
  _ppt = ppt;
  _sens = "CW";
  _angle_afaire = 0;
  _nbpas_afaire = 0;
  _nbpas_faits = 0;
  _pos_rel = 0;
  _arretnbpas = false;
  _delaivitesse = 60000 / ( _tpm * _ppt * 8); // le delai pour un 8eme de pas

  pinMode (_mot_pin1, OUTPUT);
  pinMode (_mot_pin2, OUTPUT);
  pinMode (_mot_pin3, OUTPUT);
  pinMode (_mot_pin4, OUTPUT);
}



void OliStepper::setRPM (float tpm) {
  _tpm = tpm;
  _delaivitesse = 60000 / ( _tpm * _ppt * 8); // le delai pour un 8eme de pas
}


void OliStepper::setDirection (word sens) {
	_sens = sens;
}


void OliStepper::setAngle (int angle_afaire) {
  if (angle_afaire != 0){
    _nbpas_afaire = angle_afaire * _ppt / 360L;
	_nbpas_faits = 0;
	_arretnbpas = false;
  };
}


void OliStepper::setSteps (long nbpas_afaire) {
    _nbpas_afaire = nbpas_afaire;
	_nbpas_faits = 0;
	_arretnbpas = false;
}


void OliStepper::returnToOrigin (){
	if (_pos_rel < 0) {_sens="CW";}
    if (_pos_rel == 0) {_sens="STOP";}
    if (_pos_rel > 0) {_sens="CCW";}
    _nbpas_afaire = (abs(_pos_rel) % _ppt) -1;
	_nbpas_faits = 0;
    _arretnbpas = false;
}


void OliStepper::rewindFully (){
	if (_pos_rel < 0) {_sens="CW";}
    if (_pos_rel == 0) {_sens="STOP";}
    if (_pos_rel > 0) {_sens="CCW";}
    _nbpas_afaire = abs(_pos_rel) -1;
	_nbpas_faits = 0;
    _arretnbpas = false;
}


void OliStepper::setOrigin(){
	_pos_rel = 0;
}


void OliStepper::oliRun (){

  if (!_arretnbpas) {
    if (_sens == "CW") {
      tourne1pasCW ();
      _pos_rel++;
    }
    else if (_sens == "CCW") {
      tourne1pasCCW();
      _pos_rel--;
    }
    else if (_sens == "STOP") {
      tourneSTOP();
    }
  }
  if (_arretnbpas) {
    tourneSTOP();
  }

  // nombre de pas defini --------------------------
  if (_nbpas_afaire != 0 && _nbpas_faits < _nbpas_afaire){
    _nbpas_faits ++;
  }
  if (_nbpas_faits >= _nbpas_afaire && _nbpas_afaire != 0){
    _arretnbpas = true;
  }

}


void OliStepper::tourne1pasCCW() {
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);

}


void OliStepper::tourne1pasCW() {
  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);

  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, HIGH);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, HIGH);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, LOW);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, HIGH);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);
  
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, HIGH);
  delay (_delaivitesse);
  
}

//---------------------------------------------------------
void OliStepper::tourneSTOP() {
  digitalWrite (_mot_pin1, LOW);
  digitalWrite (_mot_pin2, LOW);
  digitalWrite (_mot_pin3, LOW);
  digitalWrite (_mot_pin4, LOW);

}