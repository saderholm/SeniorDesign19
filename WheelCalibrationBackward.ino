#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with  default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *m0 = AFMS.getMotor(1); // connect DC motor to port 0
Adafruit_DCMotor *m1 = AFMS.getMotor(2); // connect DC motor to port 1
Adafruit_DCMotor *m2 = AFMS.getMotor(3); // connect DC motor to port 2
Adafruit_DCMotor *m3 = AFMS.getMotor(4); // connect DC motor to port 3

//  m0      m1    m0: front left
//    0-----0     m1: front right
//                m2: back left
//    0-----0     m3: back right
//  m2      m3

int s = 255;

void setup() {
  AFMS.begin(); // default frequency = 1.6 kHz
  // Turn on motors
  m0->setSpeed(200);
  m1->setSpeed(200);
  m2->setSpeed(200);
  m3->setSpeed(200);

  m0->run(RELEASE);
  m1->run(RELEASE);
  m2->run(RELEASE);
  m3->run(RELEASE);
  
  Serial.begin(9600);
}

void loop() {
  backward(s);
  delay(5000);
  exit(0)
}

void backward(int speed) {
  m0->setSpeed(speed);
  m1->setSpeed(speed);
  m2->setSpeed(speed);
  m3->setSpeed(speed);

  m0->run(BACKWARD);
  m1->run(BACKWARD);
  m2->run(BACKWARD);
  m3->run(BACKWARD);
}
