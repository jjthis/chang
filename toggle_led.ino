#define PIN_LED 13
unsigned int count, toggle=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println("Hello");
  count=toggle=0;
  digitalWrite(PIN_LED, toggle);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(++count);
  toggle^=1;
  digitalWrite(PIN_LED,toggle);
  delay(1000);
}
