#include "Servo.h"

Servo myServo;

const char RIGHT_PLUS = 9;
const char RIGHT_MINUS = 10;
const char LEFT_PLUS = 11;
const char LEFT_MINUS = 12;

const char PWM_SERVO = 2;

const char DOUT_TRIGGER = 3;
const char DIN_ECHO = 4;

const char PIN_IR_UP_RIGHT = 6;
const char PIN_IR_UP_LEFT = 5;
const char PIN_IR_DOWN_RIGHT = 7;
const char PIN_IR_DOWN_LEFT = 8;

int servoPosition = 90;

void setup() {
	Serial.begin(9600);
	pinMode(RIGHT_PLUS, OUTPUT);
	pinMode(RIGHT_MINUS, OUTPUT);
	pinMode(LEFT_PLUS, OUTPUT);
	pinMode(LEFT_MINUS, OUTPUT);

	pinMode(DOUT_TRIGGER, OUTPUT);
	pinMode(DIN_ECHO, INPUT);

	pinMode(PIN_IR_UP_RIGHT, INPUT);

	myServo.attach(PWM_SERVO);
	myServo.write(servoPosition);
}

void loop() {
	moveForward();
	look(90);
	look(180);
	look(135);
	look(45);
	look(0);
}

void checkCorners() {
	if (digitalRead(PIN_IR_UP_RIGHT) == 0)
	{
		turnLeft();
		delay(500);
	}
	else if (digitalRead(PIN_IR_UP_LEFT) == 0)
	{
		turnRight();
		delay(500);
	}
}

void look(int a)
{
	myServo.write(a);
	checkObstacles();
}

void stopMoving()
{
	digitalWrite(RIGHT_PLUS, LOW);
	digitalWrite(RIGHT_MINUS, LOW);
	digitalWrite(LEFT_PLUS, LOW);
	digitalWrite(LEFT_MINUS, LOW);
}

void moveForward()
{
	digitalWrite(RIGHT_PLUS, HIGH);
	digitalWrite(RIGHT_MINUS, LOW);
	digitalWrite(LEFT_PLUS, HIGH);
	digitalWrite(LEFT_MINUS, LOW);
}

void moveBack()
{
	digitalWrite(RIGHT_PLUS, LOW);
	digitalWrite(RIGHT_MINUS, HIGH);
	digitalWrite(LEFT_PLUS, LOW);
	digitalWrite(LEFT_MINUS, HIGH);
}

void turnRight() {
	digitalWrite(RIGHT_PLUS, LOW);
	digitalWrite(RIGHT_MINUS, HIGH);
	digitalWrite(LEFT_PLUS, HIGH);
	digitalWrite(LEFT_MINUS, LOW);

}

void turnLeft() {
	digitalWrite(RIGHT_PLUS, HIGH);
	digitalWrite(RIGHT_MINUS, LOW);
	digitalWrite(LEFT_PLUS, LOW);
	digitalWrite(LEFT_MINUS, HIGH);

}

int checkObstacles()
{
	digitalWrite(DOUT_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(DOUT_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(DOUT_TRIGGER, LOW);
	delayMicroseconds(10);
	long distance = pulseIn(DIN_ECHO, HIGH, 2500) / 58.0;

	delay(200);

	//Checks if there is no obstacles in 18 cm
	if (distance >= 2 && distance <= 18)
	{
		moveBack();
		delay(1000);
		turnRight();
		delay(500);
	}
	//Checks if there is no corners right and left sides of the car
	checkCorners();
}