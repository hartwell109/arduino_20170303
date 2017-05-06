//适用于推拉式落杯器
//脉冲接口7
int stepperPin  = 7;

//方向控制接口8
int directionPin = 8;

//指示灯接口13
const int indexPin = 13;

//蜂鸣器接口12
const int tonePin = 12;

//继电器a组接口4
const int relay_A = 4;

//继电器b组接口5
const int relay_B = 5;

//空杯检测接口3
const int emptiedPin = 3;

//串口字符串指令：start
String command;
int emptiedStatus = 0;

void run(int dur) {
  for (int i = 0; i < dur; ++i) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(500);
  }
}

void runRight(int dur) {
  digitalWrite(directionPin, HIGH);
  run(dur);
}

void runLeft(int dur) {
  digitalWrite(directionPin, LOW);
  run(dur);
}

void setup() {
  pinMode(indexPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(emptiedPin, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  while (!Serial) {
    ;
  }
}

void loop() {
  emptiedStatus = digitalRead(emptiedPin);
  command = Serial.read();


  if (command == "start" && emptiedStatus == 0) {
    //1、指示灯亮
    digitalWrite(indexPin, HIGH);

    //2、电机反向转动10周，400转动一周
    runRight(400 * 10);

    //3、继电器A组松
    digitalWrite(relay_A, HIGH);
    delay(1000);

    //4、电机正向转动15周，400转动一周
    runLeft(400 * 15);

    //5、继电器A组紧
    digitalWrite(relay_A, LOW);
    delay(1000);

    //6、继电器B组松
    digitalWrite(relay_B, HIGH);
    delay(1000);

    //7、电机正向转动5周，400转动一周
    runRight(400 * 5);

    //8、继电器B组紧
    digitalWrite(relay_B, LOW);
    delay(1000);

    //9、指示灯灭
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
