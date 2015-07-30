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
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  value = 0;
  for (i=0;i<=50;i++) {
    value = value + analogRead(A0);
  }
  String data = String((double)value/(double)i);
  Serial.print("Sending data: ");
  Serial.print(data);
  Serial.print("\n");
  client.println(data);
  client.stop();
}
