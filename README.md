# 🤖 Project Bionic

![Poster](https://user-images.githubusercontent.com/46389631/222119721-d204f6a5-52a0-467c-8b67-b5a962d3589a.png)

---

*💸 Please consider [donating](https://www.paypal.com/donate/?hosted_button_id=4EWXTWQ9FUFLA) on Paypal to keep this project alive.*

## 🤖 Project Introduction

Project Bionics intends to build a bio inspired robot that can mimic the nature. The design, based on the 3D models shared by [KILIC on PCBWay](https://www.pcbway.com/project/shareproject/Quadruped_Spider_Robot_3D_Printed_Parts_SG90_Servo_Motor_Arduino_Nano_10107fe3.html), can mimic the movement of a spider by using servos. The complete system is controlled by a NodeMCU and is powered by Li-ion battery which makes it portable. The robot can move to the front, back and can rotate to the left and right.

## 🔌 Components Used

> ![Components Used](https://user-images.githubusercontent.com/46389631/222161423-37f1ed7b-6798-4490-9a7f-bdc3e903d791.png)
> 
> Components Used

1. NodeMCU (ESP8266) (x1) - Microconroller that is used to control the body
2. 16-Channel PWM Servo Controller Module (x1) - Accepts the commands from the NodeMCU via I2C protocol to control the 12 servos
3. Tower Pro 9g Micro Servo (x12) - Handles the movements of each link of the body
4. 3.7V Rechargeable Battery (1800mAh) (x2) - Provides the power to drive the body
5. Lm2596 DC to DC Step down (x1) - Steps down the voltage from batteries to the NodeMCU and Servo Controller module
6. 2S Battery Management System (x1) - Handles the charging and supply of power for the batteries
7. L7809 Voltage Regulator with Heat Sink (x1) - Regulate the voltage from 12V power supply to 9V for the BMS
8. 3D Printed Body Parts - The body of the robot. These are based on the design provided by KILIC on PCBWay. These can be downloaded by [Quadruped Spider Robot](https://www.pcbway.com/project/shareproject/Quadruped_Spider_Robot_3D_Printed_Parts_SG90_Servo_Motor_Arduino_Nano_10107fe3.html)

## 🏛️ Architecture

> ![Architecture](https://user-images.githubusercontent.com/46389631/222175142-3cfedaac-7875-472b-9d22-04ca8db68520.png)
>
> Architecture of the Electronics

## 📊 Demonstration

> [![Demonstration](https://user-images.githubusercontent.com/46389631/222173876-d706b2c9-0154-42a5-bc26-7640fa28f55d.png)](https://youtu.be/7pwPqdj-oXQ)
>
> Demonstration

`© 2023 Asanka Sovis`
