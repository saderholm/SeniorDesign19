// ********************************************
// Test for analog multiplexer with TCS230 and HC-SR04.
// Unfortunately the MUX is not the ideal IO expander because it can do either input or output
// at the same time, but not both.
// ********************************************

const int selectPins[4] = {2,3,4,5}; // digital pins on the arduino
const int channel[5] = {11,12,13,14,15}; // channel that outputs are connected to
// Channel connections for TCS230 color sensor
// 15: S0
// 14: S1
// 13: S2
// 12: S3
// Channel connections for HC-SR04 ultrasonic sensor
// 11: Trig
const int sig = 6; // SIG pin on the MUX
const int echopin = 8; // Echo pin for HC-SR04
const int out = 7; // Output from TCS230

long duration, cm, inches;
int frequency = 0; 
void setup() {
  
  for (int i=0; i<4; i++)
    {
      pinMode(selectPins[i], OUTPUT);
      digitalWrite(selectPins[i], LOW);
    }
    pinMode(sig, OUTPUT); // Set up pin 6 as the output
    pinMode(echopin,INPUT); // Set up digital pin 8 as echo input from HC-SR04
    pinMode(out,INPUT); // Set up digital pin 7 as output from TCS230
    Serial.begin(9600); // Set up serial monitor

    // Set frequency selection on TCS230 to 20%
    selectMuxPin(channel[4]); // Select C15 (S0)
    digitalWrite(sig,HIGH);
    selectMuxPin(channel[3]); // Select C14 (S1)
    digitalWrite(sig,LOW);
}

 
void loop() {
    // Read from ultrasonic sensor
    ultSens();
    // Read from color sensor
    colorSens();
}

void selectMuxPin(byte pin)
{
  if (pin > 15) return; // Exit if pin is out of scope
  for (int i=0; i<4; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

void ultSens(){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  selectMuxPin(channel[0]); // select C11 (trig)
  digitalWrite(sig, LOW);
  delayMicroseconds(10);
  digitalWrite(sig, HIGH);
  delayMicroseconds(20);
  digitalWrite(sig, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echopin, HIGH);
  Serial.println(duration);
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}

void colorSens(){
  // Setting red filtered photodiodes to be read
  selectMuxPin(channel[2]); // Set mux to S2
  digitalWrite(sig,LOW);
  selectMuxPin(channel[1]); // Set mux to S3
  digitalWrite(sig,LOW);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Green filtered photodiodes to be read
  selectMuxPin(channel[2]); // Set mux to S2
  digitalWrite(sig,HIGH);
  selectMuxPin(channel[1]); // Set mux to S3
  digitalWrite(sig,HIGH);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  selectMuxPin(channel[2]); // Set mux to S2
  digitalWrite(sig,LOW);
  selectMuxPin(channel[1]); // Set mux to S3
  digitalWrite(sig,HIGH);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}