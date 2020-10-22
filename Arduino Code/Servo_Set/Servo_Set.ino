#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  500 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  2500 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servo[5] = {0, 1, 2, 3, 4}


void setup() {

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {
  

  pwm.setPWM(0, 0, pulseWidth(90));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(90));
  pwm.setPWM(3, 0, pulseWidth(90));
  pwm.setPWM(4, 0, pulseWidth(90));

  delay(100);
  
  
}

int pulseWidth(int angle){
  int pulseWide, analogValue;
  pulseWide = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  analogValue = int(float(pulseWide) / 1000000 * SERVO_FREQ * 4096);
  return analogValue;
}
