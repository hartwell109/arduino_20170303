
const int ledPin = 13;
const int buzzerPin = 12;
const long frequency = 800;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, frequency);
  delay(1000);
  noTone(buzzerPin);
  digitalWrite(ledPin, LOW);
  delay(500);
}
