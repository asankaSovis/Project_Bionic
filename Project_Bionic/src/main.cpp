/*
---- PROJECT BIONIC v1.0 -------------------------------------------
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
#define FREQUENCY 100

int movementCount = 0;

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
      //debugMsg("Servo " + String(servoID) + ": " + String(angle));
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

void incrementServo(int count, int expectedServos [][2], int speed, int increment = 1) {
  bool complete = false;

  while (!(complete))
  {
    complete = true;
    for (int i = 0; i < count; i++) {
      if (servoValues[expectedServos[i][0]] > expectedServos[i][1]) {
        setAngle(expectedServos[i][0], servoValues[expectedServos[i][0]] - increment);
      } else if (servoValues[expectedServos[i][0]] < expectedServos[i][1]) {
        setAngle(expectedServos[i][0], servoValues[expectedServos[i][0]] + increment);
      }

      complete = complete && (servoValues[expectedServos[i][0]] == expectedServos[i][1]);
      delay(speed);
    }
  }
}

void resetServos() {
  debugMsg("-- Reset Servos --------------------------------");

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
  debugMsg("-- Robot Stop --------------------------------");

  int count = 4;
  int expectedServos [][2] = { {4, 0}, {5, 90}, {6, 0}, {7, 90} };
  incrementServo(count, expectedServos, 10);

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
  debugMsg("-- Robot Start --------------------------------");

  setAngle(0, 60);
  setAngle(1, 20);
  setAngle(2, 80);
  setAngle(3, 20);

  delay(100);

  setAngle(8, 60);
  setAngle(9, 30);
  setAngle(10, 50);
  setAngle(11, 30);

  delay(1000);

  setAngle(4, 60);
  setAngle(5, 30);
  setAngle(6, 60);
  setAngle(7, 30);
}

void forwardRobot() {
  debugMsg("-- Robot Forward --------------------------------");

  setAngle(4, 30);
  delay(100);
  setAngle(0, 20);
  delay(100);
  setAngle(4, 60);
  delay(200);

  setAngle(5, 60);
  delay(100);
  setAngle(1, 20);
  delay(100);
  setAngle(5, 30);
  delay(200);

  int expectedServos1 [][2] = { {0, 80}, {1, 70} };
  incrementServo(2, expectedServos1, 0, 10);
  delay(200);

  setAngle(7, 60);
  delay(100);
  setAngle(3, 55);
  delay(100);
  setAngle(7, 30);
  delay(200);

  setAngle(6, 30);
  delay(100);
  setAngle(2, 80);
  delay(100);
  setAngle(6, 60);
  delay(200);

  int expectedServos2 [][2] = { {2, 30}, {3, 15} };
  incrementServo(2, expectedServos2, 0, 10);
  delay(200);
}

void backwardRobot() {
  debugMsg("-- Robot Backward --------------------------------");

  setAngle(5, 60);
  delay(100);
  setAngle(1, 70);
  delay(100);
  setAngle(5, 30);
  delay(200);

  setAngle(4, 30);
  delay(100);
  setAngle(0, 80);
  delay(100);
  setAngle(4, 60);
  delay(200);

  int expectedServos1 [][2] = { {0, 20}, {1, 20} };
  incrementServo(2, expectedServos1, 0, 10);
  delay(200);

  setAngle(6, 30);
  delay(100);
  setAngle(2, 30);
  delay(100);
  setAngle(6, 60);
  delay(200);

  setAngle(7, 60);
  delay(100);
  setAngle(3, 15);
  delay(100);
  setAngle(7, 30);
  delay(200);

  int expectedServos2 [][2] = { {2, 80}, {3, 55} };
  incrementServo(2, expectedServos2, 0, 10);
  delay(200);
}

void rightRobot() {
  debugMsg("-- Robot Turn Right --------------------------------");

  setAngle(4, 30);
  delay(100);
  setAngle(0, 40);
  delay(100);
  setAngle(4, 60);
  delay(200);

  setAngle(5, 60);
  delay(100);
  setAngle(1, 30);
  delay(100);
  setAngle(5, 30);
  delay(200);

  setAngle(6, 30);
  delay(100);
  setAngle(2, 50);
  delay(100);
  setAngle(6, 60);
  delay(200);

  setAngle(7, 60);
  delay(100);
  setAngle(3, 25);
  delay(100);
  setAngle(7, 30);
  delay(200);

  int expectedServos [][2] = { {0, 60}, {1, 40}, {2, 60}, {3, 50} };
  incrementServo(4, expectedServos, 0, 1);
  delay(200);
}

void leftRobot() {
  debugMsg("-- Robot Turn Left --------------------------------");

  setAngle(4, 30);
  delay(100);
  setAngle(0, 60);
  delay(100);
  setAngle(4, 60);
  delay(200);

  setAngle(5, 60);
  delay(100);
  setAngle(1, 40);
  delay(100);
  setAngle(5, 30);
  delay(200);

  setAngle(6, 30);
  delay(100);
  setAngle(2, 60);
  delay(100);
  setAngle(6, 60);
  delay(200);

  setAngle(7, 60);
  delay(100);
  setAngle(3, 40);
  delay(100);
  setAngle(7, 30);
  delay(200);

  int expectedServos [][2] = { {0, 40}, {1, 30}, {2, 50}, {3, 25} };
  incrementServo(4, expectedServos, 0, 1);
  delay(200);
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
    } else if (rawStr == "backward") {
      backwardRobot();
      debugMsg("-- Robot Backward --------------------------------");
    } else {
      int servoID = getValue(rawStr, ' ', 0).toInt();
      int angle = getValue(rawStr, ' ', 1).toInt();

      setAngle(servoID, angle);
    }


  }
}

// Run once on setup
void setup() {
  pinMode(D0, OUTPUT);

  Serial.begin(9600);

  debugMsg("\n-- Setup --------------------------------");
  debugMsg("Servo Frequency: " + String(FREQUENCY));
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  resetServos();
  debugMsg("-- End of Setup --------------------------");
}

// Loop
void loop() {
  if (movementCount == 0) {
    digitalWrite(D0, HIGH);
    delay(1000);
    digitalWrite(D0, LOW);
    startRobot();
    movementCount++;
  } else if (movementCount < 10) {
    delay(300);
    digitalWrite(D0, HIGH);
    forwardRobot();
    movementCount++;
    digitalWrite(D0, LOW);
  } else if (movementCount < 20) {
    delay(300);
    digitalWrite(D0, HIGH);
    leftRobot();
    movementCount++;
    digitalWrite(D0, LOW);
  } else if (movementCount < 30) {
    delay(300);
    digitalWrite(D0, HIGH);
    forwardRobot();
    movementCount++;
    digitalWrite(D0, LOW);
  } else if (movementCount < 40) {
    delay(300);
    digitalWrite(D0, HIGH);
    rightRobot();
    movementCount++;
    digitalWrite(D0, LOW);
  } else if (movementCount < 50) {
    delay(300);
    digitalWrite(D0, HIGH);
    backwardRobot();
    movementCount++;
    digitalWrite(D0, LOW);
  }

}



