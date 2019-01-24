// This code attempts to connect the TCS230 color sensor to the SX1509 GPIO expander using the
// I2C and SX1509 libraries. Only includes reading frequency values, not detecting color.
// Not working as of 12/15/18. The HC-SR04 still needs to be added, & I think that the NewPing library 
// or similar library would be helpful for that.

#include <Wire.h> // I2C library
#include <SparkFunSX1509.h> 

SX1509 io; // Create an SX1509 object

// SX1509 I/O pin definitions:
const int S0 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;
const int OUT = 12;
const int INT_PIN = 2; // connected to INT on SX1509

volatile int frequency; // store frequency values from sensor

void setup() {
  pinMode(13,OUTPUT); // initialize LED pin
  
  // Call io.begin(<I2C address>) to initialize the I/O
  // expander. It'll return 1 on success, 0 on fail.
  if (!io.begin(0x3E))
  {
    // If we failed to communicate, turn the pin 13 LED on
    digitalWrite(13, HIGH);
    while (1)
      ; // And loop forever.
  }

  // Initialize pin modes
  io.pinMode(S0, OUTPUT);
  io.pinMode(S1, OUTPUT);
  io.pinMode(S2, OUTPUT);
  io.pinMode(S3, OUTPUT);
  io.pinMode(OUT, INPUT);


  // Set frequency scaling to 20%
  io.digitalWrite(S0,HIGH);
  io.digitalWrite(S1,LOW);

  // enable interrupts
  io.enableInterrupt(OUT,1); // trigger interrupt on change (rising or falling)
  pinMode(INT_PIN,INPUT_PULLUP); // configure Arduino input interrupt pin (INT is active-low)
  attachInterrupt(digitalPinToInterrupt(INT_PIN),readfreq,CHANGE); // attach interrupt to interrupt pin

  // Open serial monitor
  Serial.begin(9600);
}

void loop()
{
  //colorSens();
  noInterrupts();
  tempfreq = frequency;
  interrupts();
}
// Interrupt Service Routine (ISR)
void readfreq(){
  frequency = io.digitalRead(OUT);
}

void colorSens(){
  // Setting red filtered photodiodes to be read
  io.digitalWrite(S2,LOW);
  io.digitalWrite(S3,LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Green filtered photodiodes to be read
  io.digitalWrite(S2,HIGH);
  io.digitalWrite(S3,HIGH);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  io.digitalWrite(S2,LOW);
  io.digitalWrite(S3,HIGH);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}