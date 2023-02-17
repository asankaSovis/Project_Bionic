/*
---- PROJECT BIONIC v0.0 -------------------------------------------
-- Building a bionic robot from scratch
-- Author: Asanka Sovis
-- Created: 17/02/2023
-- Last Edit: 17/02/2023
--------------------------------------------------------------------
*/

#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // Servo at 0x40 I2C register

// Defaults, do not change unless required
#define MIN_PULSE_WIDTH 600
#define MAX_PULSE_WIDTH 2600
#define FREQUENCY 50

// Defining the angular limits for each servo motor
// NOTE: DO NOT CHANGE THESE AS IT CAN DAMAGE THE ROBOT!
int limits [][2] = {
  {  0, 90 }, {  0, 90 }, {  0, 90 }, {  0, 75 }, // Servo 1, Servo  2, Servo  3, Servo  4 ------ Body
  {  0, 70 }, { 20, 90 }, {  0, 70 }, { 20, 90 }, // Servo 5, Servo  6, Servo  7, Servo  8 ------ Segment
  { 20, 90 }, {  0, 60 }, { 10, 90 }, {  0, 80 }  // Servo 9, Servo 10, Servo 11, Servo 12 ------ Claw
};

// Determines the required pulse width for a given angle value
// accept int required angle in degrees
// return int pulse width
int pulseWidth(int angle) {
  int pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  
  return analog_value;
}

// Run once on setup
void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

// Loop
void loop() {
  pwm.setPWM(0, 0, pulseWidth(60));
}



