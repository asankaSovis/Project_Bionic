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

int servoValues [] = {
  0, 0, 0, 0, // Servo 1, Servo  2, Servo  3, Servo  4 ------ Body
  0, 0, 0, 0, // Servo 5, Servo  6, Servo  7, Servo  8 ------ Segment
  0, 0, 0, 0  // Servo 9, Servo 10, Servo 11, Servo 12 ------ Claw
};

// Determines the required pulse width for a given angle value
// accept int required angle in degrees
// return int pulse width
int pulseWidth(int angle) {
  int pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  
  return analog_value;
}

void debugMsg(String message) {
  Serial.println(message);
}

bool setAngle(int servoID, int angle) {
  if ((servoID >= 0) && (servoID <= 11)) {
    if ((angle >= limits[servoID][0]) && (angle <= limits[servoID][1])) {
      pwm.setPWM(servoID, 0, pulseWidth(angle));
      servoValues[servoID] = angle;
      debugMsg("Servo " + String(servoID) + ": " + String(angle));
      return true;
    }
  }

  debugMsg("Invalid ServoID or Angle -> Servo ID: " + String(servoID) + " | Angle: " + String(angle));
  return false;
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void resetServos() {
  setAngle(4, 0);
  setAngle(5, 90);
  setAngle(6, 0);
  setAngle(7, 90);

  delay(100);

  setAngle(8, 20);
  setAngle(9, 60);
  setAngle(10, 10);
  setAngle(11, 80);

  delay(100);

  setAngle(0, 10);
  setAngle(1, 70);
  setAngle(2, 20);
  setAngle(3, 65);
}

void stopRobot() {
  int expectedValues [] = { 0, 90, 0, 90 };

  while ((servoValues[4] != expectedValues[0]) ||(servoValues[5] != expectedValues[1]) || (servoValues[6] != expectedValues[2]) || (servoValues[7] != expectedValues[3]))
  {
    for (int i = 4; i < 8; i++) {
      if (servoValues[i] > expectedValues[i - 4]) {
        setAngle(i, servoValues[i] - 1);
      } else if (servoValues[i] < expectedValues[i - 4]) {
        setAngle(i, servoValues[i] + 1);
      }

      delay(10);
    }
  }

  delay(100);

  setAngle(8, 20);
  setAngle(9, 60);
  setAngle(10, 10);
  setAngle(11, 80);

  delay(100);

  setAngle(0, 10);
  setAngle(1, 70);
  setAngle(2, 20);
  setAngle(3, 65);
}

void startRobot() {
  setAngle(0, 90);
  setAngle(1, 0);
  setAngle(2, 90);
  setAngle(3, 0);

  delay(100);

  setAngle(8, 60);
  setAngle(9, 30);
  setAngle(10, 50);
  setAngle(11, 30);

  delay(1000);

  setAngle(4, 50);
  setAngle(5, 40);
  setAngle(6, 50);
  setAngle(7, 40);
}

void serialEvent() {
  while (Serial.available()) {
    String rawStr = Serial.readString();  //read until timeout
    rawStr.trim();

    if (rawStr == "start") {
      startRobot();
      debugMsg("-- Robot Started --------------------------------");
    } else if (rawStr == "stop") {
      stopRobot();
      debugMsg("-- Robot Stopped --------------------------------");
    } else {
      int servoID = getValue(rawStr, ' ', 0).toInt();
      int angle = getValue(rawStr, ' ', 1).toInt();

      setAngle(servoID, angle);
    }


  }
}

// Run once on setup
void setup() {
  Serial.begin(9600);

  debugMsg("\n-- Setup --------------------------------");
  debugMsg("Servo Frequency: " + String(FREQUENCY));
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  resetServos();
  debugMsg("-- End of Setup ------------------------");
}

// Loop
void loop() {
  
}



