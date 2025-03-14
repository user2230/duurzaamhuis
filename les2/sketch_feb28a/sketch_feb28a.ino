void setup() {
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() {
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);

  // get random values
  int A = random(1, 4);

  // if < set lamp
  if (A == 1)
    digitalWrite(D3, HIGH);

  if (A == 2)
    digitalWrite(D5, HIGH);

  if (A == 3)
    digitalWrite(D6, HIGH);


  delay(100);
}