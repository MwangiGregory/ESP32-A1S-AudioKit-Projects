/**
 * Blink two red LEDs for the ESP32 Audio Development Platform
 * Alternates between each LED on and off every second
 */

#define LED_BUILTIN_1_PIN 19
#define LED_BUILTIN_2_PIN 22
#define BLINK_INTREVAL 500

void setup()
{
  pinMode(LED_BUILTIN_1_PIN, OUTPUT);
  pinMode(LED_BUILTIN_2_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN_1_PIN, HIGH);
  digitalWrite(LED_BUILTIN_2_PIN, LOW);
  delay(BLINK_INTREVAL);

  digitalWrite(LED_BUILTIN_1_PIN, LOW);
  digitalWrite(LED_BUILTIN_2_PIN, HIGH);
  delay(BLINK_INTREVAL);
}
