#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 640
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
#define NUMBER_SERVO 10


unsigned long timeStampList[NUMBER_SERVO];
unsigned int Min_Pulse_Width[NUMBER_SERVO];
unsigned int MAx_Pulse_width[NUMBER_SERVO];

int pulseWidth(int angle, int servo){
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, Min_Pulse_Width[servo], MAx_Pulse_width[servo]);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void openServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(0,servonumber)); 
}

void closeServo(int servonumber){
  pwm.setPWM(servonumber, 0, pulseWidth(180,servonumber)); 
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
    MAx_Pulse_width[i] = MAX_PULSE_WIDTH; //to do one by one after 
    Min_Pulse_Width[i] = MIN_PULSE_WIDTH;
    timeStampList[i]=0;   
  } 
  MAx_Pulse_width[0]=2400;
  MAx_Pulse_width[1]=2150;
  MAx_Pulse_width[2]=2000;
  MAx_Pulse_width[3]=2350;
  MAx_Pulse_width[4]=2350;
  MAx_Pulse_width[5]=1900;
  MAx_Pulse_width[6]=2350;
  MAx_Pulse_width[7]=2500;
  Min_Pulse_Width[0]=640;
  Min_Pulse_Width[1]=640;
  Min_Pulse_Width[2]=640;
  Min_Pulse_Width[3]=640;
  Min_Pulse_Width[4]=640;
  Min_Pulse_Width[5]=640;
  Min_Pulse_Width[6]=640;
  Min_Pulse_Width[7]=640;
for( i = 0 ; i < 10 ; i++)
{
  openServo(i);
  delay(300);
  closeServo(i);
  }
}


void loop() {
  UpdateServoState();  
}
