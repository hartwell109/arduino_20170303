

int stepperPins [4] = {8, 9, 10, 11};

const int indexPin = 13;
const int tonePin = 12;
const int relay_A = 4;
const int relay_B = 5;
const int emptiedPin = 3;
char command;
int emptiedStatus = 0;

void stepper(int pins[4], int dir, int dur, int del) {
  for (int i = 0; i < dur; ++i) {
    if (dir == 1) {
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], HIGH);
      delayMicroseconds(del);
      digitalWrite(pins[0], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[3], LOW);
      delayMicroseconds(del);
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], LOW);
      delayMicroseconds(del);
      digitalWrite(pins[0], LOW);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[3], HIGH);
      delayMicroseconds(del);
    }
    if (dir == -1) {
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[0], HIGH);
      delayMicroseconds(del);
      digitalWrite(pins[3], HIGH);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[1], LOW);
      digitalWrite(pins[0], LOW);
      delayMicroseconds(del);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[2], HIGH);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[0], LOW);
      delayMicroseconds(del);
      digitalWrite(pins[3], LOW);
      digitalWrite(pins[2], LOW);
      digitalWrite(pins[1], HIGH);
      digitalWrite(pins[0], HIGH);
      delayMicroseconds(del);
    }
  }
}

void setup() {
  pinMode(indexPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(emptiedPin, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  for ( int i = 0; i < 3 ; i++) {
    pinMode(stepperPins[i], OUTPUT);
  }
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
    
    //2、电机反向转动10周，512转动一周
    stepper(stepperPins, 1, 512*10, 2200);
    
    //3、继电器A组松
    digitalWrite(relay_A, HIGH);    
    delay(1000);
    
    //4、电机正向转动15周，512转动一周
    stepper(stepperPins, -1, 512*15, 2200);
    
    //5、继电器A组紧
    digitalWrite(relay_A, LOW);
    delay(1000);
    
    //6、继电器B组松
    digitalWrite(relay_B, HIGH);
    delay(1000);    
    
    //7、电机正向转动5周，512转动一周
    stepper(stepperPins, 1, 512*5, 2200);
    
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
