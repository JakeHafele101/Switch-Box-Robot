#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[5] = {0, 1, 2, 3, 4};
const int buttons[8] = {2, 3, 4, 5, 6, 7, 8, 9};

const int baseToButton = {90, 90, 90, 90, 90, 90, 90, 90}; //FIXME
const int armToButton = {95, 95, 95, 95, 95, 95, 95, 95}; //FIXME

int buttonPressed;

void setup() {

  pwm.begin();
  Serial.begin(9600);
 
  for(int i = 0; i < sizeof(buttons); i++){
    pinMode(buttons[i], INPUT);
  }

  buttonPressed = 0; //No buttons pressed at start

  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  idle(); //Sets robot arm to idle position

}

void loop() {

  buttonPressed = buttonRead();

  if(buttonPressed > 0){
    armOutExtension();
    armToButton(buttonPressed);
    armRetractIdle();
    buttonPressed = 0; //resets button so doesnt trigger right away accidentally
  }
  
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
}

void armToButton(int button){
   pwm.setPWM(0, 0, pulseWidth(baseToButton[button - 1]));//turns base to face selected button
   delay(500);
   pwm.setPWM(2, 0, pulseWidth(armToButton[button - 1]));//turns upper arm to press button
   delay(500);
}

void armRetractIdle(){
  pwm.setPWM(2, 0, pulseWidth(95)); //upper arm servo/90
  pwm.setPWM(1, 0, pulseWidth(90)); //Lower arm servo/90
  delay(1000);
  pwm.setPWM(0, 0, pulseWidth(90));
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(120));//Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(70)); //Upper arm servo //85
  delay(500);
  closeWindow();
  idle();
}

int buttonRead(){ //Returns number of button pressed if any pressed, otherwise returns 0
  for(int i = 0; i < sizeof(buttons); i++){
    Serial.print(buttons[1] + " ");
    if(buttons[i]){
      Serial.println();
      return i + 1;
    }
  }
  Serial.println();
  return 0;
}
