#define KEY1 36
#define KEY2 13
#define KEY3 19
#define KEY4 23
#define KEY5 18
#define KEY6 5

void setup()
{
  Serial.begin(115200);
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(KEY4, INPUT_PULLUP);
  pinMode(KEY5, INPUT_PULLUP);
  pinMode(KEY6, INPUT_PULLUP);
}

void loop()
{
  if (!digitalRead(KEY1))
  {
    Serial.println("KEY1");
  }
  if (!digitalRead(KEY2))
  {
    Serial.println("KEY2");
  }
  if (!digitalRead(KEY3))
  {
    Serial.println("KEY3");
  }
  if (!digitalRead(KEY4))
  {
    Serial.println("KEY4");
  }
  if (!digitalRead(KEY5))
  {
    Serial.println("KEY5");
  }
  if (!digitalRead(KEY6))
  {
    Serial.println("KEY6");
  }
  delay(200); // debounce
}
