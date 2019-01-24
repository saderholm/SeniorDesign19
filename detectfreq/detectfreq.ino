// Example code from randomnerdturtorials.com, modified to fit our team's setup.
// This code sets up the TCS230 and reads the frequency of its output.

int OutPut= 8;//naming pin8 of uno as output
unsigned int frequency = 0;

void setup() { 
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);//PINS 2, 3,4,5 as OUTPUT
   pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(8, INPUT);//PIN 8 as input (output on sensor)
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);//setting frequency selection to 20%
    Serial.begin(9600); // 9600 bit per second baud rate
}

void loop() {
                Serial.print("R=");//printing name
                digitalWrite(4,LOW);
                digitalWrite(5,LOW);//setting for RED color sensor
                frequency = pulseIn(OutPut, LOW);//reading frequency
                Serial.print(frequency);//printing RED color frequency
                Serial.print("  ");
                delay(500);


               Serial.print("B=");// printing name
                digitalWrite(4,LOW);
                digitalWrite(5,HIGH);// setting for BLUE color sensor
                frequency = pulseIn(OutPut, LOW);// reading frequency
                Serial.print(frequency);// printing BLUE color frequency
                Serial.print("  ");
                delay(500);

               Serial.print("G=");// printing name
                digitalWrite(4,HIGH);
                digitalWrite(5,HIGH);// setting for GREEN color sensor
                frequency = pulseIn(OutPut, LOW);// reading frequency
                Serial.print(frequency);// printing GREEN color frequency
                Serial.print("    ");

                delay(500);        

}              