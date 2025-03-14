void setup() {
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() {
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);

    analogWrite(D3, 0);

  float value = 0;

  while (value < 200) {
    analogWrite(D3, value);
    value++;
    delay(10);
  }
}