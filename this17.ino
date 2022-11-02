#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED 9

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define _EMA_ALPHA 0.8 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(1000000);///////////////////////////////////////////
}float ema=0;

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  float dis=(6762.0/(a_value-9)-4.0)*10.0;
  dis=min(max(0,dis),350);
  ema=_EMA_ALPHA * dis+(1-_EMA_ALPHA)*ema;
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!

  // map distance into duty
  //a_value
  //duty = //map(dis, 0, 1023, _DUTY_MIN, _DUTY_MAX);
  duty=100;
  if(100<=ema&&ema<=250){
    duty = (_DUTY_MAX-_DUTY_MIN)/150.0*(ema-100)+_DUTY_MIN;
    digitalWrite(PIN_LED, 0);
  myservo.writeMicroseconds(duty);
  }else digitalWrite(PIN_LED, 1);
  

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN: "); 
  Serial.print(100);
  Serial.print(",IR: "); 
  Serial.print(a_value);
  Serial.print(",dist: "); 
  Serial.print(dis);
  Serial.print(",ema: "); 
  Serial.print(ema);
  Serial.print(",servo: "); 
  Serial.print(duty);
  Serial.print(",MAX: "); 
  Serial.print(250);
  Serial.println("");
}
