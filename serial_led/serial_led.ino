char val;
int ledPin = 13;

//初始化部分
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

//循环部分
void loop() {
  val = Serial.read();
  if ('H' == val) {
    digitalWrite(ledPin, HIGH);
  }
  if ('F' == val) {
    digitalWrite(ledPin, LOW);
  }
}


