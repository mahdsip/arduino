#include <NewPing.h>
 
#define TRIG_PIN A2 // Pin A4 on the Motor Drive Shield connected to the ultrasonic sensor
#define ECHO_PIN A3 // Pin A5 on the Motor Drive Shield connected to the ultrasonic sensor
#define MAX_DISTANCE_POSSIBLE 1000 // sets maximum useable sensor measuring distance to 1000cm
#define MAX_SPEED 120 // sets speed of DC traction motors to 120/256 or about 47% of full speed - to reduce power draining.
#define COLL_DIST 20 // sets distance at which robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which robot looks away from object (not reverse) to 20cm (10+10)
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE); // sets up sensor library to use the correct pins to measure distance.

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;
  Serial.print("Distance");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

