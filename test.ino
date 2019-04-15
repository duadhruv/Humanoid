
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 140
#define MAX_PULSE_WIDTH 590
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 60
double perdegreechange;

char input;
int analread;
int newanalread;
double changeangle;
double changeperdegree[3];
void setup() {
        pinMode(A5,INPUT);
        pinMode(A6,INPUT);
        pinMode(A7,INPUT);
        Serial.begin(9600);
        pwm1.begin();
        pwm1.setPWMFreq(FREQUENCY);




}

void loop() {

  char input = Serial.read();

  if (input=='c') //c for servocallibration
  {
 pwm1.setPWM(0, 0, pulseWidth(85));
 delay(500);
 int p=analogRead(A5);
 Serial.println(p);
 pwm1.setPWM(0, 0, pulseWidth(95));
 delay(500);
 int q=  analogRead(A5);
  Serial.println(q);
  changeangle = double((q-p))/10.0;
 Serial.println(double((q-p))/10.0);
  }

  if(input=='d') //d is for detach
  {
  pwm1.setPWM(0,0,0);
  Serial.println("detached");
  }
  if(input=='r')//r for analogread
  {
  analread = analogRead(A5);  
  }
   if(input=='s') //s is for set90
  {
  pwm1.setPWM(0,0,90);
  Serial.println("90 set");
  }
  if(input=='n')//n for newanalogread
  {
  newanalread = analogRead(A5);  
  }
   if(input=='z')//n for newanalogread
  {
  Serial.println(90+double(newanalread-analread)/changeangle);  
  }


}


int pulse_wide(int angle){
  int pulse = map(angle,0,180,140,590);
  return pulse;
}


double pulseWidth(double angle)
{
double pulse_wide, analog_value;
pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
//analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
//Serial.println(analog_value);
return pulse_wide;
}
