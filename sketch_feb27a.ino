#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
SoftwareSerial softSerial(15, 14); // RX, TX

#define velocity (700) /* how fast the wheels spin */
#define MAX_RANGE (90)



AF_DCMotor m_driver(1, MOTOR12_64KHZ); // driver-side motor
AF_DCMotor m_passenger(2, MOTOR12_64KHZ); // passenger-side motor
Servo theServo;


int servoSpeed = 90;

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Serial online!");

 // m_driver.setSpeed(velocity);
  //m_passenger.setSpeed(velocity);
theServo.attach(9);
theServo.write(servoSpeed);
}

void loop() {
  
  while (softSerial.available()) {
    Serial.println("While Loop!");
    int stopBtn = softSerial.parseInt();
    int sweepLeft = softSerial.parseInt();
    int sweepRight = softSerial.parseInt();
    int turbobtn = softSerial.parseInt();
    int motor1 = softSerial.parseInt();
    int motor2 = softSerial.parseInt();
    int s1 = calcSpeed(motor1, turbobtn);
    int s2 = calcSpeed(motor2, turbobtn);
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
      processServoInput(sweepLeft,sweepRight,stopBtn);
    }
    else {
      Serial.println("No Input Detected...");
    }

  }
  delay(10);
}

int processServoInput(int sl,int sr, int stopBtn){
    if(stopBtn==1){
      servoSpeed = 90;
    }else if(sl == 1){
      servoSpeed = 0;
    }else if(sr == 1){
      servoSpeed = 180;
    }
    theServo.write(servoSpeed);
  
}

int calcSpeed(int pos, int turbobtn){
  Serial.println(pos);
  int speed = abs(pos-90) * (255/MAX_RANGE);
  if (turbobtn != 1) {
    speed = speed * .75;
  }
  return speed;
}

void blinkReadyLight() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
}




