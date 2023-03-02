#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// WiFi
const char *ssid = "AloiTech"; // Enter your WiFi name
const char *password = "papajoao23";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "raspberrypi.local";
const char *topic = "testTopic";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

void callback(char *topic, byte *payload, unsigned int length) {
}

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    Serial.println("");
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      client.publish(topic, "hello emqx");
    } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
    }
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:

}
