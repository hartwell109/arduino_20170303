
const int emptiedPin = 3;
const int relay_A = 4;
const int relay_B = 5;
const int pin_ctrl = 6;
const int pin_dir = 7;
const int pin_pul = 8;
const int tonePin = 12;
const int indexPin = 13;
char command;
int emptiedStatus = 0;

void run(int dur) {
  digitalWrite(pin_ctrl, LOW);
  for (int i = 0; i < dur; ++i) {
    digitalWrite(pin_pul, HIGH);
    delayMicroseconds(500);
    digitalWrite(pin_pul, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(pin_ctrl, HIGH);
}

void rightRun(int dur) {
  digitalWrite(pin_dir, HIGH);
  run(dur);
}

void leftRun(int dur) {
  digitalWrite(pin_dir, LOW);
  run(dur);
}

void setup() {
  pinMode(indexPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(emptiedPin, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(pin_pul, OUTPUT);
  pinMode(pin_dir, OUTPUT);
  pinMode(pin_ctrl, OUTPUT);
  digitalWrite(pin_ctrl, HIGH);
  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

void loop() {
  emptiedStatus = digitalRead(emptiedPin);
  command = Serial.read();
  digitalWrite(pin_ctrl, HIGH);

  if ('a' == command && emptiedStatus == 0) {
    rightRun(400 * 2);
  }

  if ('b' == command && emptiedStatus == 0) {
    leftRun(400 * 2);
  }


  if ('h' == command && emptiedStatus == 0) {
    //1、蜂鸣器长鸣一次
    tone(tonePin, 520);
    delay(1000);
    noTone(tonePin);

    //2、指示灯亮
    digitalWrite(indexPin, HIGH);
    Serial.println("start");

    //3、电机反向转动4周，400转动一周
    rightRun(400 * 4);

    //4、继电器A组松
    digitalWrite(relay_A, HIGH);
    delay(1000);

    //5、继电器A组紧
    digitalWrite(relay_A, LOW);
    delay(500);

    //6、继电器B组松
    digitalWrite(relay_B, HIGH);
    delay(500);

    //7、电机正向转动4周，400转动一周
    leftRun(400 * 4);

    //8、继电器B组紧
    digitalWrite(relay_B, LOW);
    delay(500);

    //9、电机正向转动6周，400转动一周
    rightRun(400 * 8);
    Serial.println("success");

    //10、电机反向转动5周，400转动一周
    leftRun(400 * 8);

    //11、指示灯灭
    digitalWrite(indexPin, LOW);
    Serial.println("ready");

    //12、蜂鸣器短鸣两次
    tone(tonePin, 520);
    delay(500);
    noTone(tonePin);
    delay(500);
    tone(tonePin, 520);
    delay(500);
    noTone(tonePin);
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
