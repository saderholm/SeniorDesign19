#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with  default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *m0 = AFMS.getMotor(1); // connect DC motor to port 0
Adafruit_DCMotor *m1 = AFMS.getMotor(2); // connect DC motor to port 1
Adafruit_DCMotor *m2 = AFMS.getMotor(3); // connect DC motor to port 2
Adafruit_DCMotor *m3 = AFMS.getMotor(4); // connect DC motor to port 3

//  m1      m2    m1: front left (BR)
//    0-----0     m2: front right (BR)
//                m3: back left (RB)
//    0-----0     m4: back right (RB)
//  m3      m4

int s = 150;

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
  spiralling();
}

void test(){
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
    delay(500);
    forward(s);
    delay(500);
  }
}

void spiral() {
  m0->setSpeed(45);
  m1->setSpeed(255);
  m2->setSpeed(45);
  m3->setSpeed(255);
  
  m0->run(FORWARD);
  m1->run(FORWARD);
  m2->run(FORWARD);
  m3->run(FORWARD);
}


void spiralling() {
//  digitalWrite(m0,LOW);
//  digitalWrite(m1,HIGH);
//  digitalWrite(m2,LOW);
//  digitalWrite(m3,HIGH);
  int tourtime=10000; // circle tourtime. it is about intersection areas between each spiral. it should be less than circle time
  int decreasetime=10; // time for next tour, larger spiral needs more time
  int numberofspiral=8; // number of circle
  int minspeed=137; // initial speed for spiral. 
  int maxspeed=255;// max speed 
  for(int i=0;i<=numberofspiral;i++) {
    m0->setSpeed(minspeed);
    m1->setSpeed(maxspeed);
    m2->setSpeed(minspeed);
    m3->setSpeed(maxspeed);

    m0->run(FORWARD);
    m1->run(FORWARD);
    m2->run(FORWARD);
    m3->run(FORWARD);
  
    minspeed=minspeed-8;// increase the speed to increase radius
    delay(tourtime);
    tourtime=tourtime-decreasetime;// increase the time for scan optimum area
  }
  delay(150); 
}


void circle() {
  m0->setSpeed(255);
  m1->setSpeed(137);
  m2->setSpeed(255);
  m3->setSpeed(137);
  
  m0->run(FORWARD);
  m1->run(FORWARD);
  m2->run(FORWARD);
  m3->run(FORWARD);
}

void pause() {
  m0->run(RELEASE);
  m1->run(RELEASE);
  m2->run(RELEASE);
  m3->run(RELEASE);
}

void forward(int speed) {
  m0->setSpeed(speed);
  m1->setSpeed(speed);
  m2->setSpeed(speed);
  m3->setSpeed(speed);

  m0->run(FORWARD);
  m1->run(FORWARD);
  m2->run(FORWARD);
  m3->run(FORWARD);
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

void leftTurn() {
  // outside wheels
  m0->setSpeed(255);
  m2->setSpeed(255);

  // inside wheels
  m1->setSpeed(0); // example values, can be changed
  m3->setSpeed(0);
  
  m0->run(FORWARD);
  m1->run(FORWARD);
  m2->run(FORWARD);
  m3->run(FORWARD);
}
