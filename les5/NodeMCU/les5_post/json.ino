// JSON API: https://arduinojson.org/v6/api/
 
// JSON libraries
#include <ArduinoJson.h>
 
// JSON document
JsonDocument doc;
 
void CreateJSON() {
  StaticJsonDocument<256> doc;
  static int attempt = 0;
  doc["attempt"] = ++attempt;
  doc["attempt"] = Temperature;
  doc["humidity"] = Humidity;
  doc["heat_index"] = HeatIndex;
  doc["ldr_value"] = analogRead(LDR_Pin);
  serializeJson(doc, jsonOut);
}
 
void ReadJSON(String resJSON){
  resJSON.remove(0, 9);
 
  StaticJsonDocument<200> resDoc;
  deserializeJson(resDoc, resJSON);
 
  digitalWrite(D3, bool(resDoc["lights"][0]));
  digitalWrite(D5, bool(resDoc["lights"][1]));
  digitalWrite(D6, bool(resDoc["lights"][2]));
}
 
// for easy JSON debugging
void SendJSONToSerial() {
  serializeJson(doc, Serial);
  Serial.println();
}