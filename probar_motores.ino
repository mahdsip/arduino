#include <AFMotor.h>
AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);
AF_DCMotor Motor3(3);
AF_DCMotor Motor4(4);


void setup()
   {        
            Motor1.run(RELEASE); 
            Motor2.run(RELEASE); 
            Motor3.run(RELEASE); 
            Motor4.run(RELEASE);            
            Motor1.setSpeed(250);  
            Motor2.setSpeed(250); 
            Motor3.setSpeed(250);  
            Motor4.setSpeed(250); 
   }

void loop()
   {   
       Motor1.run(FORWARD);
       Motor2.run(FORWARD); 
       Motor3.run(FORWARD);
       Motor4.run(FORWARD); 
       delay (800);

       Motor1.run(BACKWARD);
       Motor2.run(BACKWARD);
       Motor3.run(BACKWARD);
       Motor4.run(BACKWARD);
       delay (800);
   }
