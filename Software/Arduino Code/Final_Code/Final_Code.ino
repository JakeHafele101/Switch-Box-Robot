#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[5] = {0, 1, 2, 3, 4};
const int buttons[8] = {2, 3, 4, 5, 6, 7, 8, 9};

const int baseToButton[] = {90, 90, 90, 90, 90, 90, 90, 90}; //FIXME
const int armToButton[] = {95, 95, 95, 95, 95, 95, 95, 95}; //FIXME

int buttonVal[8];
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

  if(buttonPressed){
    delay(1000);
    armOutExtension();
    int buttonPressedIn = buttonRead();
    if(buttonPressedIn){
      buttonPressed = buttonPressedIn;
    }
    buttonHandler(buttonPressed);
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
}

void armRetractIdle(){
  pwm.setPWM(1, 0, pulseWidth(120)); //Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(70)); //upper arm servo/90
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
  for(int i = 0; i < 8; i++){
    buttonVal[i] = digitalRead(buttons[i]);
    Serial.print(buttonVal[i]);
    Serial.print(" ");
  }
  Serial.println();

  if(buttonVal[0]){
    return 1;
  }
  else if(buttonVal[1]){
    return 2;
  }
  else if(!buttonVal[2]){
    return 3;
  }
  else if(!buttonVal[3]){
    return 4;
  }
  else if(buttonVal[4]){
    return 5;
  }
  else if(buttonVal[5]){
    return 6;
  }
  else if(!buttonVal[6]){
    return 7;
  }
  else if(!buttonVal[7]){
    return 8;
  }
  else {
    return 0;
  }
}

void buttonHandler(int buttonPressed){
  switch(buttonPressed){
    case 1:
      buttonOne();
      break;

    case 2:
      buttonTwo();
      break;

    case 3:
      buttonThree();
      break;

    case 4:
      buttonFour();
      break;

    case 5:
      buttonFive();
      break;

    case 6:
      buttonSix();
      break;

    case 7:
      buttonSeven();
      break;

    case 8:
      buttonEight();
      break;
  }
}

//Buttons one to eight read left to right on PCB
void buttonOne(){//Pushbutton
  pwm.setPWM(0, 0, pulseWidth(78));
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(75)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(102));//Lower arm servo/90
  delay(500);
  
}

void buttonTwo(){ //Tactile Switch
  pwm.setPWM(0, 0, pulseWidth(85));
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(80)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(101));//Lower arm servo/90
  delay(500);
}

void buttonThree(){ //Slide Switch
  pwm.setPWM(0, 0, pulseWidth(94));
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(100));//Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(75)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(85)); //Upper arm servo //85
  delay(500);
}

void buttonFour(){ //Toggle Switch
  pwm.setPWM(0, 0, pulseWidth(101));
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(83)); //Upper arm servo //85
  pwm.setPWM(1, 0, pulseWidth(98));//Lower arm servo/90
  delay(500);
}

void buttonFive(){
  pwm.setPWM(0, 0, pulseWidth(110));
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(110)); //lower arm servo //85
  delay(500);

pwm.setPWM(2, 0, pulseWidth(65)); //Upper arm servo //85
  delay(500);

}

void buttonSix(){
  pwm.setPWM(0, 0, pulseWidth(115));
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(80)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(102));//Lower arm servo/90
  delay(500);
}

void buttonSeven(){
  pwm.setPWM(0, 0, pulseWidth(125));
  delay(500);
  pwm.setPWM(1, 0, pulseWidth(100));//Lower arm servo/90
  pwm.setPWM(2, 0, pulseWidth(75)); //Upper arm servo //85
  delay(500);
  pwm.setPWM(2, 0, pulseWidth(85)); //Upper arm servo //85
  delay(500);
}

void buttonEight(){
  
}
