#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 640
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
#define NUMBER_SERVO 8

int controledservo = 0;

int ClosePulse[NUMBER_SERVO];
int OpenPulse[NUMBER_SERVO]; 

int pulseWidth(int angle){
  int pulse_width, analog_value;
  pulse_width = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = analog_pulse(pulse_width);
  return analog_value;
}

int analog_pulse(int pulse){
  return int(float(pulse) / 1000000 * FREQUENCY * 4096);
}

void openServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(0)); 
}

void closeServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(180)); 
}

void UpdateServoState()
{
   String newBuffer=Serial.readString();
   if(newBuffer !="")
   {
    int newpulse = newBuffer.toInt();
    if( newpulse < 16)
    {
      controledservo = newBuffer.toInt();
      Serial.print("servo controled : ");
      Serial.println(newpulse);
    }
    else
    {
      int analog_value = analog_pulse(newpulse);
      pwm.setPWM(controledservo, 0, analog_value);
      Serial.print("servo angle ");
      Serial.println(newpulse);
    }
  }
}

void setup() {
  ClosePulse[0]=2400;
  ClosePulse[1]=2150;
  ClosePulse[2]=2000;
  ClosePulse[3]=2350;
  ClosePulse[4]=2350;
  ClosePulse[5]=1900;
  ClosePulse[6]=2350;
  ClosePulse[7]=2500;
  OpenPulse[0]=640;
  OpenPulse[1]=640;
  OpenPulse[2]=640;
  OpenPulse[3]=640;
  OpenPulse[4]=640;
  OpenPulse[5]=640;
  OpenPulse[6]=640;
  OpenPulse[7]=640;
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  int i;
  for(i = 0 ; i< NUMBER_SERVO ; i ++){
    pwm.setPWM(i, 0, analog_pulse(OpenPulse[i]));
    delay(300);
    pwm.setPWM(i, 0, analog_pulse(ClosePulse[i]));
  }
}

void loop() {
  UpdateServoState();
}
