const int pin_pul = 8;
const int pin_dir = 7;
const int indexPin = 13;
const int tonePin = 12;
const int relay_A = 4;
const int relay_B = 5;
const int emptiedPin = 3;
char command;
int emptiedStatus = 0;

void run(int pin_pul, int dur) {
  for (int i = 0; i < dur; ++i) {
    digitalWrite(pin_pul, HIGH);
    delayMicroseconds(500);
    digitalWrite(pin_pul, LOW);
    delayMicroseconds(500);
  }
}

void rightRun(int dur) {
  digitalWrite(pin_dir, 0);
  run(pin_pul, dur);
}

void leftRun(int dur) {
  digitalWrite(pin_dir, 1);
  run(pin_pul, dur);
}

void setup() {
  pinMode(indexPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(emptiedPin, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(pin_pul, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

void loop() {
  emptiedStatus = digitalRead(emptiedPin);
  command = Serial.read();

  if ('h' == command && emptiedStatus == 0) {
    //1、指示灯亮
    digitalWrite(indexPin, HIGH);

    //2、电机反向转动4周，400转动一周
    leftRun(400 * 4);

    Serial.write('success');

    //3、继电器A组松
    digitalWrite(relay_A, HIGH);
    delay(1000);

    //4、继电器A组紧
    digitalWrite(relay_A, LOW);
    delay(1000);

    //5、继电器B组松
    digitalWrite(relay_B, HIGH);
    delay(1000);

    //6、电机正向转动4周，400转动一周
    rightRun(400 * 4);

    //7、继电器B组紧
    digitalWrite(relay_B, LOW);
    delay(1000);

    //8、电机正向转动6周，400转动一周
    leftRun(400 * 6);

    //9、电机反向转动5周，400转动一周
    rightRun(400 * 6);

    //10、指示灯灭
    digitalWrite(indexPin, LOW);
  }

  if (emptiedStatus == 1) {
    tone(tonePin, 520);
    delay(1000);
    noTone(tonePin);
    delay(1000);
  } else {
    noTone(tonePin);
  }
}
