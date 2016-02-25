#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial softSerial(15, 14); // RX, TX

#define velocity (700) /* how fast the wheels spin */
#define MAX_RANGE (90)

AF_DCMotor m_driver(1, MOTOR12_64KHZ); // driver-side motor
AF_DCMotor m_passenger(2, MOTOR12_64KHZ); // passenger-side motor

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Serial online!");

 // m_driver.setSpeed(velocity);
  //m_passenger.setSpeed(velocity);


}

void loop() {
  while (softSerial.available()) {
    Serial.println("While Loop!");
    int motor1 = softSerial.parseInt();
    int motor2 = softSerial.parseInt();
    int s1 = calcSpeed(motor1);
    int s2 = calcSpeed(motor2);
    m_driver.setSpeed(s1);
    Serial.println(s1);
    m_passenger.setSpeed(s2);
    Serial.println(s2);
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

int calcSpeed(int pos){
  Serial.println(pos);
  return abs(pos-90) * (255/MAX_RANGE);
  
}

void blinkReadyLight() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
}


