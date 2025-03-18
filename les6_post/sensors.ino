void loopSensors() {
  int A = random(999);
  int B = random(999);
  int C = random(999);
  int D = random(999);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);

  if (C > A and A < B)
  {
    digitalWrite(D5, HIGH);
  }
  if (B > C and B > A and C < A)
  {
    digitalWrite(D6, HIGH);
  }

  if (D > A and D > B and D > C)
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
  }


  float value = analogRead(A0);
  Serial.println(value);

  digitalWrite(D3, LOW);
  if (value > 500 && value < 900)
  {
    digitalWrite(D3, HIGH);
  }
}
