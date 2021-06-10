const int flexPin = A0;

void setup()
{
 Serial.begin(9600);
}

void loop()
{
  int flexValue;
  flexValue = analogRead(flexPin);
  Serial.print("Sensor: ");
  Serial.println(flexValue);
  delay(500);
  flexValue = map(flexValue, 993,950 , 0, 180);
}
