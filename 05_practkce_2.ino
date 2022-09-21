#define PIN_LED 7
unsigned int toggle,i;
void setup() {
  pinMode(PIN_LED, OUTPUT);
  toggle = 0;
  digitalWrite(PIN_LED, toggle);
  delay(1000);
}

void loop() {
  for (i=0;i<5;i++) {
   toggle = 1;
   digitalWrite(PIN_LED, toggle);
   delay(200);
   toggle = 0;
   digitalWrite(PIN_LED, toggle);
   delay(200);  
  }
  toggle = 1;
  digitalWrite(PIN_LED, toggle);
  while(1) {}    
}
