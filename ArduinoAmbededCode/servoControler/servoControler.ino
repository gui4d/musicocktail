#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 640
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
#define NUMBER_SERVO 16


unsigned long timeStampList[NUMBER_SERVO];

int pulseWidth(int angle){
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Serial.println(analog_value);
  return analog_value;
}

void openServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(0)); 
}

void closeServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(180)); 
}

void UpdateServoState()
{
  if(Serial.available())
  {
    String newBuffer=Serial.readString();
    while(newBuffer !="")
    {
      
      long newLine = (newBuffer.substring(0,6)).toInt();
      if( newBuffer.length()>6 )
      {
        newBuffer=newBuffer.substring(7);
      }
      else{
        newBuffer="";
      }
      int newServo = newLine/10000;
      unsigned long newQuantite = newLine % 10000;
      if( newServo < NUMBER_SERVO && newServo >= 0 )
      {
        unsigned long newTime = newQuantite*100;// the new time is in ms the quantity is in decisec
        openServo( newServo );
        if( timeStampList[newServo]== 0)
        {
          timeStampList[newServo]= millis()+ newTime ;
        }
        else
        {
          timeStampList[newServo] += newTime ;
        }
        Serial.print("servo ");
        Serial.print(newServo);
        Serial.print(" open during ");
        Serial.print(newTime);
        Serial.print(" ms");
        Serial.print("->timeStamp: ");
        Serial.println(timeStampList[newServo]);     
      }
    }
  }
  int servo; 
  unsigned long actualTime= millis();
  for( servo = 0 ; servo < NUMBER_SERVO ; servo ++ ){
    if (timeStampList[servo]!= 0 && timeStampList[servo] <= actualTime){
      closeServo( servo );
      timeStampList[servo]=0;
      Serial.print("servo ");
      Serial.print(servo);
      Serial.println(" closed");
    }
  }
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  int i; 
  for( i = 0 ; i < 10 ; i++){
    timeStampList[i]=0;
    closeServo(i);
  } 
}


void loop() {
  UpdateServoState();
  //Serial.println(millis());
  
}
