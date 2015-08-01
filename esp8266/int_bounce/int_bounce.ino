#include <ESP8266WiFi.h>

const char* ssid     = "bnet";
const char* password = "losalamos";
WiFiServer server(80);
char buffer[1024];

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server Started");
}

int value = 0;
int i;
long bounce = 0;
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  //String request = client.readStringUntil('\r');
  bounce = client.parseInt();
  Serial.println("bounce: " + String(bounce));
  client.flush();
  bounce++;

  String data = String(millis()) + "::" + 
    String(bounce) + "::" + 
    String(WiFi.localIP());
  Serial.print("Sending data: ");
  Serial.print(data);
  Serial.print("\n");
  client.println(data);
  client.stop();
}
