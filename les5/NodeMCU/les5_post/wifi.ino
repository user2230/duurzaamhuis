// WiFi libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

// WiFi variables
const char* ssid = "";
const char* password = "";
String deviceName;

// POST variables
const String serverProtocol = "";
const String serverIP = ""; // Ma cloud url or localhost IP
const String serverDirectory = "";
const uint8_t thumbprint[20] = {};
String URL = "";



void CheckWifi() {
  if(WiFi.status() != WL_CONNECTED) wifiConnect();
}

void SetupWifi() {
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  // Making sure all NodeMCU's have a different name!
  deviceName = "NodeMCU_" + String(random(0x7FFFFFFF));
  WiFi.hostname(deviceName.c_str());

  if(serverProtocol.length() > 0 && serverIP.length() > 0 && serverDirectory.length() > 0) {
    URL += serverProtocol + serverIP + "/" + serverDirectory;
  } else {
    Serial.println("SetupWifi :: Error! - serverProtocol, serverIp or serverDirectory has a length of 0!");
  }
}

void wifiConnect(){
  WiFi.mode(WIFI_OFF);
  delay(250);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to: " + String(ssid) + " ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(150);
    Serial.print("- ");
    delay(150);
    Serial.print("- ");
    delay(150);
    Serial.print(". ");
  }
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  Serial.print("\r\nConnected: SSID: " + String(ssid)); 
  Serial.println("    IP address: " + WiFi.localIP().toString());
  Serial.println("URL: " + URL);
  Serial.println("Device name: " + deviceName);
}

void SendPOST(char message[]) {
  WiFiClientSecure client;
  client.setFingerprint(thumbprint);
  HTTPClient https;
  https.setTimeout(7500);
  
  if( https.begin(client, URL) ) {
    static unsigned long packages = 0, success = 0, loss = 0;
    https.addHeader("Content-Type", "application/json");
    
    int responseCode = https.POST(message);
    String responseMsg = https.getString();
    
    Serial.println("[HTTPS] POST request: " + String(responseCode));
    Serial.println("[HTTPS] POST " + String(responseMsg));

    // Track package loss & draw a success-rate indicator
    ++packages;
    (responseCode == 200)? ++success : ++loss;   
    float successRate = round(( (double) success / (double) packages)*10000)/100;
    Serial.println("[packages: " + String(packages) + "   package-loss: " + String(loss) + "   success-rate: " + String(successRate) + "]");
    Serial.print("[succes-rate: ");
    for(int i = 1; i <= 33; ++i) {
      (i <= round(successRate/3))? Serial.print("⬛") : Serial.print("⬜");
    }
    Serial.println("]");
    
    https.end();
    if(responseCode == 200) {
      ReadJSON(responseMsg);
    }
  } else {
    Serial.println("[HTTPS] Could not start POST request...");
  }
  Serial.println("[HTTPS] POST ended");
}
