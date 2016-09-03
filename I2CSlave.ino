#include <Wire.h>
#include <AFMotor.h>
#include <NewPing.h>

#define TRIG_PIN A2 // Pin A4 on the Motor Drive Shield connected to the ultrasonic sensor
#define ECHO_PIN A3 // Pin A5 on the Motor Drive Shield connected to the ultrasonic sensor
#define MAX_DISTANCE_POSSIBLE 1000 // sets maximum useable sensor measuring distance to 1000cm
#define MAX_SPEED 120 // sets speed of DC traction motors to 120/256 or about 47% of full speed - to reduce power draining.
#define COLL_DIST 20 // sets distance at which robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which robot looks away from object (not reverse) to 20cm (10+10)


AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(3);
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE); // sets up sensor library to use the correct pins to measure distance.

int sensorPin1 = A0;    // select the input pin for the LDR1
int sensorPin2 = A1;    // select the input pin for the LDR2
int ledPin = 13;      // select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the sensor1
int sensorValue2 = 0;  // variable to store the value coming from the sensor
 
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
 
double temp;
 
void setup() {
 pinMode(ledPin, OUTPUT);
 
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
 
 Serial.begin(9600); 
 leftMotor.run(RELEASE); 
 rightMotor.run(RELEASE);  
 leftMotor.setSpeed(255);  
 rightMotor.setSpeed(255); 
}
 
void loop() {
 delay(100);
 //GetTemp from arduino
 temp = GetTemp();
 //get distance from sonar
 unsigned int uS = sonar.ping();
 
 int cm = uS / US_ROUNDTRIP_CM;
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
  Serial.print("Distance");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
 //SEARCH LIGHT
  if(number==8) {
  if (sensorValue1>100&sensorValue2>100)
    {
       leftMotor.run(FORWARD); 
       rightMotor.run(FORWARD); 
       delay (2000);
       leftMotor.run(BACKWARD);
       rightMotor.run(BACKWARD);
       delay (2000);
    }
   }

}
 
// callback for received data
void receiveData(int byteCount){
 
 while(Wire.available()) {
  number = Wire.read();
 // LED SWITCHER
 if (number == 1){
   if (state == 0){
    digitalWrite(13, HIGH); // set the LED on
    state = 1;
   } else{
    digitalWrite(13, LOW); // set the LED off
    state = 0;
   }
  }
 //GET TEMPERATURE
  if(number==2) {
   number = (int)temp;
  }
 
   //MOVE FORWARD
  if(number==3) {
   //MOVE FORWARD
       leftMotor.run(FORWARD); 
       rightMotor.run(FORWARD);
       delay (2000);
       leftMotor.run(RELEASE); 
       rightMotor.run(RELEASE);   
   }
  //MOVE BACKWARD
  if(number==4) {
   //MOVE BACKWARD
       leftMotor.run(BACKWARD); 
       rightMotor.run(BACKWARD); 
       delay (2000);
       leftMotor.run(RELEASE); 
       rightMotor.run(RELEASE);         
   }
  //MOVE LEFT
  if(number==5) {
   //MOVE LEFT
     leftMotor.run(FORWARD);
      delay (2000);
      leftMotor.run(RELEASE); 
      rightMotor.run(RELEASE);  
   }  
   //MOVE RIGHT
  if(number==6) {
   //MOVE RIGHT
     rightMotor.run(FORWARD);
     delay (2000);
      leftMotor.run(RELEASE); 
      rightMotor.run(RELEASE);   
   }
   //STOP
  if(number==7) {
   //STOP
    leftMotor.run(RELEASE); 
    rightMotor.run(RELEASE);  
    delay (2000);
   }
 }
}
 
// callback for sending data
void sendData(){
 Wire.write(number);
}
 
// Get the internal temperature of the arduino
double GetTemp(void)
{
 unsigned int wADC;
 double t;
 ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
 ADCSRA |= _BV(ADEN); // enable the ADC
 delay(20); // wait for voltages to become stable.
 ADCSRA |= _BV(ADSC); // Start the ADC
 while (bit_is_set(ADCSRA,ADSC));
 wADC = ADCW;
 t = (wADC - 324.31 ) / 1.22;
 return (t);
}
