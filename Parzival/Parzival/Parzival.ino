/*
 Name:		Parzival.ino
 Created:	2/23/2016 2:19:12 PM
 Author:	sferguson
*/

#include "AFMotor.h"
#include <SoftwareSerial.h>
SoftwareSerial softSerial(15, 14); // RX, TX

#define velocity (700) /* how fast the wheels spin */

AF_DCMotor m_driver(1, MOTOR12_64KHZ); // driver-side motor
AF_DCMotor m_passenger(2, MOTOR12_64KHZ); // passenger-side motor

// the setup function runs once when you press reset or power the board
void setup() {
	softSerial.begin(9600);
	Serial.begin(9600);
	Serial.println("Serial online!");

	m_driver.setSpeed(velocity);
	m_passenger.setSpeed(velocity);


}

// the loop function runs over and over again until power down or reset
void loop() {
	while (softSerial.available()) {
		Serial.println("While Loop!");
		int motor1 = softSerial.parseInt();
		int motor2 = softSerial.parseInt();
		if (softSerial.read() == '\n') {
			if (motor1 < 90) {
				m_driver.run(FORWARD);
				Serial.print("Motor 1 Forward ");
			}
			else if (motor1 > 90) {
				m_driver.run(BACKWARD);
				Serial.print("Motor 1 Backward ");
			}
			else {
				m_driver.run(RELEASE);
				Serial.print("Motor 1 No Movement ");
			}
			if (motor2 < 90) {
				m_passenger.run(FORWARD);
				Serial.println("Motor 2 Forward");
			}
			else if (motor2 > 90) {
				m_passenger.run(BACKWARD);
				Serial.println("Motor 2 Backward");
			}
			else {
				m_passenger.run(RELEASE);
				Serial.println("Motor 2 No Movement");
			}

		}
		else {
			Serial.println("No Input Detected...");
		}

	}
	delay(50);
}

void blinkReadyLight() {
	for (int i = 0; i < 3; i++) {
		digitalWrite(13, HIGH);
		delay(200);
		digitalWrite(13, LOW);
		delay(200);
	}
}

