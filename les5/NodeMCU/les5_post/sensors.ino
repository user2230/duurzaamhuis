void loopSensors() {
    Temperature = random(20, 30);  // Random temperature between 20 and 30
    Humidity = random(40, 60);     // Random humidity between 40 and 60
    HeatIndex = random(25, 35);    // Random heat index between 25 and 35
    Light = analogRead(A0);        // Read LDR value from analog pin A0

    Serial.println("Temperature: " + String(Temperature));
    Serial.println("Humidity: " + String(Humidity));
    Serial.println("Heat Index: " + String(HeatIndex));
    Serial.println("Light: " + String(Light));
}