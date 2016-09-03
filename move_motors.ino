#include <AFMotor.h>
AF_DCMotor Motor1(1);
AF_DCMotor Motor3(3);

int sensorPin1 = A0;    // select the input pin for the LDR1
int sensorPin2 = A1;    // select the input pin for the LDR2
int ledPin = 13;      // select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the sensor1
int sensorValue2 = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  Motor1.run(RELEASE); 
  Motor3.run(RELEASE);  
  Motor1.setSpeed(255);  
  Motor3.setSpeed(255); 
}

void loop() {
  // read the value from the sensor1:
  sensorValue1 = analogRead(sensorPin1);
   // read the value from the sensor2:
  sensorValue2 = analogRead(sensorPin2); 
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue1);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue1);
  Serial.print("Left Sensor = ");
  Serial.print(sensorValue1);   
  Serial.print("\t"); // Prints a tab (space).
  Serial.print("Right Sensor = "); // Prints the text inside the quotes.
  Serial.print(sensorValue2); // Prints the value of the Right Sensor.
  Serial.print("\n"); // Prints a new line after all the necessary data is displayed.
  if (sensorValue1>100&sensorValue2>100)
    {
       Motor1.run(FORWARD); 
       Motor3.run(FORWARD); 
       delay (2000);
       Motor1.run(BACKWARD);
       Motor3.run(BACKWARD);
       delay (2000);
    }
}
