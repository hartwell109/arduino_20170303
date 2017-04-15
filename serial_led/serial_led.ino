//适用于转盘式的旧型号的落杯器

int motorPin = 3;
int switchPin = 2;

char command;
int switchStatus = 1;
int oldStatus = 1;

//初始化部分
void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

//循环部分
void loop() {
  switchStatus = digitalRead(switchPin);
  if (switchStatus == 0) {
    oldStatus = 0;
  }
  command = Serial.read();
  if (switchStatus == 0) {
    digitalWrite(motorPin, HIGH);
    oldStatus = 0;
  }
  if (switchStatus == 1 && oldStatus == 0) {
    digitalWrite(motorPin, LOW);
  }

  if ('H' == command ) {
    digitalWrite(motorPin, HIGH);
    oldStatus = 1;
  }

  if ('F' == command) {
    digitalWrite(motorPin, LOW);
    oldStatus = 1;
  }

  digitalWrite(13, oldStatus);
}


