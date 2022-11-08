#include <Servo.h>

#define PIN_LED 9
#define PIN_IR A0  
#define PIN_SERVO 10

#define _DUTY_MIN 553  
#define _DUTY_NEU 1476 
#define _DUTY_MAX 2399 

#define _DIST_MIN 100.0
#define _DIST_MAX 250.0

#define EMA_ALPHA 0.5
#define LOOP_INTERVAL 25  

Servo myservo;

unsigned long last_loop_time; 
int dist, dist_ema, dist_prev = _DIST_MIN;
int duty;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_IR, INPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(1000000);
}

void loop()
{
  unsigned long time_curr = millis();
  
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  
  int value = analogRead(PIN_IR); 
  dist = (6762.0/(value-9)-4.0)*10.0 - 60.0;  
  duty = (_DUTY_MIN) + (((_DUTY_MAX)-(_DUTY_MIN))/(150.0))*((dist)-100);
  
  if (dist < _DIST_MIN){  
    dist = _DIST_MIN;
    digitalWrite(PIN_LED, 1);
    myservo.writeMicroseconds(_DUTY_MIN);
  } else if (dist <= _DIST_MAX){
    digitalWrite(PIN_LED, 0);
    myservo.writeMicroseconds(duty);
  } else if ( dist > _DIST_MAX){
    dist = _DIST_MAX;
    digitalWrite(PIN_LED, 1);
    myservo.writeMicroseconds(_DUTY_MAX);
  }
  
  dist_ema = (EMA_ALPHA * dist) + ((1 - EMA_ALPHA)*dist_ema);
  
  Serial.print("MIN:");     Serial.print(_DIST_MIN);
  Serial.print(",IR:");     Serial.print(value);
  Serial.print(",dist:");   Serial.print(dist);
  Serial.print(",ema:");     Serial.print(dist_ema);
  Serial.print(",servo:");  Serial.print(duty);
  Serial.print(",MAX:");    Serial.print(_DIST_MAX);
  Serial.println("");
  
  last_loop_time += LOOP_INTERVAL; 
}
