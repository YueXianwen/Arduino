unsigned long time1;
unsigned long time2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  time1 = millis();
  time2 = micros();
  Serial.print(time1);
  Serial.println("ms");
  Serial.print(time1);
  Serial.println("us");
  delay(1000);
}
