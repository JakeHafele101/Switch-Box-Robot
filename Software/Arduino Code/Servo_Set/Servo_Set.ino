#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[5] = {0, 1, 2, 3, 4};
const int toggle[1] = {4};

void setup() {

  pwm.begin();
  Serial.begin(9600);
 
  pinMode(toggle[1], INPUT_PULLUP);

  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

idle();

}

void loop() {
  Serial.println(digitalRead(toggle[0]));
//  if(digitalRead(toggle[0]) == LOW){
//    Serial.println("VoltageLow");
//    pwm.setPWM(0, 0, pulseWidth(180));
//    // if the this is brooken before the servo has finished then return to the initial position and break the if statement.
//    delay (1000);
//    pwm.setPWM(0, 0, pulseWidth(0));
//    delay (2000);
//  }
//
//


 //delay(5000);
 
 
 armOutExtension();
 
 armRetractIdle();
 

 
  
  
}

int pulseWidth(int angle){
  int pulseWide, analogValue;
  pulseWide = map(angle, 0, 270, SERVO_MIN, SERVO_MAX);
  analogValue = int(float(pulseWide) / 1000000 * SERVO_FREQ * 4096);
  return analogValue;
}

void openWindow(){
  pwm.setPWM(3, 0, pulseWidth(180)); //right window open servo, rest 0 degrees, open 135 degrees
  pwm.setPWM(4, 0, pulseWidth(0)); //Left window open servo, rest 180 degrees, open 45 degrees
}

void closeWindow(){
  pwm.setPWM(3, 0, pulseWidth(0)); //right window open servo, rest 0 degrees, open 135 degrees
  pwm.setPWM(4, 0, pulseWidth(180)); //Left window open servo, rest 180 degrees, open 45 degrees

}
void idle() {
 pwm.setPWM(0, 0, pulseWidth(90)); //Base servo
  pwm.setPWM(1, 0, pulseWidth(170)); //Lower arm servo
  pwm.setPWM(2, 0, pulseWidth(10)); //Upper arm servo
  closeWindow();
  delay(1000);
}

void armOutExtension(){ //this will need to change for each switch
   openWindow();
   
     
  pwm.setPWM(2, 0, pulseWidth(40)); //Upper arm servo
  delay(700);
   pwm.setPWM(1, 0, pulseWidth(120));//Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(70)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(90)); //Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(95)); //upper arm servo/90
  delay(700);
  pwm.setPWM(0, 0, pulseWidth(110));//base servo CHANGE THIS PER FUNCTION
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(90));//base servo CHANGE THIS PER FUNCTION
 delay(500);
 pwm.setPWM(0, 0, pulseWidth(70));//base servo CHANGE THIS PER FUNCTION
 delay(500);
}


void armRetractIdle(){
  pwm.setPWM(0, 0, pulseWidth(90));//base servo CHANGE THIS PER FUNCTION
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(95)); //upper arm servo/90
   pwm.setPWM(1, 0, pulseWidth(90)); //Lower arm servo/90
    delay(1000);
   pwm.setPWM(1, 0, pulseWidth(120));//Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(70)); //Upper arm servo //85
  delay(500);
  closeWindow();
  idle();
}
