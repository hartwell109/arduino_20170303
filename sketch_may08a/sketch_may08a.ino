const int emptiedPin = 3;
const int emptiedPin2 = 12;

const int relay_A = 4;
const int relay_B = 5;

const int pin1_ctrl = 6;
const int pin1_dir = 7;
const int pin1_pul = 8;

const int pin2_ctrl = 9;
const int pin2_dir = 10;
const int pin2_pul = 11;

const int tonePin = 13;
const int indexPin = 13;
char command;
String status = "ready";
int emptiedStatus = 0;

void run1(int dur) {
  digitalWrite(pin1_ctrl, LOW);
  for (int i = 0; i < dur; ++i) {
    digitalWrite(pin1_pul, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pin1_pul, LOW);
    delayMicroseconds(2000);
  }
  digitalWrite(pin1_ctrl, HIGH);
}

void rightRun1(int dur) {
  digitalWrite(pin1_dir, HIGH);
  run1(dur);
}

void leftRun1(int dur) {
  digitalWrite(pin1_dir, LOW);
  run1(dur);
}

void run2(int dur) {
  digitalWrite(pin2_ctrl, LOW);
  for (int i = 0; i < dur; ++i) {
    digitalWrite(pin2_pul, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pin2_pul, LOW);
    delayMicroseconds(2000);
  }
  digitalWrite(pin2_ctrl, HIGH);
}

void rightRun2(int dur) {
  digitalWrite(pin2_dir, HIGH);
  run2(dur);
}

void leftRun2(int dur) {
  digitalWrite(pin2_dir, LOW);
  run2(dur);
}

void setup() {
  pinMode(indexPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(emptiedPin, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(pin1_pul, OUTPUT);
  pinMode(pin1_dir, OUTPUT);
  pinMode(pin1_ctrl, OUTPUT);
  pinMode(pin2_pul, OUTPUT);
  pinMode(pin2_dir, OUTPUT);
  pinMode(pin2_ctrl, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

void loop() {
  emptiedStatus = digitalRead(emptiedPin);
  command = Serial.read();

  if ('i' == command && emptiedStatus == 0) {
    Serial.println(status);
  }

  if ('h' == command && emptiedStatus == 0) {
    //1、蜂鸣器长鸣一次
    tone(tonePin, 520);
    delay(1000);
    noTone(tonePin);

    //2、指示灯亮
    digitalWrite(indexPin, HIGH);
    status = "start";
    Serial.println(status);

    //3、电机反向转动4周，400转动一周
    leftRun1(400 * 4);

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
    rightRun1(400 * 4);

    //8、继电器B组紧
    digitalWrite(relay_B, LOW);
    delay(500);

    //9、电机正向转动10周，400转动一周
    leftRun1(400 * 10);
    status = "success";
    Serial.println(status);

    //10、电机反向转动10周，400转动一周
    rightRun1(400 * 10);

    //11、指示灯灭电机断电
    digitalWrite(indexPin, LOW);
    digitalWrite(pin1_ctrl, HIGH);
    status = "ready";
    Serial.println(status);

    //12、蜂鸣器短鸣两次
    tone(tonePin, 520);
    delay(500);
    noTone(tonePin);
    delay(500);
    tone(tonePin, 520);
    delay(500);
    noTone(tonePin);
  }

  //13、上空杯检测
  if (emptiedStatus == 1) {
    delay(500);
    status = "empty";
    Serial.println(status);
  }

}
