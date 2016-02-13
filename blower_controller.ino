#define CONTROLL_PIN 9

void setup() {
  pinMode(CONTROLL_PIN, OUTPUT);
  digitalWrite(CONTROLL_PIN, LOW);

  Serial.begin(115200);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("Serial Read Test");
  Serial.println("-------------------");

}

int get_serial_data() {

  char input[30];
  uint8_t i = 0;
  int result = -1;

  while (true) {
    if (Serial.available() > 0) {
      input[i] = Serial.read();
      if (input[i] >= '0' && input[i] <= '9') {
        i++;
      } else {

        if (i == 0) {
          break;
        }

        // 末尾に終端文字の挿入
        input[i] = '\0';
        // 受信文字列を送信
        //Serial.println(input);
        // カウンタの初期化
        i = 0;
        result = atoi(input);
        break;
      }
    }
  }

  return result;
}

void loop() {

  int v = get_serial_data();

  if (v == -1) {
    return;
  }

  if (v == 0) {
    Serial.print("DEVICE OFF\n");
    analogWrite(CONTROLL_PIN, 0);
  } else if (v > 0 && v < 256) {
    Serial.print("DEVICE ON ");
    Serial.println(v);
    analogWrite(CONTROLL_PIN, v);
  } else {
    Serial.println("INVALID DATA");
  }

}
