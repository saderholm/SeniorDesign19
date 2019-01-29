// Senior Design ~ IEEE Robot ~ Color Detection 
// Date: January 29, 2019
// This program identifies color of object from TCS3200 sensor input
// Optimal range: 
/ /Code modified from: https://www.instructables.com/id/Arduino-Color-Detection/

// Define TCS3200 pin wired to Arduino
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 8 // Sensor output

// Initialize variables
int red = 0;
int grn = 0;
int blu = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW); 

  // Setting frequency scaling to 100%                 // TRY THIS
  //digitalWrite(S0,HIGH);
  //digitalWrite(S1,HIGH); 
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(sensorOut, LOW); // Reading RED component of color
  
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    grn = pulseIn(sensorOut, LOW); // Reading GREEN component of color
    
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    blu = pulseIn(sensorOut, LOW); // Reading BLUE component of color

// RGB frequency range for white
  if (red > 11  && red < 14   &&  grn >  12 && grn < 15    &&  blu > 10  && blu < 13)   Serial.println("WHITE");

  //else if (red > 80 && red < 125  &&  grn > 90 && grn < 125   &&  blu > 80 && blu < 125)  Serial.println("BLACK");

  // RGB frequency range for red
  else if (red > 25 && red < 95   &&  grn > 106 && grn < 165    &&  blu > 71 && blu < 150)   Serial.println("RED");

  // RGB frequency range for green
  else if (red > 43 && red < 80   &&  grn > 24 && grn < 124    &&  blu > 48 && blu < 128)   Serial.println("GREEN");

  // RGB frequency range for yellow
  else if (red > 16 && red < 75   &&  grn > 23 && grn < 127    &&  blu > 42 && blu < 129)   Serial.println("YELLOW");

  // RGB frequency range for BLUE
  else if (red > 62 && red < 89  &&  grn > 28 && grn < 140   &&  blu > 21 && blu < 134)   Serial.println("BLUE");

  //else  Serial.println("NO_COLOR");

}
