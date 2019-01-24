#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with  default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *m0 = AFMS.getMotor(0); // connect DC motor to port 0
Adafruit_DCMotor *m1 = AFMS.getMotor(1); // connect DC motor to port 1
Adafruit_DCMotor *m2 = AFMS.getMotor(2); // connect DC motor to port 2
Adafruit_DCMotor *m3 = AFMS.getMotor(3); // connect DC motor to port 3

//  m0      m1    m0: front left
//    0-----0     m1: front right
//                m2: back left
//    0-----0     m3: back right
//  m2      m3

int s = 150;

void setup() {
  AFMS.begin(); // default frequency = 1.6 kHz
  // Turn on motors
  m0.setSpeed(200);
  m1.setSpeed(200);
  m2.setSpeed(200);
  m3.setSpeed(200);

  m0.run(RELEASE);
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  
  Serial.begin(9600);
}

void loop() {
  // Test forward, pause, and backward
  forward(s);
  delay(1000);
  pause();
  delay(500);
  backward(s);
  delay(1000);
  pause();
  // Test left turn & circling function
  for(int i = 0; i < 3; i++){
    leftTurn();
    forward(s);
    delay(500);
  }
}

void pause() {
  m0.run(RELEASE);
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
}

void forward(int speed) {
  m0.setSpeed(speed);
  m1.setSpeed(speed);
  m2.setSpeed(speed);
  m3.setSpeed(speed);

  m0.run(FORWARD);
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
}

void backward(int speed) {
  m0.setSpeed(speed);
  m1.setSpeed(speed);
  m2.setSpeed(speed);
  m3.setSpeed(speed);

  m0.run(BACKWARD);
  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
}

void leftTurn() {
  // outside wheels
  m1.setSpeed(255);
  m3.setSpeed(255);

  // inside wheels
  m0.setSpeed(128); // example values, can be changed
  m2.setSpeed(128);
  
  m0.run(FORWARD);
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
}
