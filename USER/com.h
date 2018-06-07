#ifndef __COM_H
#define	__COM_H

#include "motor.h"
#include "servo.h"
#include "Sevseg.h"
#include "button.h"
#include "DHT11.h"
#include "Pirmotion.h"
#include "UltrasonicWave.h"
#include "WS2812B.h"
#include "exti.h"
#include "adc.h"
#include "Bport_out.h"

#define VERSION 0
#define ULTRASONIC_SENSOR 1
#define TEMPERATURE_SENSOR 2
#define LIGHT_SENSOR 3
#define POTENTIONMETER 4
#define JOYSTICK 5
#define GYRO 6
#define SOUND_SENSOR 7
#define RGBLED 8
#define SEVSEG 9
#define MOTOR 10
#define SERVO 11
#define ENCODER 12
#define IR 13
#define IRREMOTE 14
#define PIRMOTION 15
#define INFRARED 16
#define LINEFOLLOWER 17
#define IRREMOTECODE 18
#define SHUTTER 20
#define LIMITSWITCH 21
#define BUTTON 22
#define HUMITURE 23
#define FLAMESENSOR 24
#define GASSENSOR 25
#define COMPASS 26
#define DIGITAL 30
#define ANALOG 31
#define PWM 32
#define SERVO_PIN 33
#define TONE 34
#define BUTTON_INNER 35
#define PULSEIN 37
#define ULTRASONIC_ARDUINO 36
#define STEPPER 40
#define LEDMATRIX 41
#define TIMER 50
#define TOUCH_SENSOR 51
#define BUZZER 52

#define GET 1
#define RUN 2
#define RESET 4
#define START 5

extern unsigned char Readbuffer[20];
extern int Perform;

void parseData();
void callOK();
void sendByte(char c);
void sendFloat(float value);
int readmotor(int speed);
void runModule(int device);
void readSensor(int device);


#endif
